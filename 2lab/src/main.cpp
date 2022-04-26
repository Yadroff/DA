#include <iostream>
#include "avl.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    TAVL<std::string, unsigned long long> tree;
    std::string command, key;
    unsigned long long value;

    while (true) {
        std::cin >> std::ws;
        if (std::cin.eof()) {
            break;
        }
        std::cin >> command;
        if (command == "+") {
            std::cin >> key;
            for (auto &x: key) {
                x = (char) tolower(x);
            }
            std::cin >> value;
            if (tree.Insert(key, value)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "Exist" << std::endl;
            }
        } else if (command == "-") {
            std::cin >> key;
            for (auto &x: key) {
                x = (char) tolower(x);
            }
            if (tree.Remove(key)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "NoSuchWord" << std::endl;
            }
        } else if (command == "!") {
            std::cin >> key;
            if (key == "Save") {
                std::cin >> command;
                std::ofstream ofs(command.c_str(), std::ios::binary);
                tree.Serialize(ofs);
                std::cout << "OK" << std::endl;
            } else if (key == "Load") {
                std::cin >> command;
                std::ifstream ifs(command.c_str(), std::ios::binary);
                tree.Deserialize(ifs);
                std::cout << "OK" << std::endl;
            }
        } else if (command == "Print") {
            tree.Print();
        } else {
            unsigned long long *tempValue;
            for (auto &x: command) {
                x = (char) tolower(x);
            }
            if ((tempValue = tree.Find(command)) != nullptr) {
                std::cout << "OK: " << *tempValue << std::endl;
            } else {
                std::cout << "NoSuchWord" << std::endl;
            }
        }
    }
    return 0;
}