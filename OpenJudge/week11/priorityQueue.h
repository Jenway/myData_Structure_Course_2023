#include "arrayDeque.h"
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
void PriorityQueue<T, Compare>::push( T& x)
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