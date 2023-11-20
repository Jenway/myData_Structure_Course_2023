// other s ide of the sea...
#if !defined(ARRAYDEQUE_H)
#define ARRAYDEQUE_H

// Double-ended queue implemented with a circular array
#include <iostream>

template <typename T>
class ArrayDeque {
private:
    int capacity;
    int _front;
    int _rear;
    int _size;
    T* data;

    void resize();
    void resize(int newCapacity);
    int prevIndex(int index) const { return (index - 1 + capacity) % capacity; }
    int nextIndex(int index) const { return (index + 1) % capacity; }

public:
    ArrayDeque(int capacity = 10)
        : capacity { capacity }
        , _front { 0 }
        , _rear { 0 }
        , _size { 0 }
        , data { new T[capacity] {} }
    {
    }
    ~ArrayDeque()
    {
        delete[] data;
        clear();
    }
    void push_front(T& e)
    {
        this->_front = prevIndex(this->_front);
        this->data[this->_front] = e;
        _size++;
        resize();
    }
    void push_back(T& e)
    {
        this->data[this->_rear] = e;
        this->_rear = nextIndex(this->_rear);
        _size++;
        resize();
    }
    void push_back(const T& e)
    {
        this->data[this->_rear] = e;
        this->_rear = nextIndex(this->_rear);
        _size++;
        resize();
    }
    void push_front(T&& e)
    {
        this->push_front(std::forward<T>(e));
    }

    void push_back(T&& e)
    {
        this->push_back(std::forward<T>(e));
    }

    void pop_front()
    {
        this->_front = nextIndex(this->_front);
        _size--;
        resize();
    }
    void pop_back()
    {
        this->_rear = prevIndex(this->_rear);
        _size--;
        resize();
    }

    T& front()
    {
        if (_size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        int firstIndex = this->_front;
        return this->data[firstIndex];
    }
    T& back()
    {
        if (_size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        int lastIndex = prevIndex(this->_rear);
        return this->data[lastIndex];
    }
    T& operator[](int index)
    {
        if (index < 0 || index > _size) {
            std::cout << "index: " << index << std::endl;
            throw std::out_of_range("Index out of range");
        }

        return this->data[(this->_front + index) % capacity];
    }
    int size() const { return this->_rear - this->_front; }
    bool empty() const { return _size == 0; }
    bool isFull() const { return size() == capacity; }
    void clear() { this->_front = this->_rear = 0; }
};

template <typename T>
void ArrayDeque<T>::resize()
{
    if (size() == capacity - 1) {
        resize(capacity * 2);
    } else if (size() < capacity / 4 && capacity / 2 >= 10) {
        resize(capacity / 2);
    }
}

template <typename T>
void ArrayDeque<T>::resize(int newCapacity)
{
    T* newData = new T[newCapacity];
    for (int i = 0; i < size(); i++) {
        newData[i] = data[(i + _front) % capacity];
    }
    delete[] data;
    data = newData;
    _front = 0;
    _rear = size();
    capacity = newCapacity;
}

#endif // ARRAYDEQUE_H
#if !defined(ARRAYQUEUE_H)
#define ARRAYQUEUE_H
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

#endif // ARRAYQUEUE_H
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
using vector = ArrayDeque<T>;

template <typename T>
class less {
public:
    bool operator()(const T& lhs, const T& rhs) { return lhs < rhs; }
};
template <typename T>
class greater {
public:
    bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

template <typename T, typename Compare = less<T>> // default is less
class PriorityQueue {
private:
    vector<T> heap;
    Compare cmp;

    void percolateDown(int hole);

public:
    PriorityQueue() = default;
    PriorityQueue(const PriorityQueue& rhs) = default;
    PriorityQueue(PriorityQueue&& rhs) = default;
    PriorityQueue& operator=(const PriorityQueue& rhs) = default;
    PriorityQueue& operator=(PriorityQueue&& rhs) = default;
    ~PriorityQueue() = default;

    template <typename InputIterator>
    PriorityQueue(InputIterator first, InputIterator last, Compare cmp = Compare())
        : heap(first, last)
        , cmp(cmp)
    {
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            percolateDown(i);
        }
    }

    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); }
    T& top() { return this->heap[0]; }

    void push(T& x);
    void push(T&& x);
    void pop();
};

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::percolateDown(int hole)
{
    T tmp = std::move(heap[hole]);

    for (int child = hole * 2 + 1; child < heap.size(); hole = child, child = hole * 2 + 1) {
        if (child != heap.size() - 1 && cmp(heap[child + 1], heap[child])) {
            ++child;
        }
        if (cmp(heap[child], tmp)) {
            heap[hole] = std::move(heap[child]);
        } else {
            break;
        }
    }
    heap[hole] = std::move(tmp);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(T& x)
{
    heap.push_back(x);
    int hole = heap.size() - 1;
    for (; hole > 0 && cmp(x, heap[(hole - 1) / 2]); hole = (hole - 1) / 2) {
        heap[hole] = std::move(heap[(hole - 1) / 2]);
    }
    heap[hole] = x;
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(T&& x)
{
    heap.push_back(std::move(x));
    int hole = heap.size() - 1;
    for (; hole > 0 && cmp(heap[hole], heap[(hole - 1) / 2]); hole = (hole - 1) / 2) {
        heap[hole] = std::move(heap[(hole - 1) / 2]);
    }
    heap[hole] = std::move(x);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::pop()
{
    heap[0] = std::move(heap.back());
    heap.pop_back();
    percolateDown(0);
}

template <typename T, typename Compare>
void heapSort(T* a, int n, Compare cmp = Compare())
{
    for (int i = n / 2 - 1; i >= 0; --i) {
        T tmp = std::move(a[i]);
        int child;
        int hole = i;
        for (; hole * 2 + 1 < n; hole = child) {
            child = hole * 2 + 1;
            if (child != n - 1 && cmp(a[child + 1], a[child])) {
                ++child;
            }
            if (cmp(a[child], tmp)) {
                a[hole] = std::move(a[child]);
            } else {
                break;
            }
        }
        a[hole] = std::move(tmp);
    }
    for (int i = n - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        T tmp = std::move(a[0]);
        int child;
        int hole = 0;
        for (; hole * 2 + 1 < i; hole = child) {
            child = hole * 2 + 1;
            if (child != i - 1 && cmp(a[child + 1], a[child])) {
                ++child;
            }
            if (cmp(a[child], tmp)) {
                a[hole] = std::move(a[child]);
            } else {
                break;
            }
        }
        a[hole] = std::move(tmp);
    }
}

#include <iostream>

template <typename K, typename E>
struct Pair {
    K first;
    E second;
};

template <typename T>
using my_Queue = ArrayQueue<T>;

template <typename T>
using my_Stack = ArrayStack<T>;

template <typename T>
struct node {
    T data;
    node* left;
    node* right;
};

template <typename T, typename Node = node<T>>
class linkedBinaryTree {
    using Queue = my_Queue<Node*>;
    using Stack = my_Stack<Node*>;

public:
    linkedBinaryTree()
        : root { nullptr }
        , _size { 0 }
        , nodeIndex { nullptr }
    {
    }
    linkedBinaryTree(Node* root)
        : root { root }
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::preOrder(Node* node, void (*visit)(Node* node))
{
    if (node != nullptr) {
        visit(node);
        preOrder(node->left, visit);
        preOrder(node->right, visit);
    }
}

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::inOrder(Node* node, void (*visit)(Node* node))
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::postOrder(Node* node, void (*visit)(Node* node))
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::levelOrder(Node* node, void (*visit)(Node* node))
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::count_all()
{

    for (int i = 1; i <= size(); i++) {
        std::cout << count(find(i)) << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename Node>
int linkedBinaryTree<T, Node>::count(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        return 1 + count(node->left) + count(node->right);
    }
}

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::height_all()
{
    for (int i = 1; i <= size(); i++) {
        std::cout << height(find(i)) << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename Node>
int linkedBinaryTree<T, Node>::height(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        int left = height(node->left);
        int right = height(node->right);
        return 1 + (left > right ? left : right);
    }
}

#if !defined(__STRING_H__)
#define __STRING_H__
#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

constexpr int BUFFER_SIZE = 9024000; // Jesus that is a big buffer to pass the online judge

class my_string {
private:
    char* data;
    size_t length;

    static int my_strlen(const char* str);
    static void my_strcpy(char* dst, const char* src);

public:
    class iterator {
    private:
        char* ptr;

    public:
        iterator(char* ptr)
            : ptr(ptr)
        {
        }
        iterator& operator++()
        {
            ptr++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }
        iterator& operator--()
        {
            ptr--;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            --*this;
            return temp;
        }
        char& operator*() { return *ptr; }
        bool operator==(const iterator& it) { return ptr == it.ptr; }
        bool operator!=(const iterator& it) { return ptr != it.ptr; }
    };
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + length); }

    my_string(const char* str = nullptr);
    my_string& operator=(const char* str);

    my_string(const my_string& str);
    my_string& operator=(const my_string& str);

    ~my_string() { delete[] data; }

    int toInt();

    bool operator==(const my_string& str) const;
    char& operator[](int n) const;

    size_t size() const { return length; }
    const char* c_str() const { return data; }

    friend istream& operator>>(istream& is, my_string& str);
    friend ostream& operator<<(ostream& os, my_string& str);

    friend my_string operator+(const my_string& lhs, const my_string& rhs);
};

my_string::my_string(const char* str)
{
    if (str == nullptr) {
        length = 0;
        data = new char[1];
        *data = '\0';
    } else {
        length = my_strlen(str);
        data = new char[length + 1];
        my_strcpy(data, str);
    }
}
my_string::my_string(const my_string& str)
{
    length = str.size();
    data = new char[length + 1];
    my_strcpy(data, str.c_str());
}

int my_string::toInt()
{
    int res = 0;
    for (int i = 0; i < length; i++) {
        res = res * 10 + data[i] - '0';
    }
    return res;
}

my_string& my_string::operator=(const my_string& str)
{
    if (this == &str) {
        return *this;
    }
    delete[] data;
    length = str.size();
    data = new char[length + 1];
    my_strcpy(data, str.c_str());
    return *this;
}

my_string& my_string::operator=(const char* str)
{
    if (data == str) {
        return *this;
    }
    delete[] data;
    length = my_strlen(str);
    data = new char[length + 1];
    my_strcpy(data, str);
    return *this;
}

bool my_string::operator==(const my_string& str) const
{
    if (length != str.size()) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (data[i] != str[i]) {
            return false;
        }
    }
    return true;
}

char& my_string::operator[](int n) const
{
    if (n >= length) {
        throw "out of range";
    } else {
        return data[n];
    }
}

istream& operator>>(istream& is, my_string& str)
{
    char* temp = new char[BUFFER_SIZE];
    is >> temp;
    delete[] str.data;
    str.length = str.my_strlen(temp);
    str.data = new char[str.length + 1];
    str.my_strcpy(str.data, temp);
    delete[] temp;
    return is;
}
ostream& operator<<(ostream& os, my_string& str)
{
    os << str.c_str();
    return os;
}
int my_string::my_strlen(const char* str)
{
    int len = 0;
    while (*str++ != '\0') {
        len++;
    }
    return len;
}
void my_string::my_strcpy(char* dst, const char* src)
{
    while (*src != '\0') {
        *dst++ = *src++;
    }
    *dst = '\0';
}

my_string operator+(const my_string& lhs, const my_string& rhs)
{
    my_string res;
    res.length = lhs.size() + rhs.size();
    res.data = new char[res.length + 1];
    my_string::my_strcpy(res.data, lhs.c_str());
    my_string::my_strcpy(res.data + lhs.size(), rhs.c_str());
    return res;
}

#endif // __STRING_H__

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode *left, *right;
    HuffmanNode(char data = '\0', int frequency = 0)
        : data(data)
        , frequency(frequency)
        , left(nullptr)
        , right(nullptr)
    {
    }
};
class compare {
public:
    bool operator()(HuffmanNode*& a, HuffmanNode*& b)
    {
        return a->frequency < b->frequency;
    }
};

using BinaryTree = linkedBinaryTree<char, HuffmanNode>;
using minHeap = PriorityQueue<HuffmanNode*, compare>;
using String = my_string;
// using String = std::string;

class HuffmanTree {
private:
    HuffmanNode* root;
    BinaryTree* tree;
    int codes[26];

public:
    static minHeap calFrequency(const char* input, int length)
    {
        int weight[26] = { 0 };
        for (int i = 0; i < length; i++) {
            weight[input[i] - 'a']++;
        }

        minHeap weightHeap;
        for (int i = 0; i < 26; i++) {
            if (weight[i] != 0) {
                HuffmanNode* h = new HuffmanNode;
                h->data = 'a' + i;
                h->frequency = weight[i];
                weightHeap.push(h);
            }
        }
        return weightHeap;
    }

    void buildTree(minHeap& weightHeap)
    {
        while (weightHeap.size() > 1) {
            HuffmanNode* node1 = weightHeap.top();
            weightHeap.pop();
            HuffmanNode* node2 = weightHeap.top();
            weightHeap.pop();

            HuffmanNode* newNode = new HuffmanNode('\0', node1->frequency + node2->frequency);
            newNode->left = node1;
            newNode->right = node2;

            weightHeap.push(newNode);
        }
        this->tree = new BinaryTree(weightHeap.top());
        this->root = weightHeap.top();
        weightHeap.pop();
    }
    void assignCode()
    {
        assignCode(root, "");
    }

    void assignCode(HuffmanNode* n, String code)
    {
        if (n == nullptr) {
            return;
        }
        if (n->left == nullptr && n->right == nullptr) {
            codes[n->data - 'a'] = code.size();
        }
        if (n->left) {
            assignCode(n->left, code + "0");
        }
        if (n->right) {
            assignCode(n->right, code + "1");
        }
    }

    int calLength(String& input)
    {
        int length = 0;
        for (auto& i : input) {
            length += codes[i - 'a'];
        }
        return length;
    }
};

class Solution {
private:
    String input;

public:
    Solution(const String& input)
        : input(input)
    {
    }
    ~Solution() = default;
    void runtest()
    {
        int weight[26] = { 0 };
        for (auto& i : input) {
            weight[i - 'a']++;
        }
        minHeap weightHeap = HuffmanTree::calFrequency(input.c_str(), input.size());
        HuffmanTree h;
        h.buildTree(weightHeap);
        h.assignCode();
        std::cout << h.calLength(input) << std::endl;
    }
};

int main(void)
{
    String input;
    std::cin >> input;
    Solution s { input };
    s.runtest();
}