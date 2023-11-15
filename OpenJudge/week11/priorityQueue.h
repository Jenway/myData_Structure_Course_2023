#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <utility> // std::move std::swap

template <typename T>
class PriorityQueue {
private:
    int capacity;
    int heapSize;
    bool (*cmp)(const T&, const T&);
    T* heap;

    void resize(int newCapacity);
    void freeArray();
    void heapify(int index);
    static void heapify(T* a, int n, int index, bool (*cmp)(const T&, const T&));

public:
    static bool greater(const T&, const T&);
    static bool less(const T&, const T&);

    PriorityQueue(int capacity = 100);
    PriorityQueue(T* a, T* b);

    ~PriorityQueue();

    static void make_heap(T* begin, T* end, bool (*cmp)(const T&, const T&));
    static void sort_heap(T* begin, T* end, bool (*cmp)(const T&, const T&));

    void push(T& value);
    void push(T&& value);

    void pop();

    T& top() const;

    bool empty() const { return heapSize == 0; }
    size_t size() const { return heapSize; }
};

template <typename T>
bool PriorityQueue<T>::greater(const T& a, const T& b)
{
    return a > b;
}

template <typename T>
bool PriorityQueue<T>::less(const T& a, const T& b)
{
    return a < b;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(int capacity)
    : capacity(capacity)
    , heapSize(0)
    , cmp(greater)
{
    heap = new T[capacity];
}

template <typename T>
PriorityQueue<T>::PriorityQueue(T* a, T* b)
    : capacity((b - a) * 2)
    , heapSize(b - a)
    , cmp(greater)
{
    heap = new T[capacity];
    for (int i = 0; i < heapSize; i++) {
        heap[i] = *(a + i);
    }
    make_heap(heap, heap + heapSize, cmp);
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    this->freeArray();
}

template <typename T>
void PriorityQueue<T>::resize(int newCapacity)
{
    T* newHeap = new T[newCapacity];
    for (int i = 0; i < heapSize; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

template <typename T>
void PriorityQueue<T>::push(T& value)
{
    if (heapSize == capacity) {
        resize(2 * capacity);
    }
    heap[heapSize] = value;

    for (int i = heapSize; i > 0 && cmp(heap[(i - 1) / 2], heap[i]); i = (i - 1) / 2) {
        std::swap(heap[i], heap[(i - 1) / 2]);
    }

    heapSize++;
}

template <typename T>
void PriorityQueue<T>::push(T&& value)
{
    this->push(value);
}

template <typename T>
void PriorityQueue<T>::pop()
{
    if (empty()) {
        throw std::out_of_range("PriorityQueue<>::pop(): empty priority queue");
    }
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapify(0);
}

template <typename T>
T& PriorityQueue<T>::top() const
{
    if (empty()) {
        throw std::out_of_range("PriorityQueue<>::top(): empty priority queue");
    }
    return heap[0];
}

template <typename T>
void PriorityQueue<T>::freeArray()
{
    delete[] heap;
    heap = nullptr;
}

template <typename T>
void PriorityQueue<T>::heapify(int index)
{
    heapify(heap, heapSize, index, cmp);
}

template <typename T>
void PriorityQueue<T>::heapify(T* a, int n, int index, bool (*cmp)(const T&, const T&))
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int _llest = index;
    if (left < n && cmp(a[left], a[_llest])) {
        _llest = left;
    }

    if (right < n && cmp(a[right], a[_llest])) {
        _llest = right;
    }

    if (_llest != index) {
        std::swap(a[index], a[_llest]);
        heapify(a, n, _llest, cmp);
    }
}

template <typename T>
void PriorityQueue<T>::make_heap(T* begin, T* end, bool (*cmp)(const T&, const T&))
{
    int n = end - begin;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(begin, n, i, cmp);
    }
}

template <typename T>
void PriorityQueue<T>::sort_heap(T* begin, T* end, bool (*cmp)(const T&, const T&))
{
    for (int i = end - begin - 1; i >= 0; i--) {
        std::swap(begin[0], begin[i]);
        heapify(begin, i, 0, cmp);
    }
}

#endif // PRIORITYQUEUE_H
