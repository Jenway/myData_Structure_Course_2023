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