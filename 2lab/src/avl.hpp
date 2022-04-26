#ifndef AVL_H
#define AVL_H

#include <fstream>
#include <iostream>
#include <cstring>

template<typename K, typename T>
class TAVL {
private:

    struct TNode {
        K Key;
        T Value;
        TNode *Left, *Right;
        short Height;

        TNode(const K &k, const T &v) {
            Key = k;
            Value = v;
            Left = Right = nullptr;
            Height = 1;
        }
    };

    TNode *Root;

    TNode *FindTree(TNode *tree, const K &k) {
        while (tree != nullptr) {
            if (k > tree->Key) {
                tree = tree->Right;
            } else if (k < tree->Key) {
                tree = tree->Left;
            } else {
                return tree;
            }
        }
        return tree;
    }

    TNode *InsertNode(TNode *tree, TNode *ins) {
        if (tree == nullptr) {
            return ins;
        }
        if (ins->Key < tree->Key) {
            TNode *temp = InsertNode(tree->Left, ins);
            if (temp == nullptr)
                return nullptr;
            tree->Left = temp;
        } else if (ins->Key > tree->Key) {
            TNode *temp = InsertNode(tree->Right, ins);
            if (temp == nullptr)
                return nullptr;
            tree->Right = temp;
        } else {
            return nullptr;
        }
        FixHeight(tree);
        return Balance(tree);
    }

    TNode *RemoveNode(TNode *tree, const K &key) {
        if (tree == nullptr) {
            return nullptr;
        }
        if (key < tree->Key) {
            TNode *temp = RemoveNode(tree->Left, key);
            tree->Left = temp;
        } else if (key > tree->Key) {
            TNode *temp = RemoveNode(tree->Right, key);
            tree->Right = temp;
        } else {
            if (tree->Right == nullptr) {
                TNode *temp = tree->Left;
                delete tree;
                return temp;
            } else if (tree->Left == nullptr) {
                TNode *temp = tree->Right;
                delete tree;
                return temp;
            } else {
                TNode *m = Min(tree->Right);
                tree->Key = m->Key;
                tree->Value = m->Value;
                tree->Right = RemoveMin(tree->Right);
                delete m;
            }
        }
        FixHeight(tree);
        return Balance(tree);
    }

    void Print(TNode *tree, int tab) {
        const int TAB_INCR = 4;
        if (tree == nullptr) {
            return;
        }
        Print(tree->Right, tab + TAB_INCR);
        for (int i = 0; i < tab; ++i) {
            std::cout << ' ';
        }
        std::cout <<
                  // tree->Key <<
                  "< " << tree->Key << ", " << tree->Value << " >" <<
                  // "(h:" << tree->GetHeight << ")" <<
                  // "(bf:" << BFactor(tree) << ")" <<
                  std::endl;
        Print(tree->Left, tab + TAB_INCR);
    }

    TNode *Min(TNode *tree) {
        while (tree->Left != nullptr) {
            tree = tree->Left;
        }
        return tree;
    }

    TNode *RemoveMin(TNode *tree) {
        if (tree->Left == nullptr) {
            return tree->Right;
        }
        tree->Left = RemoveMin(tree->Left);
        return Balance(tree);
    }

    TNode *RightRotate(TNode *tree) {
        TNode *temp = tree->Left;
        tree->Left = temp->Right;
        temp->Right = tree;
        FixHeight(tree);
        FixHeight(temp);
        return temp;
    }

    TNode *LeftRotate(TNode *tree) {
        TNode *temp = tree->Right;
        tree->Right = temp->Left;
        temp->Left = tree;
        FixHeight(tree);
        FixHeight(temp);
        return temp;
    }

    TNode *Balance(TNode *tree) {
        short bf = BFactor(tree);
        if (bf < -1) {
            if (BFactor(tree->Left) > 0) {
                tree->Left = LeftRotate(tree->Left);
            }
            tree = RightRotate(tree);
        } else if (bf > 1) {
            if (BFactor(tree->Right) < 0) {
                tree->Right = RightRotate(tree->Right);
            }
            tree = LeftRotate(tree);
        }
        FixHeight(tree);
        return tree;
    }

    inline short Max(short a, short b) {
        return a > b ? a : b;
    }

    inline short GetHeight(TNode *tree) {
        return tree == nullptr ? 0 : tree->Height;
    }

    void FixHeight(TNode *tree) {
        tree->Height = Max(GetHeight(tree->Left), GetHeight(tree->Right)) + 1;
    }

    inline short BFactor(TNode *tree) {
        return GetHeight(tree->Right) - GetHeight(tree->Left);
    }

    void DeleteTree(TNode *tree) {
        if (tree == nullptr)
            return;
        DeleteTree(tree->Left);
        DeleteTree(tree->Right);
        delete tree;
    }

    void SerializeRecursive(TNode *tree, std::ofstream &ofs) {
        bool isEmpty = tree == nullptr;
        ofs.write((char *) &isEmpty, sizeof(bool));
        if (isEmpty) {
            return;
        }
        size_t size = tree->Key.size();
        ofs.write((char *) &size, sizeof(size_t));
        ofs.write(tree->Key.c_str(), sizeof(char) * size);
        ofs.write((char *) &tree->Value, sizeof(T));
        ofs.write((char *) &tree->Height, sizeof(short));
        SerializeRecursive(tree->Left, ofs);
        SerializeRecursive(tree->Right, ofs);
    }

    TNode *DeserializeRecursive(std::ifstream &is) {
        bool isEmpty;
        is.read((char *) &isEmpty, sizeof(bool));
        if (isEmpty) {
            return nullptr;
        }
        size_t size;
        is.read((char *) &size, sizeof(size_t));
        char *buffer = new char[size];
        is.read(buffer, sizeof(char) * size);
        K key;
        key.resize(size);
        for (size_t i = 0; i < size; ++i) {
            key[i] = buffer[i];
        }
        delete[] buffer;
        T value;
        is.read((char *) &value, sizeof(T));
        short height;
        is.read((char *) &height, sizeof(short));
        auto *newNode = new TNode(key, value);
        newNode->Height = height;
        newNode->Left = DeserializeRecursive(is);
        newNode->Right = DeserializeRecursive(is);
        return newNode;
    }

public:
    void Swap(TAVL<K, T> &other) {
        TNode *temp = Root;
        Root = other.Root;
        other.Root = temp;
    }

    void Deserialize(std::ifstream &is) {
        Root = DeserializeRecursive(is);
    }

    void Serialize(std::ofstream &ofs) {
        SerializeRecursive(Root, ofs);
    }

    T *Find(const K &k) {
        TNode *temp = FindTree(Root, k);
        return temp == nullptr ? nullptr : &(temp->Value);
    }

    TAVL() {
        Root = nullptr;
    }

    ~TAVL() {
        DeleteTree(Root);
    }

    int Insert(const K &k, const T &v) {
        if (FindTree(Root, k) != nullptr) {
            return 0;
        }
        Root = InsertNode(Root, new TNode(k, v));
        return 1;
    }

    int Remove(const K &k) {
        if (FindTree(Root, k) == nullptr) {
            return 0;
        }
        Root = RemoveNode(Root, k);
        return 1;
    }

    int Empty() {
        return Root == nullptr;
    }

    void Print() {
        Print(Root, 0);
    }
};

#endif