#ifndef INC_4LAB_SRC_TWORD_HPP
#define INC_4LAB_SRC_TWORD_HPP

#include <iostream>
#include <vector>

const unsigned short MAX_WORD_SIZE = 16;

class TWord {
public:
    TWord() = default;

    TWord(const std::string &str, const unsigned int &word, const unsigned int &string);

    char &operator[](unsigned short &i);

    char operator[](unsigned short &i) const;

    friend bool operator==(const TWord &lhs, const TWord &rhs);

    friend bool operator!=(const TWord &lhs, const TWord &rhs);

    void setStringId(unsigned int stringId);

    void setWordId(unsigned int wordId);

    unsigned int getStringId() const;

    unsigned int getWordId() const;

    friend std::ostream &operator<<(std::ostream &os, const TWord &word);
private:
    char Word[MAX_WORD_SIZE];
    unsigned int StringID;
    unsigned int WordID;
};

std::vector<int> ZFunction(const std::vector<TWord> &string);

std::vector<int> SPFunction(const std::vector<TWord> &string);

void Search(const std::vector<TWord> &pattern, const std::vector<TWord> &text, const std::vector<int> &sp, int &start);

#endif //INC_4LAB_SRC_TWORD_HPP
