#include "arrayList.h"
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