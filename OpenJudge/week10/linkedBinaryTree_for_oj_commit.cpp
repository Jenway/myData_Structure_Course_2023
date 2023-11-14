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
class ArrayQueue {
private:
    T* data;
    int _size;
    int capacity;
    int _front;
    int _back;

    void resize(int newCapacity);
    int nextIndex(int index);

public:
    ArrayQueue()
        : _size(0)
        , capacity(10)
        , _front(0)
        , _back(0)
    {
        data = new T[capacity];
    }
    ~ArrayQueue()
    {
        delete[] data;
    }
    void push(const T& val);
    void pop();
    T& front() { return data[_front]; }
    int size() const { return _size; }
    bool empty() const { return _size == 0; }
};

template <typename T>
void ArrayQueue<T>::push(const T& val)
{
    if (_size == capacity) {
        resize(capacity * 2);
    }
    data[_back] = val;
    _back = nextIndex(_back);
    _size++;
}

template <typename T>
void ArrayQueue<T>::pop()
{
    if (_size == 0) {
        throw "pop from empty queue";
    } else {
        _front = nextIndex(_front);
        _size--;
    }
}

template <typename T>
void ArrayQueue<T>::resize(int newCapacity)
{
    if (newCapacity == _size) {
        return;
    } else if (newCapacity < _size) {
        return; // tobe done
    } else {
        T* new_data = new T[newCapacity];
        for (int i = 0; i < _size; i++) {
            new_data[i] = data[(_front + i) % _size];
        }
        delete[] data;
        data = new_data;
        _front = 0;
        _back = _size;
        capacity = newCapacity;
    }
}

template <typename T>
int ArrayQueue<T>::nextIndex(int index)
{
    return (index + 1) % capacity;
}

template <typename K, typename E>
struct Pair {
    K first;
    E second;
};

#include <iostream>

using std::cin;

template <typename T>
using my_Queue = ArrayQueue<T>;

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
        , nodeIndex { nullptr }
    {
    }
    ~linkedBinaryTree()
    {
        clear();
    }
    int size() const { return _size; }

    void input();

    void preOrder(void (*visit)(Node* node)) { preOrder(root, visit); }
    void inOrder(void (*visit)(Node* node)) { inOrder(root, visit); }
    void postOrder(void (*visit)(Node* node)) { postOrder(root, visit); }
    void levelOrder(void (*visit)(Node* node)) { levelOrder(root, visit); }

    void count_all();
    void height_all();

private:
    Node* root;
    int _size;
    Node** nodeIndex;

    void preOrder(Node* node, void (*visit)(Node* node));
    void inOrder(Node* node, void (*visit)(Node* node));
    void postOrder(Node* node, void (*visit)(Node* node));
    void levelOrder(Node* node, void (*visit)(Node* node));

    Node* find(int i)
    {
        if (i > _size) {
            return nullptr;
        } else {
            return nodeIndex[i];
        }
    }
    int count(Node* node);
    int height(Node* node);

    void clear()
    {
        postOrder(root, [](Node* node) { delete node; });
    }
};

using Queue = my_Queue<linkedBinaryTree<int>::Node*>;
using Stack = my_Stack<linkedBinaryTree<int>::Node*>;

template <typename T>
void linkedBinaryTree<T>::input()
{
    /*
     * 第一行为一个数字 n(10 <= n <= 100000)，表示有这棵树有 n 个节点，内容为 1 ~n
     * 之后 n 行每行两个数字，第 i 行的两个数字 a、b 表示内容为 i 的节点的左孩子节点的内容为 a，右孩子节点的内容为 b，
     * -1 表示该位置没有节点。保证数据有效，根节点内容为 1
     */
    Queue q;
    int n;
    cin >> n;
    this->_size = n;
    nodeIndex = new Node*[n + 1];
    this->root = new Node { 1, nullptr, nullptr };
    nodeIndex[1] = root;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        Node* it = find(i);
        if (it != nullptr) {
            if (a != -1) {
                it->left = new Node { a, nullptr, nullptr };
                nodeIndex[a] = it->left;
            }
            if (b != -1) {
                it->right = new Node { b, nullptr, nullptr };
                nodeIndex[b] = it->right;
            }
        }
    }
}

template <typename T>
void linkedBinaryTree<T>::preOrder(Node* node, void (*visit)(Node* node))
{
    if (node != nullptr) {
        visit(node);
        preOrder(node->left, visit);
        preOrder(node->right, visit);
    }
}

template <typename T>
void linkedBinaryTree<T>::inOrder(Node* node, void (*visit)(Node* node))
{
    Stack stack;
    Node* current = node;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        visit(current);

        current = current->right;
    }
}

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

template <typename T>
void linkedBinaryTree<T>::levelOrder(Node* node, void (*visit)(Node* node))
{
    Queue q;
    while (node != nullptr) {
        visit(node);
        if (node->left != nullptr) {
            q.push(node->left);
        }
        if (node->right != nullptr) {
            q.push(node->right);
        }
        if (q.empty()) {
            node = nullptr;
        } else {
            node = q.front();
            q.pop();
        }
    }
}

template <typename T>
void linkedBinaryTree<T>::count_all()
{

    for (int i = 1; i <= size(); i++) {
        std::cout << count(find(i)) << " ";
    }
    std::cout << std::endl;
}

template <typename T>
int linkedBinaryTree<T>::count(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        return 1 + count(node->left) + count(node->right);
    }
}

template <typename T>
void linkedBinaryTree<T>::height_all()
{
    for (int i = 1; i <= size(); i++) {
        std::cout << height(find(i)) << " ";
    }
    std::cout << std::endl;
}

template <typename T>
int linkedBinaryTree<T>::height(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        int left = height(node->left);
        int right = height(node->right);
        return 1 + (left > right ? left : right);
    }
}

using namespace std;
using BinaryTree = linkedBinaryTree<int>;

class Solution {
private:
    BinaryTree* tree;

public:
    Solution()
        : tree { new BinaryTree() }
    {
    }
    ~Solution()
    {
        delete tree;
    }
    void runTest()
    {
        /*
        *格式
        *输入格式
        *第一行为一个数字 n (10<=n<=100000)，表示有这棵树有 n 个节点，编号为 1~n。
        *之后 n 行每行两个数字，第 i 行的两个数字 a、b 表示编号为 i 的节点的左孩子节点为 a，右孩子节点为 b，-1 表示该位置没有节点。
        *保证数据有效，根节点为 1。

        *输出格式
        *第一行，n 个数字，表示该树的前序遍历。
        *第二行，n 个数字，表示该树的中序遍历。
        *第三行，n 个数字，表示该树的后序遍历
        *第四行，n 个数字，表示该树的层次遍历。
        *第五行，n 个数字，第 i 个数字表示以 i 节点为根的子树的节点数目。
        *第六行，n 个数字，第 i 个数字表示以 i 节点为根的子树的高度。
        */
        auto output = [](BinaryTree::Node* node) { cout << node->data << " "; };
        this->tree->input();
        this->tree->preOrder(output);
        cout << endl;
        this->tree->inOrder(output);
        cout << endl;
        this->tree->postOrder(output);
        cout << endl;
        this->tree->levelOrder(output);
        cout << endl;
        this->tree->count_all();
        this->tree->height_all();
    }
};

int main(void)
{
    Solution* sol = new Solution();
    sol->runTest();
    delete sol;
    return 0;
}