#include <iostream>
#include <algorithm>
#include <vector>

#include "Graph.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
//    std::cout << "Hello, World!" << std::endl;
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adjacencyList(n);
    int from, to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        --from;
        --to;
        adjacencyList[from].emplace_back(to);
        adjacencyList[to].emplace_back(from);
    }
    Graph graph(n, adjacencyList);
//    auto startBFS = std::chrono::high_resolution_clock::now();
//    auto answer = graph.findConnectivityComponents();
//    for (auto &ans: answer) {
//        std::sort(ans.begin(), ans.end());
//    }
//    std::sort(answer.begin(), answer.end(),
//              [](const std::vector<int> &left, const std::vector<int> &right) { return left[0] < right[0]; });
//    for (const auto &ans: answer) {
//        for (const auto &vert: ans) {
//            std::cout << vert + 1 << " ";
//        }
//        std::cout << '\n';
//    }
//    auto endBFS = std::chrono::high_resolution_clock::now();
//    std::cout << "BFS TIME: " << std::chrono::duration_cast<std::chrono::microseconds>(endBFS - startBFS).count()
//              << "[microsec]" << std::endl;
//    auto startDFS = std::chrono::high_resolution_clock::now();
    auto answerDFS = graph.findConnectivityComponentsByDFS();
    for (auto &ans: answerDFS) {
        std::sort(ans.begin(), ans.end());
    }
    std::sort(answerDFS.begin(), answerDFS.end(),
              [](const std::vector<int> &left, const std::vector<int> &right) { return left[0] < right[0]; });
    for (const auto &ans: answerDFS) {
        for (const auto &vert: ans) {
            std::cout << vert + 1 << " ";
        }
        std::cout << '\n';
    }
//    auto endDFS = std::chrono::high_resolution_clock::now();
//    std::cout << "DFS TIME: " << std::chrono::duration_cast<std::chrono::microseconds>(endDFS - startDFS).count()
//              << "[microsec]" << std::endl;
    return 0;
}