#include "SuffTree.h"

#include <utility>

/*!
 * Конструктор суффиксного дерева для строки s
 * @param s - исходная строка
 */
TSuffixTree::TSuffixTree(std::string s) :
        text(std::move(s)) {
    root = new Node(DEFAULT_VALUE, new int(DEFAULT_VALUE), false);
    active_node = root;
    global_end = DEFAULT_VALUE;
    active_edge = DEFAULT_VALUE; //activeEdge is represented as input string character index
    active_length = 0; //this tells how many characters we need to walk down for find symbol that needed
    suffixes_to_add = 0;
    for (int i = 0; i < text.size(); ++i) {
        insert(i);
    }
}

std::string
TSuffixTree::lexMinString() {
    std::string result_string;
    size_t length = (text.size() - 1) / 2;
    Node *next = root;
    while (result_string.size() < length) {
        auto it = next->children.begin();
        if (it->first == '$') {
            ++it;
        }
        next = it->second;
        for (int i = next->start; i <= *(next->end); ++i) {
            result_string += text[i];
            if (result_string.size() == length) {
                break;
            }
        }
    }
    return result_string;
}

/*!
 * Функция вставки суффикса, начинающегося в позиции pos
 * @param pos - позиция начала суффикса (0-индексация)
 */
void
TSuffixTree::insert(const int &text_position) {
    last_created_node = nullptr; /*indicating there is no internal node waiting for it's suffix link reset in current phase*/
    ++suffixes_to_add; //indicating that a new suffix ready to be added in tree
    ++global_end; //
    while (suffixes_to_add > 0) {
        //If activeLength is ZERO, set activeEdge to the current character
        if (active_length == 0) {
            active_edge = text_position;
        }
        // A new leaf edge gets created
        if (!active_node->children[text[active_edge]]) {
            active_node->children[text[active_edge]] = new Node(text_position, &global_end, true);
            if (last_created_node != nullptr) {
                last_created_node->suffix_link = active_node;
                last_created_node = nullptr;
            }
        } else {
            // Get the next node at the end of edge starting with activeEdge
            Node *next_node = active_node->children[text[active_edge]];
            int edge_length = *(next_node->end) - next_node->start + 1;
            //tricks
            if (active_length >= edge_length) {
                active_edge += edge_length;
                active_length -= edge_length;
                active_node = next_node;
                continue;
            }
            //(current character being processed is already on the edge
            if (text[next_node->start + active_length] == text[text_position]) {
                //If a newly created node waiting for it's suffix link to be set, then set suffix link of that waiting node to current active node
                if (last_created_node != nullptr) {
                    last_created_node->suffix_link = active_node;
                    last_created_node = nullptr;
                }
                ++active_length;
                break;
            }
            //new leaf edge and a new internal node get created - if there is no way, create a new nodes
            Node *to_add = new Node(next_node->start, new int(next_node->start + active_length - 1), false);
            active_node->children[text[active_edge]] = to_add;
            next_node->start += active_length;
            std::pair<char, Node *> first = std::make_pair(text[text_position],
                                                           new Node(text_position, &global_end, true));
            std::pair<char, Node *> second = std::make_pair(text[next_node->start], next_node);
            to_add->children.insert(first);
            to_add->children.insert(second);
            //suffixLink of lastNewNode points to current newly created internal node
            if (last_created_node != nullptr) {
                last_created_node->suffix_link = to_add;
            }
            last_created_node = to_add;
        }
        --suffixes_to_add; //decrement remaining suffixes because we finished inserting
        if (active_node == root && active_length > 0) {
            ++active_edge;
            --active_length;
        } else if (active_node != root) {
            active_node = active_node->suffix_link;
        }
    }
}

//std::string
//TSuffixTree::lexMinString(const size_t &n, const std::shared_ptr<TNode>& node)
//{
//	// конец рекурсии
//	if (n == 0){
//		return {};
//	}
//	int len = node->length();
//	if (len > n){
//		return text.substr(node->left, n);
//	} else {
//		return text.substr(node->left, len) + lexMinString(n - len, node->children.begin()->second);
//	}
//}
