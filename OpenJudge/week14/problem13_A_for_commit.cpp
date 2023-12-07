#if !defined(_ARRAYLIST_H)
#define _ARRAYLIST_H

#include <stdexcept> // for std::out_of_range

template <typename T>
class arrayList {
private:
    T* array;
    int _size;
    int _capacity;

public:
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef T* pointer;
    typedef int size_type;

    class iterator {
    private:
        T* ptr;

    public:
        iterator(T* ptr);
        ~iterator() = default;
        T& operator*() const;
        T* operator->() const;

        iterator& operator++();
        iterator operator++(int);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

        operator bool() const { return ptr != nullptr; }
    };

    arrayList()
        : _size(0)
        , _capacity(10)
    {
        array = new T[_capacity];
    }

    arrayList(int capacity)
        : _size(capacity)
        , _capacity(capacity)
    {
        array = new T[_capacity];
        for (int i = 0; i < _capacity; i++) {
            array[i] = T();
        }
    }
    arrayList(int count, const T& value)
        : _size(count)
        , _capacity(count * 2)
    {
        array = new T[_capacity];
        for (int i = 0; i < count; i++) {
            array[i] = value;
        }
    }

    ~arrayList();
    arrayList(const arrayList& list);
    arrayList(arrayList&& list);
    arrayList& operator=(const arrayList& list);
    arrayList& operator=(arrayList&& list);
    void assign(int count, const T& value);

    // Element access
    T& at(int index);
    T& operator[](int index);
    T& front();
    T& back();
    T* data();

    // Iterators

    iterator begin() const { return iterator(array); }
    iterator end() const { return iterator(array + _size); }

    // Capacity
    bool empty() const { return _size == 0; }
    int size() const { return _size; }
    void reserve(int new_Capacity);
    int capacity() const { return _capacity; }

    // Modifiers
    void clear();
    iterator insert(const iterator position, const T& val);
    iterator insert(const iterator position, T&& val);
    iterator erase(iterator position);
    void push_back(const T& data);
    void push_back(T&& data);
    void pop_back();
    void resize(int new_Size, const T& defaultValue);
};

template <typename T>
arrayList<T>::~arrayList()
{

    // for (int i = 0; i < _size; ++i) {
    //     array[i].~T();
    // }

    delete[] array;
    array = nullptr;
}

template <typename T>
arrayList<T>& arrayList<T>::operator=(const arrayList& list)
{
    if (this == &list) {
        return *this;
    }
    delete[] array;
    _capacity = list._capacity;
    _size = list._size;
    array = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        array[i] = list.array[i];
    }
    return *this;
}
template <typename T>
arrayList<T>& arrayList<T>::operator=(arrayList&& list)
{
    if (this == &list) {
        return *this;
    }
    delete[] array;
    _capacity = list._capacity;
    _size = list._size;
    array = list.array;
    list.array = nullptr;
    return *this;
}
template <typename T>
arrayList<T>::arrayList(const arrayList& list)
{
    this->operator=(list);
}

template <typename T>
arrayList<T>::arrayList(arrayList&& list)
{
    if (this == &list) {
        return;
    }
    delete[] array;
    _capacity = list._capacity;
    _size = list._size;
    array = list.array;
    list.array = nullptr;
}

template <typename T>
void arrayList<T>::assign(int count, const T& value)
{
    if (count < 0) {
        return;
    }
    if (count > _capacity) {
        reserve(count);
    }
    for (int i = 0; i < count; i++) {
        array[i] = value;
    }
    _size = count;
}

template <typename T>
void arrayList<T>::push_back(const T& data)
{
    if (_size == _capacity) {
        _capacity *= 2;
        T* newArray = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[_size++] = data;
}
template <typename T>
void arrayList<T>::push_back(T&& data)
{
    this->push_back(data);
}

template <typename T>
void arrayList<T>::reserve(int new_Capacity)
{
    if (new_Capacity <= _capacity) {
        return;
    }
    _capacity = new_Capacity;
    T* newArray = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
}

template <typename T>
T& arrayList<T>::at(int index)
{
    return (*this)[index];
}

template <typename T>
T& arrayList<T>::operator[](int index)
{
    if (index < 0 || index >= _size) {
        throw std::out_of_range("index out of range");
    }
    return array[index];
}

template <typename T>
T& arrayList<T>::front()
{
    if (_size == 0) {
        throw std::out_of_range("index out of range");
    }
    return array[0];
}

template <typename T>
T& arrayList<T>::back()
{
    if (_size == 0) {
        throw std::out_of_range("index out of range");
    }
    return array[_size - 1];
}

template <typename T>
T* arrayList<T>::data()
{
    if (_size == 0) {
        return nullptr;
    } else {
        return array;
    }
}

template <typename T>
void arrayList<T>::pop_back()
{
    if (_size == 0) {
        return;
    }
    _size--;
}

template <typename T>
void arrayList<T>::clear()
{
    _size = 0;
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::insert(const iterator position, const T& val)
{
    if (_size == _capacity) {
        _capacity *= 2;
        T* newArray = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    int index = position - begin();
    for (int i = _size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = val;
    _size++;
    return iterator(array + index);
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::insert(const iterator position, T&& val)
{
    return insert(position, val);
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::erase(iterator position)
{
    int index = position - begin();
    for (int i = index; i < _size - 1; i++) {
        array[i] = array[i + 1];
    }
    _size--;
    return iterator(array + index);
}

template <typename T>
void arrayList<T>::resize(int new_Size, const T& defaultValue)
{
    if (new_Size < 0) {
        return;
    }
    if (new_Size > _capacity) {
        reserve(new_Size);
    }
    for (int i = _size; i < new_Size; i++) {
        array[i] = defaultValue;
    }
    _size = new_Size;
}

// iterator

template <typename T>
arrayList<T>::iterator::iterator(T* ptr)
    : ptr(ptr)
{
}

template <typename T>
T& arrayList<T>::iterator::operator*() const
{
    if (ptr == nullptr) {
        throw std::out_of_range("iterator out of range");
    } else {
        return *ptr;
    }
}

template <typename T>
T* arrayList<T>::iterator::operator->() const
{
    if (ptr == nullptr) {
        throw std::out_of_range("iterator out of range");
    } else {
        return ptr;
    }
}

template <typename T>
typename arrayList<T>::iterator& arrayList<T>::iterator::operator++()
{
    if (ptr == nullptr) {
        throw std::out_of_range("iterator out of range");
    } else {
        ptr++;
        return *this;
    }
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::iterator::operator++(int)
{
    iterator temp = *this;
    ++*this;
    return temp;
}

template <typename T>
bool arrayList<T>::iterator::operator==(const iterator& other) const
{
    return ptr == other.ptr;
}

template <typename T>
bool arrayList<T>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

#endif // _ARRAYLIST_H
#if !defined(LINKEDLIST_H)
#define LINKEDLIST_H

#include <stdexcept> // for std::out_of_range

template <typename T>
class LinkedList {
protected:
    typedef struct node {
        T val;
        struct node* next;
        struct node* prev;
        node(T val, struct node* next = nullptr, struct node* prev = nullptr)
            : val(val)
            , next(next)
            , prev(prev)
        {
        }
    } Node;
    Node* head;
    Node* tail;
    int _size;

public:
    class Iterator {
    private:
        Node* current;

    public:
        friend class LinkedList<T>;
        Iterator(Node* current)
            : current(current)
        {
        }
        ~Iterator() = default;

        T operator*() const;
        Iterator operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        operator bool() const;
        Iterator operator+(const int& n) const;
    };

    LinkedList();
    LinkedList(const LinkedList& list);
    ~LinkedList();

    // Element access
    T& front() { return head->val; }
    T& back() { return tail->val; }

    // Iterators
    Iterator begin();
    Iterator end();

    // Capacity
    bool empty() const { return head == nullptr; }
    int size() const { return _size; }

    // Modifiers
    void clear();
    Iterator insert(const Iterator& pos, T val);
    bool erase(Iterator pos);
    void push_back(T& val);
    void push_back(T&& val) { push_back(val); }
    void pop_back();
    void push_front(T& val);
    void push_front(T&& val) { push_front(val); }
    void pop_front();

    // Operation
    LinkedList merge(LinkedList& list);
    bool remove(T val);
    void reverse();
    void sort();

    int getIdx(T val) const;
    Iterator getIndex(T val) const;
};

// <--- implement of LinkedList --->
template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr)
    , tail(nullptr)
    , _size(0)

{
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& list)
{
    head = nullptr;
    tail = nullptr;
    _size = 0;
    Node* p = list.head;
    while (p != nullptr) {
        push_back(p->val);
        p = p->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return LinkedList<T>::Iterator(head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return LinkedList<T>::Iterator(nullptr);
}

template <typename T>
void LinkedList<T>::clear()
{
    Node* p = head;
    while (p != nullptr) {
        head = p->next;
        delete p;
        p = head;
    }
    head = nullptr;
    tail = nullptr;
    _size = 0;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::insert(const LinkedList<T>::Iterator& pos, T val)
{
    if (pos == begin()) {
        head = new Node(val, head);
        if (head->next) {
            head->next->prev = head;
        } else {
            tail = head;
        }
        _size++;
        return Iterator(head);
    } else if (pos == end()) {
        push_back(val);
        return Iterator(tail);
    } else {
        Node* newNode = new Node(val, pos.current, pos.current->prev);
        pos.current->prev = newNode;
        newNode->prev->next = newNode;
        _size++;
        return Iterator(newNode);
    }
}

template <typename T>
bool LinkedList<T>::erase(LinkedList<T>::Iterator pos)
{
    if (pos) {
        if (pos.current->prev) {
            pos.current->prev->next = pos.current->next;
        } else {
            head = pos.current->next;
        }
        if (pos.current->next) {
            pos.current->next->prev = pos.current->prev;
        } else {
            tail = pos.current->prev;
        }
        delete pos.current;
        _size--;
        return true;
    } else {
        return false;
    }
}

template <typename T>
void LinkedList<T>::push_back(T& val)
{
    if (head == nullptr) {
        head = new Node(val);
        tail = head;
    } else {
        tail->next = new Node(val, nullptr, tail);
        tail = tail->next;
    }
    _size++;
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if (tail != nullptr) {
        Node* p = tail;
        tail = tail->prev;
        delete p;
        _size--;
    }
    if (tail == nullptr) {
        head = nullptr;
    }
}

template <typename T>
void LinkedList<T>::push_front(T& val)
{
    if (head == nullptr) {
        head = new Node(val);
        tail = head;
    } else {
        head->prev = new Node(val, head);
        head = head->prev;
    }
    _size++;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if (head != nullptr) {
        Node* p = head;
        head = head->next;
        delete p;
        _size--;
    }
    if (head == nullptr) {
        tail = nullptr;
    }
}

template <typename T>
LinkedList<T> LinkedList<T>::merge(LinkedList<T>& list)
{
    LinkedList<T> newList = LinkedList<T>();
    Node *p = head, *q = list.head;
    while (p != nullptr || q != nullptr) {
        if (p == nullptr) {
            newList.push_back(q->val);
            q = q->next;
        } else if (q == nullptr) {
            newList.push_back(p->val);
            p = p->next;
        } else if (p->val < q->val) {
            newList.push_back(p->val);
            p = p->next;
        } else {
            newList.push_back(q->val);
            q = q->next;
        }
    }
    return newList;
}

template <typename T>
bool LinkedList<T>::remove(T val)
{
    return this->erase(this->getIndex(val));
}

template <typename T>
void LinkedList<T>::reverse()
{
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
void LinkedList<T>::sort()
{
    Node *p, *q;
    for (p = head; p != nullptr; p = p->next) {
        for (q = p->next; q != nullptr; q = q->next) {
            if (p->val > q->val) {
                T tmp = p->val;
                p->val = q->val;
                q->val = tmp;
            }
        }
    }
}

template <typename T>
int LinkedList<T>::getIdx(T val) const
{
    Node* p = head;
    int idx = 0;
    while (p != nullptr) {
        if (p->val == val) {
            return idx;
        }
        p = p->next;
        idx++;
    }
    return -1;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::getIndex(T val) const
{

    for (Node* p = head; p != nullptr; p = p->next) {
        if (p->val == val) {
            return LinkedList<T>::Iterator(p);
        }
    }
    return LinkedList<T>::Iterator(nullptr);
}

// <--- implement of iterator --->

template <typename T>
T LinkedList<T>::Iterator::operator*() const
{
    return current->val;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++()
{
    // e.g. ++it
    if (current == nullptr) {
        throw std::out_of_range("out of range");
    }
    current = current->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    // e.g. it++
    if (current == nullptr) {
        throw std::out_of_range("out of range");
    }
    LinkedList<T>::Iterator it = *this;
    ++(*this);
    return it;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const LinkedList<T>::Iterator& rhs) const
{
    return current == rhs.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const LinkedList<T>::Iterator& rhs) const
{
    return current != rhs.current;
}

template <typename T>
LinkedList<T>::Iterator::operator bool() const
{
    return current != nullptr;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator+(const int& n) const
{
    LinkedList<T>::Iterator it = *this;
    for (int i = 0; i < n; i++) {
        ++it;
    }
    return it;
}

#endif // LINKEDLIST_H
#include <iostream>

template <typename T>
using vector = arrayList<T>;

template <typename T>
class my_less {
public:
    bool operator()(const T& lhs, const T& rhs) { return lhs < rhs; }
};
template <typename T>
class my_greater {
public:
    bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

template <typename T, typename Compare>
void make_heap(T* a, int n, Compare cmp = Compare());

template <typename T, typename Compare = my_less<T>> // default is less
class PriorityQueue {
private:
    vector<T> heap;
    Compare cmp;

    void percolateDown(int hole = 0);

public:
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
    // percolateUp
    for (; hole > 0 && cmp(x, heap[(hole - 1) / 2]); hole = (hole - 1) / 2) {
        heap[hole] = std::move(heap[(hole - 1) / 2]);
    }
    heap[hole] = x;
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(T&& x)
{
    this->push(x);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::pop()
{
    heap[0] = std::move(heap.back());
    heap.pop_back();
    if (!heap.empty()) {
        percolateDown();
    }
}

template <typename T, typename Compare>
void make_heap(T* a, int n, Compare cmp)
{
    // Iterate all non-leaf nodes
    for (int i = n / 2 - 1; i >= 0; --i) {
        // percolateDown
        T tmp = std::move(a[i]);
        int child;
        int hole = i;
        for (; hole * 2 + 1 < n; hole = child) {
            child = hole * 2 + 1; // left_child
            if (child != n - 1 && cmp(a[child + 1], a[child])) {
                ++child; // find the _est child
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

template <typename T, typename Compare>
void sort_heap(T* a, int n, Compare cmp = Compare())
{
    for (int i = n - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        // percolateDown
        T tmp = std::move(a[0]);
        int child;
        int hole = 0;
        for (; hole * 2 + 1 < i; hole = child) {
            child = hole * 2 + 1; // left_child
            if (child != i - 1 && cmp(a[child + 1], a[child])) {
                ++child; // find the _est child
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

template <typename T, typename Compare = my_greater<T>>
void heapSort(T* a, int n, Compare cmp = Compare())
{
    make_heap(a, n, cmp);
    sort_heap(a, n, cmp);
}

class UnionFind {
private:
    using Vector = arrayList<int>;
    Vector parent;

public:
    UnionFind(int size)
    {
        // 初始化，每个元素的父节点为自己
        parent.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    // 查找根节点（代表元素）
    int find(int x)
    {
        return (parent[x] == x) ? x : (parent[x] = find(parent[x]));
    }

    // 合并两个集合
    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    // 判断两个元素是否属于同一集合
    bool isConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};
struct wEdge {
    int a, b, w;

    bool operator<(const wEdge& other) const { return w < other.w; }
    bool operator>(const wEdge& other) const { return w > other.w; }
};
using wEge = struct wEdge;

template <typename T>
using Vector = arrayList<T>;

using List = LinkedList<wEdge>;
using PQueue = PriorityQueue<wEdge, my_less<wEdge>>;

template <typename T>
class linkedWGraph {
private:
    int n;
    Vector<List> graph;

public:
    linkedWGraph(int n)
        : n(n)
        , graph(Vector<List>(n + 1))
    {
    }

    int size() const { return n; }

    void addEdge(int a, int b, int w)
    {
        graph[a].push_back(wEdge { a, b, w });
        graph[b].push_back(wEdge { b, a, w });
    }

    long long prim()
    {
        Vector<bool> visited(n + 1, false);
        PQueue q;
        q.push(wEdge { 0, 1, 0 });
        long long ans = 0;
        while (!q.empty()) {
            wEdge e = q.top();
            q.pop();
            if (visited[e.b])
                continue;
            visited[e.b] = true;
            ans += e.w;
            for (auto edge : graph[e.b]) {
                if (!visited[edge.b]) {
                    q.push(edge);
                }
            }
        }
        return ans;
    }

    long long kruskal()
    {
        UnionFind uf(n + 1);
        Vector<wEdge> arr;
        for (int i = 1; i <= n; i++) {
            for (auto edge : graph[i]) {
                arr.push_back(edge);
            }
        }
        heapSort<wEdge>(arr.data(), arr.size());
        long long ans = 0;
        for (auto e : arr) {
            int rootX = uf.find(e.a);
            int rootY = uf.find(e.b);

            if (rootX != rootY) {
                uf.unite(e.a, e.b);
                ans += e.w;
            }
        }

        return ans;
    }
};

class Solution {
private:
    int e;
    linkedWGraph<int> graph;

public:
    Solution(int n, int e)
        : e(e)
        , graph(linkedWGraph<int>(n))
    {
    }
    void solve()
    {
        for (int i = 0; i < e; i++) {
            int a, b, w;
            std::cin >> a >> b >> w;
            graph.addEdge(a, b, w);
        }
        std::cout << graph.prim() << std::endl;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, e;
    std::cin >> n >> e;
    Solution solution(n, e);
    solution.solve();
    return 0;
}