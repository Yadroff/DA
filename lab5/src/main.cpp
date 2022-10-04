#include <iostream>
#include "SuffTree.h"

int main() {
//    std::cout << "Hello, World!" << std::endl;
	std::string str;
	std::cin >> str;
	std::cout << str.substr(1, 0);
	TSuffixTree tree(str + str);
	std::cout << tree.lexMinString(str.size());
    return 0;
}
