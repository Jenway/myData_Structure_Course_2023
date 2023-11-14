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

template <typename T>
using my_Stack = ArrayStack<T>;

/*
 *创建二叉树类。二叉树的存储结构使用链表。提供操作:前序遍历、中序遍历、后序遍历、层次遍历、计算二叉树结点数目、计算二叉树高度。
 */

template <typename T>
class linkedBinaryTree {
public:
    typedef struct node {
        T data;
        node* left;
        node* right;
    } Node;
    linkedBinaryTree()
        : root { nullptr }
        , _size { 0 }
    {
    }
    ~linkedBinaryTree()
    {
        clear();
    }
    int size() const { return _size; }

    void input();

    void postOrder(void (*visit)(Node* node)) { postOrder(root, visit); }

    void buildTree(const int* preOrder, const int* inOrder, int n, int* inOrderIndex)
    {
        this->root = buildHelper(preOrder, 0, n - 1, inOrder, 0, n - 1, inOrderIndex);
    }

private:
    Node* root;
    int _size;

    void postOrder(Node* node, void (*visit)(Node* node));

    void clear()
    {
        postOrder(root, [](Node* node) { delete node; });
    }

    Node* buildHelper(const int* preOrder, int preStart, int preEnd, const int* inOrder, int inStart, int inEnd, int* inOrderIndex)
    {
        if (preStart > preEnd || inStart > inEnd) {
            return nullptr;
        }

        Node* root = new Node { preOrder[preStart], nullptr, nullptr };

        int index_in_inOrder = inOrderIndex[preOrder[preStart]];

        int leftTreeSize = index_in_inOrder - inStart;
        root->left = buildHelper(preOrder, preStart + 1, preStart + leftTreeSize, inOrder, inStart, index_in_inOrder - 1, inOrderIndex);
        root->right = buildHelper(preOrder, preStart + leftTreeSize + 1, preEnd, inOrder, index_in_inOrder + 1, inEnd, inOrderIndex);

        return root;
    }
};

using Stack = my_Stack<linkedBinaryTree<int>::Node*>;

template <typename T>
void linkedBinaryTree<T>::postOrder(Node* node, void (*visit)(Node* node))
{
    if (node == nullptr) {
        return;
    }
    Stack stack1, stack2;
    stack1.push(node);

    while (!stack1.empty()) {
        Node* temp = stack1.top();
        stack1.pop();
        stack2.push(temp);

        if (temp->left) {
            stack1.push(temp->left);
        }
        if (temp->right) {
            stack1.push(temp->right);
        }
    }

    while (!stack2.empty()) {
        Node* temp = stack2.top();
        stack2.pop();
        visit(temp);
    }
}

using namespace std;
using BinaryTree = linkedBinaryTree<int>;
using Node = BinaryTree::Node;

class Solution {
private:
    int n;
    int* preOrder;
    int* inOrder;
    int* inOrderIndex;
    BinaryTree* tree;

public:
    Solution(int num)
        : n { num }
        , preOrder { new int[n] }
        , inOrder { new int[n] }
        , inOrderIndex { new int[n + 1] { -1 } }
        , tree { new BinaryTree() }
    {
    }
    ~Solution()
    {
        delete tree;
    }
    void runTest();
};

void Solution::runTest()
{
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        preOrder[i] = temp;
    }
    for (int i = 0; i < n; i++) {
        cin >> temp;
        inOrder[i] = temp;
        inOrderIndex[temp] = i;
    }

    this->tree->buildTree(preOrder, inOrder, n, inOrderIndex);
    this->tree->postOrder([](BinaryTree::Node* node) { cout << node->data << " "; });
    cout << endl;
}

int main(void)
{
    int n;
    cin >> n;
    Solution* sol = new Solution(n);
    sol->runTest();
    delete sol;
    return 0;
}