#ifndef INC_4LAB_SRC_TWORD_HPP
#define INC_4LAB_SRC_TWORD_HPP

#include <iostream>
#include <vector>

const unsigned short MAX_WORD_SIZE = 17;
const unsigned short ALPHABET_SIZE = 26;

struct TWord {
    TWord();

    friend bool operator==(const TWord &lhs, const TWord &rhs);

    friend bool operator!=(const TWord &lhs, const TWord &rhs);

    char Word[MAX_WORD_SIZE];
    unsigned int StringID;
    unsigned int WordID;
    unsigned int Size;
    unsigned int Hash;
};

std::vector<int> ZFunction(const std::vector<TWord> &string);

std::vector<int> SPFunction(const std::vector<TWord> &string);

void Search(const std::vector<TWord> &pattern, const std::vector<TWord> &text, const std::vector<int> &sp, int &start);

#endif //INC_4LAB_SRC_TWORD_HPP
