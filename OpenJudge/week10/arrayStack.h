
#include <iostream>

template <typename T>
class ArrayStack {
private:
    T* data;
    int _top;
    int _size;

    bool isFull();
    void resize(int newSize);

public:
    ArrayStack()
        : ArrayStack(100)
    {
    }
    ArrayStack(int size);
    ~ArrayStack();

    ArrayStack(const ArrayStack& other) = delete;
    ArrayStack& operator=(const ArrayStack& other) = delete;
    ArrayStack& operator=(ArrayStack&& other);
    ArrayStack(ArrayStack&& other);

    void push(T& item);
    void push(T&& item);
    void pop();

    bool empty() const;
    size_t size() const;

    T& top();

    // for debug
    void print();
};

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack&& other)
{
    data = other.data;
    _top = other._top;
    _size = other._size;
    other.data = nullptr;
    other._top = -1;
    other._size = 0;
    return *this;
}
template <typename T>
ArrayStack<T>::ArrayStack(ArrayStack&& other)
{
    *this = std::move(other);
}

template <typename T>
ArrayStack<T>::ArrayStack(int size)
    : _size(size)
{
    data = new T[size];
    _top = -1;
}

template <typename T>
ArrayStack<T>::~ArrayStack()
{
    delete[] data;
}

template <typename T>
void ArrayStack<T>::resize(int newSize)
{
    T* newData = new T[newSize];
    for (int i = 0; i < _size; i++) {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    _size = newSize;
}

template <typename T>
size_t ArrayStack<T>::size() const
{
    return _size;
}

template <typename T>
void ArrayStack<T>::push(T& item)
{
    if (isFull()) {
        resize(_size * 2);
    }
    data[++_top] = item;
}

template <typename T>
void ArrayStack<T>::push(T&& item)
{
    if (isFull()) {
        resize(_size * 2);
    }
    data[++_top] = std::move(item);
}

template <typename T>
void ArrayStack<T>::pop()
{
    if (empty()) {
        throw "ArrayStack is empty";
    } else {
        --_top;
    }
}

template <typename T>
bool ArrayStack<T>::empty() const
{
    return _top == -1;
}

template <typename T>
bool ArrayStack<T>::isFull()
{
    return _top == _size - 1;
}

template <typename T>
T& ArrayStack<T>::top()
{
    if (empty()) {
        throw "ArrayStack is empty";
    } else {
        return data[_top];
    }
}

template <typename T>
void ArrayStack<T>::print()
{
    for (int i = 0; i <= _top; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;
}
