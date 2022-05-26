#include "TWord.hpp"

TWord::TWord(const std::string &str, const unsigned int &word, const unsigned int &string) {
    for (unsigned short i = 0; i < MAX_WORD_SIZE; ++i) {
        Word[i] = str[i];
    }
    StringID = word;
    WordID = string;
}

char &TWord::operator[](unsigned short &i) {
    return Word[i];
}


bool operator==(const TWord &lhs, const TWord &rhs) {
    for (unsigned short i = 0; i < MAX_WORD_SIZE; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const TWord &lhs, const TWord &rhs) {
    return !(lhs == rhs);
}

void TWord::setStringId(unsigned int stringId) {
    StringID = stringId;
}

void TWord::setWordId(unsigned int wordId) {
    WordID = wordId;
}

unsigned int TWord::getStringId() const {
    return StringID;
}

unsigned int TWord::getWordId() const {
    return WordID;
}

char TWord::operator[](unsigned short &i) const {
    return (i < MAX_WORD_SIZE) ? Word[i] : '\0';
}


std::ostream &operator<<(std::ostream &os, const TWord &word) {
    std::string str;
    for (unsigned short i = 0; i < MAX_WORD_SIZE and word[i] != 0; ++i) {
        str.push_back(word.Word[i]);
    }
    os << str;
    return os;
}

std::vector<int> ZFunction(const std::vector<TWord> &string) {
    int n = (int) string.size();
    std::vector<int> z(n);
    z.reserve(n);
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
    sp.reserve(n);
    for (int i = n - 1; i > 0; --i) {
        sp[i + z[i] - 1] = z[i];
    }
    return sp;
}

void Search(const std::vector<TWord> &pattern, const std::vector<TWord> &text, const std::vector<int> &sp, int &start) {
    size_t patternSize = pattern.size();
    size_t textSize = text.size();
    unsigned int i = start;
    while (i < textSize - patternSize + 1) {
        unsigned int j = 0;
        while (j < patternSize and text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == patternSize) {
            std::cout << text[i].getStringId() << ", " << text[i].getWordId() << std::endl;
        } else if (j > 0 and j > sp[j - 1]) {
            i = i + j - sp[j - 1] - 1;
        }
        ++i;
    }
    start = i - patternSize;
}
