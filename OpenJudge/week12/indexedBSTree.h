#include <functional>
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
    void via_rank(std::function<void(T)> func, int rank);

public:
    indexedBSTree() = default;
    ~indexedBSTree() = default;

    void insert(T data);
    void find_via_name(T data);
    void remove(T data);
    void find_via_rank(int rank);
    void remove_via_rank(int rank);
};

template <typename T>
void indexedBSTree<T>::insert(T data)
{
    int ret = 0; // xor
    Node* p = this->root;
    Node* q = nullptr;
    while (p != nullptr) {
        q = p;
        ret ^= p->data; // XOR
        if (data < p->data) {
            p = p->left;
        } else if (data > p->data) {
            p = p->right;
        } else {
            std::cout << 0 << std::endl; // XOR
            return;
        }
    }

    std::cout << ret << std::endl; // XOR
    Node* newNode = new Node { data, nullptr, nullptr, 0 };
    if (q == nullptr) {
        this->root = newNode;
    } else if (data < q->data) {
        q->left = newNode;
    } else {
        q->right = newNode;
    }
    this->_size++;

    // UPDATE leftSize
    p = this->root;
    while (p != nullptr) {
        if (data < p->data) {
            p->leftSize++;
            p = p->left;
        } else if (data > p->data) {
            p = p->right;
        } else {
            break;
        }
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
        return;
    }
    // 有一个孩子
    if (node->right == nullptr) {
        if (q == nullptr) {
            root = node->left;
        } else {
            q->left == node ? q->left = node->left : q->right = node->left;
        }
        delete node;
        node = nullptr;
        return;
    }
    // 有两个孩子
    {
        Node* minRight = node->right;
        Node* minRightParent = node;
        while (minRight->left != nullptr) {
            minRightParent = minRight;
            minRight = minRight->left;
        }
        T temp = minRight->data;
        this->erase(minRight);
        node->data = temp;
        return;
    }
}

template <typename T>
void indexedBSTree<T>::remove(T data)
{
    // 查询与删除操作中，待查询的元素也需要异或入答案中
    int ret = 0; // xor
    Node *p = this->root, *q = nullptr;
    while (p != nullptr) {
        ret ^= p->data; // XOR
        if (data < p->data) {
            q = p;
            p = p->left;
        } else if (data > p->data) {
            q = p;
            p = p->right;
        } else {
            std::cout << ret << std::endl; // XOR
            this->erase(p);
            return;
        }
    }
    std::cout << 0 << std::endl; // XOR
}
template <typename T>
void indexedBSTree<T>::find_via_name(T data)
{
    // 查询与删除操作中，待查询的元素也需要异或入答案中
    int ret = 0; // xor
    Node* p = this->root;
    while (p != nullptr) {
        ret ^= p->data; // XOR
        if (data < p->data) {
            p = p->left;
        } else if (data > p->data) {
            p = p->right;
        } else {
            std::cout << ret << std::endl; // XOR
            return;
        }
    }
    std::cout << 0 << std::endl; // XOR
    return;
}

template <typename T>
void indexedBSTree<T>::find_via_rank(int rank)
{
    this->via_rank(std::bind(&indexedBSTree::find_via_name, this, std::placeholders::_1), rank);
}

template <typename T>
void indexedBSTree<T>::remove_via_rank(int rank)
{
    this->via_rank(std::bind(&indexedBSTree::remove, this, std::placeholders::_1), rank);
}

template <typename T>
void indexedBSTree<T>::via_rank(std::function<void(T)> func, int rank)
{
    if (rank < 1 || rank > this->_size) {
        std::cout << 0 << std::endl; // XOR
        return;
    }

    Node* p = this->root;

    while (p != nullptr) {
        if (rank == p->leftSize + 1) {
            func(p->data);
            return;
        } else if (rank < p->leftSize + 1) {
            p = p->left;
        } else {
            rank -= p->leftSize + 1;
            p = p->right;
        }
    }

    return;
}