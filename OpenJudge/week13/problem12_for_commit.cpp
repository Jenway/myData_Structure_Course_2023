#if !defined(_ARRAYLIST_H)
#define _ARRAYLIST_H

#include <iostream>
using namespace std;

template <typename T>
class arrayList {
private:
    T* array;
    int _size;
    int _capacity;

public:
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
    this->push_back(std::move(data));
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
    array[index] = std::move(val);
    _size++;
    return iterator(array + index);
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
#include <iostream>

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
    Iterator push_front(T& val)
    {
        head = new Node(val, head);
        return Iterator(head);
    }
    void pop_front();

    // Operation
    LinkedList merge(LinkedList& list);
    bool remove(T val);
    void reverse();
    void sort();

    int getIdx(T val) const;
    Iterator getIndex(T val) const;

    // for test
    void LOG_output()
    {
        for (auto i : *this) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    void LOG_output(std::stringstream& ss)
    {
        for (auto i : *this) {
            ss << i << " ";
        }
    }
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
    Node* p = list.head;
    while (p != nullptr) {
        push_back(p->val);
        p = p->next;
    }

    _size = list._size;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
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
bool LinkedList<T>::remove(T val)
{
    return this->erase(this->getIndex(val));
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
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return LinkedList<T>::Iterator(head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
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
        throw "out of range";
    }
    current = current->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    // e.g. it++
    if (current == nullptr) {
        throw "out of range";
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

template <typename T>
class my_greater {
public:
    bool operator()(const T& a, const T& b) const
    {
        return a > b;
    }
};

template <typename T, typename Compare = my_greater<T>>
class sortedLinkedList : public LinkedList<T> {
    using Node = typename LinkedList<T>::Node;

private:
    Compare cmp;

public:
    sortedLinkedList() = default;
    ~sortedLinkedList() = default;

    void insert(T& val)
    {
        // LinkedList<T>::insert(std::lower_bound(LinkedList<T>::begin(), LinkedList<T>::end(), val), val);
        auto it = LinkedList<T>::begin();
        for (; it != LinkedList<T>::end(); ++it) {
            if (cmp(*it, val)) {
                break;
            }
        }
        LinkedList<T>::insert(it, val);
    }
};

#include <cassert>
#include <iostream>

template <typename T>
using Vector = arrayList<T>;

template <typename T>
using List = sortedLinkedList<T>;

template <typename T>
class linkedGraph {
private:
    int vertexNum;
    Vector<List<T>> adjList;

public:
    // 创建无向图类，存储结构使用邻接链表，提供操作：插入一条边，删除一条边，BFS，DFS。
    linkedGraph(int n)
        : vertexNum { n }
        , adjList(n + 1)
    {
    }
    ~linkedGraph() = default;

    int size() const { return adjList.size(); }

    void insertEdge(T u, T v)
    {
        assert(u > 0 && u <= this->vertexNum && v > 0 && v <= this->vertexNum);
        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    void deleteEdge(T u, T v)
    {
        assert(u > 0 && u <= this->vertexNum && v > 0 && v <= this->vertexNum);
        adjList[u].remove(v);
        adjList[v].remove(u);
    }

    void dfs(T u, Vector<bool>& visited)
    {
        visited[u] = true;
        for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
            if (!visited[*it]) {
                dfs(*it, visited);
            }
        }
    }

    void dfs(T u, Vector<bool>& visited, Vector<T>& dfsList)
    {
        visited[u] = true;
        dfsList.push_back(u);
        for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
            if (!visited[*it]) {
                dfs(*it, visited, dfsList);
            }
        }
    }

    // 第六行输出从 t 点开始字典序最小的 bfs 序列
    void bfs(T u, Vector<bool>& visited, Vector<T>& bfsList)
    {
        visited[u] = true;
        List<T> queue;
        queue.push_back(u);
        while (!queue.empty()) {
            T u = queue.front();
            queue.pop_front();
            bfsList.push_back(u);
            for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    queue.push_back(*it);
                }
            }
        }
    }

    void connectedComponents(Vector<Vector<T>>& components)
    {
        Vector<bool> visited(adjList.size(), false);
        for (int i = 1; i <= this->vertexNum; ++i) {
            if (!visited[i]) {
                Vector<T> component;
                dfs(i, visited, component);
                components.push_back(component);
            }
        }
    }

    int shortestPath(T s, T t)
    {
        Vector<bool> visited(adjList.size(), false);
        Vector<int> distance(adjList.size(), 0);
        List<T> queue;
        visited[s] = true;
        queue.push_back(s);
        while (!queue.empty()) {
            T u = queue.front();
            queue.pop_front();
            for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    distance[*it] = distance[u] + 1;
                    queue.push_back(*it);
                }
            }
        }
        return distance[t] ? distance[t] : -1;
    }
};

#include <iostream>

class Solution {
private:
    linkedGraph<int> g;
    int m, s, t;

public:
    Solution(int n)
        : g(n)
    {
        // m (10≤m≤200000) 代表接下来共有 m 个操作
        // s 代表起始点，t 代表终点。
        std::cin >> m >> s >> t;
        // 接下来 m 行，0 代表插入一条边，1 代表删除一条边，接下来两个整数 u，v 代表边的两个端点。
        for (int i = 0; i < m; ++i) {
            int op, u, v;
            std::cin >> op >> u >> v;
            if (op == 0) {
                g.insertEdge(u, v);
            } else {
                g.deleteEdge(u, v);
            }
        }
    }
    void solve()
    {
        // 第一行输出图中有多少个连通分量

        Vector<Vector<int>> components;

        g.connectedComponents(components);
        std::cout << components.size() << "\n";

        // 第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔
        for (auto& component : components) {
            std::cout << *component.begin() << " ";
        }
        std::cout << "\n";

        // 第三行输出从 s 点开始的 dfs 序列长度
        Vector<bool> visited(g.size(), false);
        Vector<int> dfsList;
        g.dfs(s, visited, dfsList);
        std::cout << dfsList.size() << "\n";

        // 第四行输出从 s 点开始的字典序最小的 dfs 序列
        for (auto& v : dfsList) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        // 第五行输出从 t 点开始的 bfs 序列的长度
        visited.assign(g.size(), false);
        Vector<int> bfsList;
        g.bfs(t, visited, bfsList);
        std::cout << bfsList.size() << "\n";

        // 第六行输出从 t 点开始字典序最小的 bfs 序列
        for (auto& v : bfsList) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        // 第七行输出从 s 点到 t 点的最短路径，若是不存在路径则输出-1
        std::cout << g.shortestPath(s, t) << "\n";
    }
};

int main()
{

    int n;
    std::cin >> n;
    Solution s(n);
    s.solve();
    return 0;
}
