#if !defined(__ARRAYSTACK_H__)
#define __ARRAYSTACK_H__
#include <iostream>

template <typename T>
class ArrayStack {
private:
    T* data;
    int _top;
    int _size;

    bool isFull();
    void resize(int newSize);

public:
    ArrayStack()
        : ArrayStack(100)
    {
    }
    ArrayStack(int size);
    ~ArrayStack();

    ArrayStack(const ArrayStack& other) = delete;
    ArrayStack& operator=(const ArrayStack& other) = delete;
    ArrayStack& operator=(ArrayStack&& other);
    ArrayStack(ArrayStack&& other);

    void push(T& item);
    void push(T&& item);
    void pop();

    bool empty() const;
    size_t size() const;

    T& top();

    // for debug
    void print();
};

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack&& other)
{
    data = other.data;
    _top = other._top;
    _size = other._size;
    other.data = nullptr;
    other._top = -1;
    other._size = 0;
    return *this;
}
template <typename T>
ArrayStack<T>::ArrayStack(ArrayStack&& other)
{
    *this = std::move(other);
}

template <typename T>
ArrayStack<T>::ArrayStack(int size)
    : _size(size)
{
    data = new T[size];
    _top = -1;
}

template <typename T>
ArrayStack<T>::~ArrayStack()
{
    delete[] data;
}

template <typename T>
void ArrayStack<T>::resize(int newSize)
{
    T* newData = new T[newSize];
    for (int i = 0; i < _size; i++) {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    _size = newSize;
}

template <typename T>
size_t ArrayStack<T>::size() const
{
    return _size;
}

template <typename T>
void ArrayStack<T>::push(T& item)
{
    if (isFull()) {
        resize(_size * 2);
    }
    data[++_top] = item;
}

template <typename T>
void ArrayStack<T>::push(T&& item)
{
    if (isFull()) {
        resize(_size * 2);
    }
    data[++_top] = std::move(item);
}

template <typename T>
void ArrayStack<T>::pop()
{
    if (empty()) {
        throw "ArrayStack is empty";
    } else {
        --_top;
    }
}

template <typename T>
bool ArrayStack<T>::empty() const
{
    return _top == -1;
}

template <typename T>
bool ArrayStack<T>::isFull()
{
    return _top == _size - 1;
}

template <typename T>
T& ArrayStack<T>::top()
{
    if (empty()) {
        throw "ArrayStack is empty";
    } else {
        return data[_top];
    }
}

template <typename T>
void ArrayStack<T>::print()
{
    for (int i = 0; i <= _top; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;
}
#endif // __ARRAYSTACK_H__
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

using namespace std;

/*
* 创建带索引的二叉搜索树类。存储结构使用链表，提供操作:插入、删除、按名次删除、查找、按名次查找、升序输出所有元素。
格式
*输入格式
输入第一行一个数字 m (m<=1000000)，表示有 m 个操作。
*接下来 m 行，每一行有两个数字 a，b：

*当输入的第一个数字 a 为 0 时，输入的第二个数字 b 表示向搜索树中插入 b
*当输入的第一个数字 a 为 1 时，输入的第二个数字 b 表示向搜索树中查找 b
*当输入的第一个数字 a 为 2 时，输入的第二个数字 b 表示向搜索树中删除 b
*当输入的第一个数字 a 为 3 时，输入的第二个数字 b 表示查找搜索树中名次为 b 的元素
*当输入的第一个数字 a 为 4 时，输入的第二个数字 b 表示删除搜索树中名次为 b 的元素

输出格式
*对于输入中的每一种操作，输出执行操作的过程中依次比较的元素值的异或值。

注意

* 查询与删除操作中，待查询的元素也需要异或入答案中
* 查找（删除）操作中，如果未找到，或者插入操作，已存在，输出 0（不插入），不需要输出异或和
* 查找（删除）第 b 大，如果不存在，输出 0
* 删除操作中，如果当前元素有两个孩子，替换的为 右子树中最小的，如果只有一个孩子，直接用该孩子替换当前元素，如果没有孩子，直接删除
* 删除操作的替换过程中所有比较操作不计入答案
*/

class Solution {
private:
    int n;
    indexedBSTree<int> bst;

public:
    Solution(int n)
        : n(n)
    {
    }
    void runTest()
    {
        int a, b;
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            enum options { INSERT = 0,
                FIND_VIA_NAME,
                DELETE_VIA_NAME,
                FIND_VIA_RANK,
                DELETE_VIA_RANK };
            switch (a) {
            case INSERT:
                bst.insert(b);
                break;
            case FIND_VIA_NAME:
                bst.find_via_name(b);
                break;
            case DELETE_VIA_NAME:
                bst.remove(b);
                break;
            case FIND_VIA_RANK:
                bst.find_via_rank(b);
                break;
            case DELETE_VIA_RANK:
                bst.remove_via_rank(b);
                break;
            default:
                break;
            }
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m;
    cin >> m;
    Solution sol { Solution(m) };
    sol.runTest();
    return 0;
}