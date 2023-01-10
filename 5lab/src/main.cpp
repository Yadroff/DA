#include <iostream>
#include <chrono>

#include "SuffTree.h"

const std::string SENTINEL = "$";


int main() {
    auto startPoint = std::chrono::system_clock::now();
    std::string input;
    std::cin >> input;
    input = input + input + SENTINEL;
    auto *tree = new TSuffixTree(input);
    std::string answer = tree->lexMinString();
//    std::cout << answer << "\n";
    delete tree;
    auto endPoint = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count() << " ms"
              << std::endl;
    return 0;
}