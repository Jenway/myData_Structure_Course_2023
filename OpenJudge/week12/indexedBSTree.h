#include "arrayStack.h"
#include <iostream>

template <typename T>
class indexedNode {
public:
    T data;
    indexedNode* left;
    indexedNode* right;
    int leftSize;
};

template <typename T>
class indexedBSTree {
    using Node = indexedNode<T>;

private:
    int _size = 0;
    Node* root = nullptr;

    void erase(Node* node);
    T via_rank(int rank) const;

public:
    indexedBSTree() = default;
    ~indexedBSTree() = default;

    void insert(T data);
    Node* find_via_name(T data) const;
    void remove(T data);
    void find_via_rank(int rank);
    void remove_via_rank(int rank);
};

template <typename T>
void indexedBSTree<T>::insert(T data)
{
    int ret = 0; // xor
    Node *p = this->root, *q = nullptr;
    // std::stack<Node*> stk;
    ArrayStack<Node*> stk(this->_size);
    while (p != nullptr) {
        ret ^= p->data; // XOR
        q = p;
        if (data < p->data) {
            stk.push(p);
            p = p->left;
        } else if (data > p->data) {
            p = p->right;
        } else {
            std::cout << 0 << "\n"; // XOR
            return;
        }
    }

    std::cout << ret << "\n"; // XOR

    Node* newNode = new Node { data, nullptr, nullptr, 0 };
    this->_size++;

    if (this->root == nullptr) {
        this->root = newNode;
        return;
    } else if (data < q->data) {
        q->left = newNode;
    } else {
        q->right = newNode;
    }

    // UPDATE leftSize
    while (!stk.empty()) {
        p = stk.top();
        stk.pop();
        p->leftSize++;
    }

    return;
}

template <typename T>
void indexedBSTree<T>::erase(Node* node)
{
    // * 删除操作中，如果当前元素有两个孩子，替换的为 右子树中最小的
    //* 如果只有一个孩子，直接用该孩子替换当前元素
    //* 如果没有孩子，直接删除
    if (node == nullptr) {
        return;
    }
    // UPDATE leftSize
    Node *p = root, *q = nullptr;
    while (p != node) {
        q = p;
        if (node->data < p->data) {
            p->leftSize--;
            p = p->left;
        } else if (node->data > p->data) {
            p = p->right;
        } else {
            break;
        }
    }

    // 无孩子
    if (node->left == nullptr && node->right == nullptr) {
        if (q == nullptr) {
            root = nullptr;
        } else {
            q->left == node ? q->left = nullptr : q->right = nullptr;
        }
        delete node;
        node = nullptr;
    } else if (node->right == nullptr || node->left == nullptr) {
        // 有一个孩子
        Node* child = node->left == nullptr ? node->right : node->left;
        if (q == nullptr) {
            root = child;
        } else {
            q->left == node ? q->left = child : q->right = child;
        }
        delete node;
        node = nullptr;
    } else {
        // 有两个孩子
        Node* minRight = node->right;
        Node* minRightParent = node;
        int new_leftSize = node->leftSize;
        while (minRight->left != nullptr) {
            minRightParent = minRight;
            minRight = minRight->left;
            minRightParent->leftSize--;
        }
        if (q == nullptr) {
            root = minRight;
        } else {
            q->left == node ? q->left = minRight : q->right = minRight;
        }
        minRight->left = node->left;
        minRight->leftSize = new_leftSize;
        if (minRightParent != node) {
            minRightParent->left = minRight->right;
            minRight->right = node->right;
        }
        delete node;
        node = nullptr;
    }
    this->_size--;
    return;
}
// 查询与删除操作中，待查询的元素也需要异或入答案中
template <typename T>
typename indexedBSTree<T>::Node* indexedBSTree<T>::find_via_name(T data) const
{
    int ret = 0; // XOR

    Node* p = this->root;
    while (p != nullptr) {

        ret ^= p->data; // XOR

        if (data < p->data) {
            p = p->left;
        } else if (data > p->data) {
            p = p->right;
        } else {
            std::cout << ret << "\n"; // XOR
            return p;
        }
    }
    std::cout << 0 << "\n"; // XOR
    return nullptr;
}

template <typename T>
void indexedBSTree<T>::remove(T data)
{
    this->erase(this->find_via_name(data));
}

template <typename T>
T indexedBSTree<T>::via_rank(int rank) const
{
    // find-k-th-smallest-element
    Node* p = this->root;
    while (p != nullptr) {
        if (rank == p->leftSize + 1) {
            return p->data;
        } else if (rank <= p->leftSize) {
            p = p->left;
        } else {
            rank -= (p->leftSize + 1);
            p = p->right;
        }
    }
    return -1;
}

template <typename T>
void indexedBSTree<T>::find_via_rank(int rank)
{
    if (rank < 1 || rank > this->_size) {
        std::cout << 0 << "\n"; // XOR
        return;
    }

    this->find_via_name(via_rank(rank));
}

template <typename T>
void indexedBSTree<T>::remove_via_rank(int rank)
{
    if (rank < 1 || rank > this->_size) {
        std::cout << 0 << "\n"; // XOR
        return;
    }

    this->remove(via_rank(rank));
}
