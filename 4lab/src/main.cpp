#include <iostream>
#include <vector>


#include "TWord.hpp"

void Clear(TWord &word) {
    for (unsigned short i = 0; i < MAX_WORD_SIZE; ++i) {
        word[i] = '\0';
    }
}

int main() {
    bool textPatternFlag = true;
    std::vector<TWord> pattern;
    std::vector<TWord> text;
    int start = 0;
    char c;
    unsigned short ind = 0;
    TWord current;
    std::vector<int> sp;
    current.setWordId(0);
    current.setStringId(0);
    Clear(current);
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (ind > 0) {
                textPatternFlag ? pattern.emplace_back(current) : text.emplace_back(current);
                if (!textPatternFlag and text.size() > 2 * pattern.size()) {
                    Search(pattern, text, sp, start);
                    text.erase(text.begin(), text.begin() + (int) pattern.size());
                    text.reserve(2 * pattern.size());
                }
                Clear(current);
                ind = 0;
            }
            current.setStringId(current.getStringId() + 1);
            if (textPatternFlag) {
                textPatternFlag = false;
                if (pattern.empty()) {
                    return 0;
                }
                current.setStringId(1);
                sp = SPFunction(pattern);
            }
            current.setWordId(1);
        } else if (c == '\t' or c == ' ') {
            if (ind > 0) {
                textPatternFlag ? pattern.emplace_back(current) : text.emplace_back(current);
                if (!textPatternFlag and text.size() > 2 * pattern.size()) {
                    Search(pattern, text, sp, start);
                    text.erase(text.begin(), text.begin() + (int) pattern.size());
                    text.reserve(2 * pattern.size());
                }
                ind = 0;
                current.setWordId(current.getWordId() + 1);
                Clear(current);
            }
        } else {
            if ('a' <= c and 'z' >= c) {
                c = toupper(c);
            }
            current[ind] = c;
            ++ind;
        }
    }
    if (ind > 0) {
        textPatternFlag ? pattern.emplace_back(current) : text.emplace_back(current);
    }
    Search(pattern, text, sp, start);
    return 0;
}
