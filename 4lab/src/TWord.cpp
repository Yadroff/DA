#include "TWord.hpp"

TWord::TWord() : WordID(0), StringID(0), Hash(0), Size(0) {}

bool operator==(const TWord &lhs, const TWord &rhs) {
    if (lhs.Hash != rhs.Hash) {
        return false;
    }
    for (int i = 0; i < lhs.Size; ++i) {
        if (lhs.Word[i] != rhs.Word[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const TWord &lhs, const TWord &rhs) {
    return !(lhs == rhs);
}

std::vector<int> ZFunction(const std::vector<TWord> &string) {
    int n = (int) string.size();
    std::vector<int> z(n);
    for (int i = 1, left = 0, right = 0; i < n; ++i) {
        if (i <= right) {
            z[i] = std::min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < n and string[z[i]] == string[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > right) {
            left = i, right = i + z[i] - 1;
        }
    }
    return z;
}

std::vector<int> SPFunction(const std::vector<TWord> &string) {
    std::vector<int> z = ZFunction(string);
    int n = (int) z.size();
    std::vector<int> sp(n);
    for (int i = n - 1; i > 0; --i) {
        sp[i + z[i] - 1] = z[i];
    }
    return sp;
}

void Search(const std::vector<TWord> &pattern, const std::vector<TWord> &text, const std::vector<int> &sp, int &start) {
    size_t patternSize = pattern.size();
    size_t textSize = text.size();
    if (patternSize > textSize) {
        return;
    }
    unsigned int i = start;
    while (i < textSize - patternSize + 1) {
        unsigned int j = 0;
        while (j < patternSize and text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == patternSize) {
            std::cout << text[i].StringID << ", " << text[i].WordID << "\n";
        } else if (j > 0 and j > sp[j - 1] + 1) {
            i = i + j - sp[j - 1] - 1;
        }
        ++i;
    }
    start = i - patternSize;
}