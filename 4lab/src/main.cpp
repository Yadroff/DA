#include "TWord.hpp"

inline void Clear(TWord &word) {
    word.Hash = 0;
    word.Size = 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<TWord> pattern;
    std::vector<TWord> text;
    int start = 0;
    unsigned short ind = 0;
    TWord current;
    std::vector<int> sp;
    std::string buffer;
    getline(std::cin, buffer);
    for (auto &c: buffer) {
        if (c == ' ' or c == '\t') {
            if (ind > 0) {
                pattern.emplace_back(current);
            }
            Clear(current);
            ind = 0;
        } else {
            current.Word[ind] = toupper(c);
            current.Hash = current.Hash * ALPHABET_SIZE + current.Word[ind] - 'A';
            ++ind;
        }
    }
    if (ind > 0) {
        pattern.emplace_back(current);
        Clear(current);
        ind = 0;
    }
    sp = SPFunction(pattern);
    text.reserve(2 * pattern.size());
    current.WordID = 1;
    current.StringID = 1;
    while (getline(std::cin, buffer)) {
        for (auto &c: buffer) {
            if (c == '\t' or c == ' ') {
                if (ind > 0) {
                    text.emplace_back(current);
                    if (text.size() > 2 * pattern.size()) {
                        Search(pattern, text, sp, start);
                        text.erase(text.begin(), text.begin() + (int) pattern.size());
                        text.reserve(2 * text.size());
                    }
                    ind = 0;
                    ++current.WordID;
                    Clear(current);
                }
            } else {
                current.Word[ind] = toupper(c);
                current.Hash = current.Hash * ALPHABET_SIZE + current.Word[ind] - 'A';
                ++ind;
            }
        }
        if (ind > 0) {
            text.emplace_back(current);
            if (text.size() > 2 * pattern.size()) {
                Search(pattern, text, sp, start);
                text.erase(text.begin(), text.begin() + (int) pattern.size());
                text.reserve(2 * text.size());
            }
        }
        current.WordID = 1;
        ++current.StringID;
        Clear(current);
        ind = 0;
    }
    if (ind > 0) {
        text.emplace_back(current);
    }
    Search(pattern, text, sp, start);
    return 0;
}