#include <iostream>

template <typename T>
class myQueue {
private:
    T* data;
    size_t _size;
    size_t capacity;
    size_t _front;
    size_t _back;

    void resize(size_t newCapacity);
    size_t nextIndex(size_t index);

public:
    myQueue()
        : _size(0)
        , capacity(10)
        , _front(0)
        , _back(0)
    {
        data = new T[capacity];
    }
    ~myQueue()
    {
        delete[] data;
    }
    void push(const T& val);
    void pop();
    T& front() { return data[_front]; }
    size_t size() const { return _size; }
};

template <typename T>
void myQueue<T>::push(const T& val)
{
    if (_size == capacity) {
        resize(capacity * 2);
    }
    data[_back] = val;
    _back = nextIndex(_back);
    _size++;
}

template <typename T>
void myQueue<T>::pop()
{
    _front = nextIndex(_front);
    _size--;
}

template <typename T>
void myQueue<T>::resize(size_t newCapacity)
{
    if (newCapacity == _size) {
        return;
    } else if (newCapacity < _size) {
        return; // tobe done
    } else {
        T* new_data = new T[newCapacity];
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = data[(_front + i) % _size];
        }
        delete[] data;
        data = new_data;
        _front = 0;
        _back = _size;
        capacity = newCapacity;
    }
}

template <typename T>
size_t myQueue<T>::nextIndex(size_t index)
{
    return (index + 1) % capacity;
}
