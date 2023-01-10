#include "Shazam.h"

#include <filesystem>
#include <fstream>
#include <algorithm>

std::vector<Complex> Shazam::roots_ = Shazam::initRoots();
std::vector<double> Shazam::hann_ = Shazam::HannWindow();

void threadFunc(Shazam *shazam, Size start, Size count, std::vector<std::string> *songs) {
    for (Size i = 0; i < count; ++i) {
        shazam->append((*songs)[start + i]);
    }
}

Shazam::Shazam() {
    std::ifstream in(LIB_FILE);
    if (!in.is_open()) {
        std::cout << "CAN NOT OPEN FILE: " << LIB_FILE << std::endl;
        perror(std::string("CAN NOT OPEN INPUT FILE: ").append(LIB_FILE).c_str());
        initDB();
        return;
    }
    read(in);
    in.close();
}

std::vector<Complex> Shazam::initRoots() {
    std::vector<Complex> roots(BLOCK_SIZE / 2);
    double angle = 2 * M_PI / BLOCK_SIZE;
    Complex W(std::cos(angle), std::sin(angle));
    Complex root(1, 0);
    for (int i = 0; i < BLOCK_SIZE / 2; ++i, root *= W) {
        roots[i] = root;
    }
    return roots;
}

std::vector<double> Shazam::HannWindow() {
    std::vector<double> Hann(BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        Hann[i] = 0.5 * (1UL - std::cos(2UL * (double) M_PI * i / (BLOCK_SIZE - 1)));
    }
    return Hann;
}

std::vector<float> Shazam::processFile(const std::string &fileName) {
    auto handle = mpg123_new(nullptr, nullptr);
    assert(handle != nullptr);
    assert(mpg123_param(handle, MPG123_FLAGS, MPG123_MONO_MIX | MPG123_QUIET | MPG123_FORCE_FLOAT, 0.) == MPG123_OK);
    assert(mpg123_open(handle, fileName.c_str()) == MPG123_OK);
    long rate;
    int channels, encoding;
//    assert(mpg123_getformat(handle, &rate, &channels, &encoding) == MPG123_OK);
    if (mpg123_getformat(handle, &rate, &channels, &encoding) != MPG123_OK) {
        std::cout << "CAN NOT GET FORMAT" << std::endl;
    }
    if (rate != RATE) {
        std::cout << "ERROR: FILE: " << fileName << " WRONG RATE: " << rate << std::endl;
        return {};
    }
    const int partSize = 1024;
    unsigned char part[partSize];
    Size bytesRead = 0;
    Size bytesProcessed = 0;
    std::vector<float> arr(partSize / sizeof(float));
    do {
        int err = mpg123_read(handle, part, partSize, &bytesRead);
        arr.resize((bytesRead + bytesProcessed) / sizeof(float) + 1);
        memcpy((unsigned char *) arr.data() + bytesProcessed, part, bytesRead);
        bytesProcessed += bytesRead;
        if (err == MPG123_DONE) {
            break;
        }
        assert(err == MPG123_OK);
    } while (bytesRead);
    arr.resize(bytesProcessed / sizeof(float));
    int err = mpg123_close(handle);
    assert(err == MPG123_OK);
    mpg123_delete(handle);
    return arr;
}

std::vector<Size> Shazam::getHashes(const std::string &fileName) {
    using namespace std::chrono;
    auto start = system_clock::now();
    std::vector<float> samples = processFile(fileName);
    std::vector<Size> res;
    Size blocks = samples.size() / BLOCK_SIZE;
    res.reserve(blocks);
    for (size_t block = 0; block < blocks; ++block) {
        std::vector<Complex> _complex(BLOCK_SIZE);
        for (int i = 0; i < BLOCK_SIZE; ++i) {
            _complex[i] = Complex(samples[block * BLOCK_SIZE + i]) * hann_[i];
        }
        FFT(&_complex);
        std::array highVal{-1., -1., -1., -1., -1.};
        std::array<Size, RANGE_NUM> maxFreq = {0, 0, 0, 0, 0};
        for (Size freq = RANGE_MIN; freq < RANGE_MAX; ++freq) {
            double intensity = std::log(std::abs(_complex[freq]) + 1.);
            Size id = getInd(freq);
            if (intensity > highVal[id]) {
                highVal[id] = intensity;
                maxFreq[id] = freq;
            }
        }
        res.emplace_back(hash(maxFreq));
    }
/*    auto end = system_clock::now();
    std::cout << "GET HASHES TIME: " << fileName << std::endl <<  end - start << std::endl;*/
    return res;
}

void Shazam::FFT(std::vector<Complex> *a) {
    int n = (int) a->size();
    if (n == 1) return;

    std::vector<Complex> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = (*a)[i];
        a1[j] = (*a)[i + 1];
    }
    FFT(&a0);
    FFT(&a1);

    double ang = 2 * M_PI / n;
    Complex w(1), wn(std::cos(ang), std::sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        (*a)[i] = a0[i] + w * a1[i];
        (*a)[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }
}

Size Shazam::getInd(Size freq) {
    if (freq < RANGE_MIN) {
        return 0;
    }
    if (freq > RANGE_MAX) {
        return RANGE_NUM - 1;
    }
    for (int i = 0; i < RANGE_NUM; ++i) {
        if (freq < RANGES[i]) {
            return i;
        }
    }
    return RANGE_NUM - 1;
}

Size Shazam::hash(const std::array<Size, RANGE_NUM> &freq) {
    Size res = freq[0] - (freq[0] % HASH_CONST);
    res += (freq[1] - (freq[1] % HASH_CONST)) * 100;
    res += (freq[2] - (freq[2] % HASH_CONST)) * 100000;
    res += (freq[3] - (freq[3] % HASH_CONST)) * 100000000;
    return res;
}

void Shazam::append(const std::string &fileName) {
    using namespace std::chrono;
    std::string name = std::filesystem::path(fileName).filename();
    auto time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "APPEND FILE: " << name << " START" << std::endl;
    auto hashes = getHashes(fileName);
    std::lock_guard<std::mutex> lock(mutex_);
    Size id = songs_.size();
    songs_.emplace_back(name);
    newSongs_[id] = name;
    for (Size i = 0; i < hashes.size(); ++i) {
        database_[hashes[i]].emplace_back(std::make_pair(id, i));
    }
    time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "APPEND FILE: " << name << " END" << std::endl;
}


void Shazam::initDB() {
    auto songs = getSongs();
    using namespace std::chrono;
    auto time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "FOUND " << songs.size() << " FILES" << std::endl;
    Size threadsCount = std::thread::hardware_concurrency();
    Size songsPerThread = songs.size() / threadsCount;
    Size ost = songs.size() % threadsCount;
    std::vector<std::thread> threads;
    Size start = 0;
    for (Size i = 0; i < threadsCount; ++i) {
        threads.emplace_back(threadFunc, this, start, songsPerThread + (i < ost), &songs);
        start += songsPerThread + (i < ost);
    }
    for (Size i = 0; i < threadsCount; ++i) {
        threads[i].join();
    }
}

std::vector<std::string> Shazam::getSongs() {
    std::vector<std::string> res;
    for (const auto &file: std::filesystem::directory_iterator(LIBRARY_PATH)) {
        if (file.path().extension() == ".mp3") {
            res.emplace_back(file.path());
        }
    }
    return res;
}

void Shazam::read(std::ifstream &input) {
    std::string name;
    Size vecSize, hash, blockNum, id = 0;
    std::vector<std::string> songs;
    std::unordered_map<Size, std::vector<std::pair<Size, Size>>> database;
    while (std::getline(input, name)) {
        if (name.empty()) {
            continue;
        }
        songs.emplace_back(name);
        using namespace std::chrono;
        auto time = system_clock::to_time_t(system_clock::now());
        std::cout << std::ctime(&time) << "READ FROM DB SONG: " << name << " START" << std::endl;
        input >> vecSize;
        for (Size i = 0; i < vecSize; ++i) {
            input >> hash >> blockNum;
            database[hash].emplace_back(std::make_pair(id, blockNum));
        }
        ++id;
        time = system_clock::to_time_t(system_clock::now());
        std::cout << std::ctime(&time) << "READ FROM DB SONG: " << name << " END" << std::endl;
//        input.ignore('\n', 1);
    }
    songs_ = songs;
    database_ = database;
    input.close();
}

void Shazam::write(std::ofstream &out) {
    std::unordered_map<Size, std::vector<std::pair<Size, Size>>> map(newSongs_.size()); // [ID, {[Hash, Block number]}]
    for (const auto &[hash, vector]: database_) {
        for (const auto &[id, blockNum]: vector) {
            if (newSongs_.contains(id)) {
                map[id].emplace_back(std::make_pair(hash, blockNum));
            }
        }
    }
    for (const auto &[id, vec]: map) {
        out << songs_[id] << std::endl;
        out << vec.size() << std::endl;
        for (const auto &[hash, blockNum]: vec) {
            out << hash << " " << blockNum << std::endl;
        }
    }
    out.close();
}

Shazam::~Shazam() {
    std::ofstream out(LIB_FILE, std::ostream::app | std::ostream::out);
    if (!out.is_open()) {
        std::cout << "ERROR: CAN NOT OPEN FILE: " << LIB_FILE << std::endl;
        perror(std::string("CAN NOT OPEN OUTPUT FILE: ").append(LIB_FILE).c_str());
    } else {
        write(out);
    }
}

std::vector<std::pair<std::string, double>> Shazam::search(const std::string &name) {
    using namespace std::chrono;
    auto time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "\t\tBEGIN SEARCH\nGET HASHES: START " << name << std::endl;
    auto hashes = getHashes(name);
    time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "GET HASHES: END\nSearch: START" << std::endl;
    std::unordered_map<Size, Size> statistic;
    Size cnt = 0;
    /* Собираем статистику совпадений. Берем i и j отрезок времени в заданной песне.
     * Ищем совпадающие по хэшу песни с одинаковой разницей в отрезках.
     * В результате имеем пары [ID, stat], где ID - ID песни, stat - количество совпадающих отрезков */
    for (Size firstSample = 0; firstSample < hashes.size(); ++firstSample) {
        for (Size secondSample = firstSample + 1; secondSample < hashes.size(); ++secondSample) {
            Size firstHash = hashes[firstSample], secondHash = hashes[secondSample];
            auto firstIt = database_.find(firstHash);
            auto secondIt = database_.find(secondHash);
            if (firstIt == database_.end() or secondIt == database_.end()) {
                continue;
            }
            ++cnt;
            auto firstVec = firstIt->second, secondVec = secondIt->second;
            // вектор пар [id, sample], хэш каждого сэмпла равен либо хэшу первого сэмпла образца, либо второго
            for (const auto &[firstID, firstBlock]: firstVec) {
                for (const auto &[secondID, secondBlock]: secondVec) {
                    if (firstID == secondID and diff(firstSample, secondSample) == diff(firstBlock, secondBlock)) {
                        ++statistic[firstID];
                    }
                }
            }
        }
    }
    time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "SEARCH: END\nCREATE RESULT: START" << std::endl;
    std::vector<std::pair<std::string, double>> res;
    res.reserve(statistic.size());
    for (const auto &[id, stat]: statistic) {
        double percent = static_cast<double>(stat) / static_cast<double>(cnt) * 100.;
        res.emplace_back(songs_[id], percent);
    }
    std::sort(all(res), [](const auto &left, const auto &right) { return left.second > right.second; });
    time = system_clock::to_time_t(system_clock::now());
    std::cout << std::ctime(&time) << "CREATE RESULT: END\n EXIT FROM SEARCH" << std::endl;
    return res;
}

Size Shazam::diff(const Size &left, const Size &right) {
    return (left > right) ? left - right : right - left;
}
