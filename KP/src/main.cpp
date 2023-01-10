#include "Shazam.h"

inline void usage() {
    std::cout
            << "USAGE:\n append <path to file>: add file to database\n search <path to file>: search mp3 at database\n exit: end program\n";
}

int main(int argv, char **argc) {
    Shazam shazam;
    std::string query, filename;
    usage();
    bool run = true;
    while (run) {
        std::cin >> query;
        if (query == "append") {
            std::cin >> filename;
            shazam.append(filename);
            usage();
        } else if (query == "search") {
            std::cin >> filename;
            auto res = shazam.search(filename);
            std::cout << "\t\tSEARCH RESULT:" << std::endl;
            std::cout.precision(4);
            for (const auto &[name, percent]: res) {
                std::cout << percent << "% " << name << std::endl;
            }
            usage();
        } else if (query == "exit") {
            run = false;
        } else {
            usage();
        }
    }
    return 0;
}
