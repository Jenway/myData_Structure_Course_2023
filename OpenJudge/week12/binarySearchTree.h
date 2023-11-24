#include "linkedBinaryTree.h"
#include <iostream>

template <typename K, typename E>
class binarySearchTree : public linkedBinaryTree<Pair<K, E>> {
    using Node = node<Pair<K, E>>;

public:
    bool empty() const { return this->_size == 0; }
    int size() const { return this->_size; }
    Pair<K, E>* find(const K& theKey) const;
    void insert(const Pair<K, E>& thePair);
    void erase(const K& theKey);

    void ascend() const
    {
        this->inOrder([](Node* node) { std::cout << node->data.second << " "; });
    }
};

template <typename K, typename E>
Pair<K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{
    Node* p = this->root;
    while (p != nullptr) {
        if (theKey < p->data.first) {
            p = p->left;
        } else if (theKey > p->data.first) {
            p = p->right;
        } else {
            return &p->data;
        }
    }
    return nullptr;
}

template <typename K, typename E>
void binarySearchTree<K, E>::insert(const Pair<K, E>& thePair)
{
    Node* p = this->root;
    Node* q = nullptr;
    while (p != nullptr) {
        q = p;
        if (thePair.first < p->data.first) {
            p = p->left;
        } else if (thePair.first > p->data.first) {
            p = p->right;
        } else {
            p->data.second = thePair.second;
            return;
        }
    }

    Node* newNode = new Node { thePair, nullptr, nullptr };
    if (q == nullptr) {
        this->root = newNode;
    } else if (thePair.first < q->data.first) {
        q->left = newNode;
    } else {
        q->right = newNode;
    }
    this->_size++;
}

template <typename K, typename E>
void binarySearchTree<K, E>::erase(const K& theKey)
{
    Node* p = this->root;
    Node* q = nullptr;
    while (p != nullptr) {
        if (theKey < p->data.first) {
            q = p;
            p = p->left;
        } else if (theKey > p->data.first) {
            q = p;
            p = p->right;
        } else {
            break;
        }
    }

    if (p == nullptr) {
        return;
    }

    if (p->left == nullptr && p->right == nullptr) {
        // 无孩子
        if (q == nullptr) {
            this->root = nullptr;
        } else if (q->left == p) {
            q->left = nullptr;
        } else {
            q->right = nullptr;
        }
        delete p;
    } else if (p->left != nullptr && p->right != nullptr) {
        // 有两个孩子
        Node* r = p->right;
        Node* s = p;
        while (r->left != nullptr) {
            s = r;
            r = r->left;
        }
        p->data = r->data;
        if (s == p) {
            s->right = r->right;
        } else {
            s->left = r->right;
        }
        delete r;
    } else {
        // 有一个孩子
        Node* child = p->left != nullptr ? p->left : p->right;
        if (q == nullptr) {
            this->root = child;
        } else if (q->left == p) {
            q->left = child;
        } else {
            q->right = child;
        }
        delete p;
    }
    this->_size--;
}

