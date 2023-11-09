#include <algorithm>
#include <vector>


template <typename T>
class PriorityQueue {
    std::vector<T> heap;

public:
    PriorityQueue() { }

    void push(T val)
    {
        heap.push_back(val);
        std::push_heap(heap.begin(), heap.end());
    }

    void pop()
    {
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
    }

    T top()
    {
        return heap.front();
    }

    bool empty()
    {
        return heap.empty();
    }
};