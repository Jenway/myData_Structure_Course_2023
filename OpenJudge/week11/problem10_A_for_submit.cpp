
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
        if (index < 0 || index >= _size) {
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

    void push(const T& x);
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
void PriorityQueue<T, Compare>::push(const T& x)
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

using min_heap = PriorityQueue<int>;
using namespace std;

class Solution {
private:
    int n;
    min_heap pq;

public:
    Solution(int n)
        : n(n)
    {
    }
    void input()
    {
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            pq.push(x);
        }
        cout << pq.top() << endl;
    }
    void runTest()
    {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int op;
            cin >> op;
            switch (op) {
            case 1:
                int x;
                cin >> x;
                pq.push(x);
                cout << pq.top() << endl;
                break;
            case 2:
                pq.pop();
                cout << pq.top() << endl;
                break;
            case 3: {
                int sz;
                cin >> sz;
                int* b = new int[sz];
                for (int j = 0; j < sz; j++) {
                    cin >> b[j];
                }
                heapSort<int, std::greater<int>>(b, sz);
                for (int j = 0; j < sz; j++) {
                    cout << b[j] << " ";
                }
                delete[] b;
                cout << endl;
                break;
            }
            default:
                break;
            }
        }
    }
};

int main(void)
{
    int n;
    cin >> n;
    Solution sol(n);
    sol.input();
    sol.runTest();
    return 0;
}