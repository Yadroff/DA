#include <iostream>
#include <algorithm>
#include <chrono>

#define all(s) s.begin(), s.end()

int main() {
    auto startPoint = std::chrono::system_clock::now();
    std::string string;
    std::cin >> string;
    size_t n = string.size();
    std::string res(n, 'z');
    string += string;
    for (size_t start = 0; start < n; ++start) {
        std::string subStr = string.substr(start, n);
        if (subStr < res) {
            res = subStr;
        }
    }
//    std::cout << res << std::endl;
    auto endPoint = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count() << " ms"
              << std::endl;
}