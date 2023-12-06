#include "linkedList.h"

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