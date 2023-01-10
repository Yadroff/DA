#ifndef SRC_GRAPH_H
#define SRC_GRAPH_H

#include <vector>

class Graph {
public:
    Graph(const int &n, const std::vector<std::vector<int>> &list);

    [[nodiscard]] std::vector<std::vector<int>> findConnectivityComponents() const;

    [[nodiscard]] std::vector<std::vector<int>> findConnectivityComponentsByDFS() const;

private:
    void DFS(const int &n, std::vector<bool> &used, std::vector<int> &component) const;

    static bool hasUnused(const std::vector<bool> &used);

    int n_;
    std::vector<std::vector<int>> adjacencyList_;
};


#endif //SRC_GRAPH_H
