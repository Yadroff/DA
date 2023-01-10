#include "Graph.h"

#include <algorithm>
#include <queue>

Graph::Graph(const int &n, const std::vector<std::vector<int>> &list) : n_(n), adjacencyList_(list) {}


std::vector<std::vector<int>> Graph::findConnectivityComponents() const {
    std::vector<bool> used(n_, false);
    std::vector<std::vector<int>> answer;
    std::vector<int> new_component;
    std::queue<int> queue;
    int last = 0;
    do {
        new_component.clear();
        int n = 0;
        for (int i = last; i < n_; ++i) { // выбираем вершину, с которой будем начинать поиск в глубину
            if (!used[i]) {
                n = i;
                break;
            }
        }
        last = n;
        new_component.emplace_back(n);
        used[n] = true;
        queue.emplace(n);
        while (!queue.empty()) {
            int vert = queue.front();
            queue.pop();
            for (const auto &to: adjacencyList_[vert]) {
                if (!used[to]) {
                    queue.emplace(to);
                    used[to] = true;
                    new_component.emplace_back(to);
                }
            }
        }
        answer.emplace_back(new_component);
    } while (hasUnused(used));
    return answer;
}

bool Graph::hasUnused(const std::vector<bool> &used) {
    if (std::any_of(used.begin(), used.end(), [](const bool &ok) { return !ok; })) {
        return true;
    }
    return false;
}

std::vector<std::vector<int>> Graph::findConnectivityComponentsByDFS() const {
    std::vector<bool> used(n_, false);
    std::vector<std::vector<int>> answer;
    std::vector<int> new_component;
    int last = 0;
    int n = 0;
    do {
        new_component.clear();
        for (int i = last; i < n_; ++i) {
            if (!used[i]) {
                n = i;
                break;
            }
        }
        last = n;
        DFS(n, used, new_component);
        answer.emplace_back(new_component);
    } while (hasUnused(used));
    return answer;
}

void Graph::DFS(const int &n, std::vector<bool> &used, std::vector<int> &component) const {
    used[n] = true;
    component.emplace_back(n);
    for (const auto &vert: adjacencyList_[n]) {
        if (!used[vert]) {
            DFS(vert, used, component);
        }
    }
}