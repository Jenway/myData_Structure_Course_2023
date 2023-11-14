#ifndef ARRAYDEQUE_H
#define ARRAYDEQUE_H

#include <cstdlib> // size_t
#include <stdexcept> // std::out_of_range
#include <utility> // std::move

// Double-ended queue implemented with a circular array
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
    ~ArrayDeque();

    ArrayDeque(const ArrayDeque& other) = delete;
    ArrayDeque& operator=(const ArrayDeque& other) = delete;
    ArrayDeque& operator=(ArrayDeque&& other);
    ArrayDeque(ArrayDeque&& other);

    void push_front(T& e);
    void push_back(T& e);
    void push_front(T&& e);
    void push_back(T&& e);

    void pop_front();
    void pop_back();

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }

    T& front();
    T& back();

    void clear();
};

template <typename T>
ArrayDeque<T>::~ArrayDeque()
{
    delete[] data;
    clear();
}

template <typename T>
ArrayDeque<T>& ArrayDeque<T>::operator=(ArrayDeque&& other)
{
    capacity = other.capacity;
    _front = other._front;
    _rear = other._rear;
    _size = other._size;
    data = other.data;
    other.capacity = 0;
    other._front = 0;
    other._rear = 0;
    other._size = 0;
    other.data = nullptr;
    return *this;
}

template <typename T>
ArrayDeque<T>::ArrayDeque(ArrayDeque&& other)
{
    *this = std::move(other);
}

template <typename T>
void ArrayDeque<T>::push_front(T& e)
{

    this->_front = prevIndex(this->_front);
    this->data[this->_front] = e;
    _size++;
    resize();
}

template <typename T>
void ArrayDeque<T>::push_back(T& e)
{
    this->data[this->_rear] = e;
    this->_rear = nextIndex(this->_rear);
    _size++;
    resize();
}

template <typename T>
void ArrayDeque<T>::push_front(T&& e)
{
    this->push_front(std::forward<T>(e));
}

template <typename T>
void ArrayDeque<T>::push_back(T&& e)
{
    this->push_back(std::forward<T>(e));
}

template <typename T>
void ArrayDeque<T>::pop_front()
{
    if (empty()) {
        throw std::out_of_range("deque is empty");
    }
    this->_front = nextIndex(this->_front);
    _size--;
    resize();
}

template <typename T>
void ArrayDeque<T>::pop_back()
{
    if (empty()) {
        throw std::out_of_range("deque is empty");
    }
    this->_rear = prevIndex(this->_rear);
    _size--;
    resize();
}

template <typename T>
T& ArrayDeque<T>::front()
{
    if (empty()) {
        throw std::out_of_range("deque is empty");
    } else {
        return this->data[this->_front];
    }
}

template <typename T>
T& ArrayDeque<T>::back()
{
    if (empty()) {
        throw std::out_of_range("deque is empty");
    } else {
        return this->data[prevIndex(this->_rear)];
    }
}

template <typename T>
void ArrayDeque<T>::clear()
{
    _front = 0;
    _rear = 0;
    _size = 0;
}

template <typename T>
void ArrayDeque<T>::resize()
{
    if (_size == capacity) {
        resize(capacity * 2);
    } else if (_size < capacity / 4) {
        resize(capacity / 2);
    }
}

template <typename T>
void ArrayDeque<T>::resize(int newCapacity)
{
    T* newData = new T[newCapacity] {};
    int j = 0;
    for (int i = _front; i != _rear; i = nextIndex(i)) {
        newData[j++] = data[i];
    }
    newData[j] = data[_rear];
    delete[] data;
    data = newData;
    capacity = newCapacity;
    _front = 0;
    _rear = j;
}

#endif // ARRAYDEQUE_H