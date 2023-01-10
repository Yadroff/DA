#ifndef SUFF_TREE_SUFFTREE_H
#define SUFF_TREE_SUFFTREE_H

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <map>

/*!
 * Класс суффиксного дерева. Конструируется из строки.
 */
class TSuffixTree {
public:
    explicit TSuffixTree(std::string s);

    std::string
    lexMinString();

    ~TSuffixTree() = default;

private:
    /*!
     * структура ребра суффиксного дерева.
     */
    struct Node {
        Node *suffix_link;
        int start;
        int *end;
        std::map<char, Node *> children;
        bool is_leaf;

        Node(int start, int *end, bool is_leaf) {
            this->start = start;
            this->end = end;
            suffix_link = nullptr;
            this->is_leaf = is_leaf;
        }

        ~Node() {
            for (auto &it: children) {
                delete (it.second);
            }
        }
    };

    void
    insert(const int &pos);

    Node *root;
    Node *active_node;
    Node *last_created_node;
    int active_edge;
    int active_length;
    int suffixes_to_add;
    std::string text;
    int global_end;
    static const int DEFAULT_VALUE = -1;
};

#endif //SUFF_TREE_SUFFTREE_H
