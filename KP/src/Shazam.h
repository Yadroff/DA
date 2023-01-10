#ifndef KP_SHAZAM_H
#define KP_SHAZAM_H

#include <chrono>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "Definitions.h"

class Shazam {
public:
    Shazam();

    ~Shazam();

    void append(const std::string &fileName);

    void write(std::ofstream &out);

    void read(std::ifstream &input);

    std::vector<std::pair<std::string, double>> search(const std::string &name);

    static std::vector<Complex> initRoots();

    static std::vector<double> HannWindow();

private:
    void initDB();

    std::vector<float> processFile(const std::string &fileName);

    std::vector<Size> getHashes(const std::string &fileName);

    static std::vector<std::string> getSongs();

    static void FFT(std::vector<Complex> *arr);

    static Size getInd(Size freq);

    static Size hash(const std::array<Size, RANGE_NUM> &freq);

    static std::vector<Complex> roots_;
    static std::vector<double> hann_;
    std::mutex mutex_;

    std::unordered_map<Size, std::vector<std::pair<Size, Size>>> database_; // [hash, [id, block_num]]
    /* для каждого хэша хранится вектор из пар ID песни, номер блока*/
    std::unordered_map<Size, std::string> newSongs_;
    std::vector<std::string> songs_;

    static Size diff(const Size &left, const Size &right);
};


#endif //KP_SHAZAM_H
