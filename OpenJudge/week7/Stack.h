#include <iostream>

using namespace std;

template <typename T>
class my_stack {
private:
    T* data;
    int _top;
    int _size;

    bool isFull();
    void resize(int newSize);

public:
    my_stack()
        : my_stack(100)
    {
    }
    my_stack(int size);
    ~my_stack();

    my_stack(const my_stack& other) = delete;
    my_stack& operator=(const my_stack& other) = delete;
    my_stack& operator=(my_stack&& other);
    my_stack(my_stack&& other);

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
my_stack<T>& my_stack<T>::operator=(my_stack&& other)
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
my_stack<T>::my_stack(my_stack&& other)
{
    *this = std::move(other);
}

template <typename T>
my_stack<T>::my_stack(int size)
    : _size(size)
{
    data = new T[size];
    _top = -1;
}

template <typename T>
my_stack<T>::~my_stack()
{
    delete[] data;
}

template <typename T>
void my_stack<T>::resize(int newSize)
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
size_t my_stack<T>::size() const
{
    return _size;
}

template <typename T>
void my_stack<T>::push(T& item)
{
    if (isFull()) {
        resize(_size * 2);
    }
    data[++_top] = item;
}

template <typename T>
void my_stack<T>::push(T&& item)
{
    if (isFull()) {
        resize(_size * 2);
    }
    data[++_top] = std::move(item);
}

template <typename T>
void my_stack<T>::pop()
{
    if (empty()) {
        throw "my_stack is empty";
    } else {
        --_top;
    }
}

template <typename T>
bool my_stack<T>::empty() const
{
    return _top == -1;
}

template <typename T>
bool my_stack<T>::isFull()
{
    return _top == _size - 1;
}

template <typename T>
T& my_stack<T>::top()
{
    if (empty()) {
        throw "my_stack is empty";
    } else {
        return data[_top];
    }
}

template <typename T>
void my_stack<T>::print()
{
    for (int i = 0; i <= _top; i++) {
        cout << data[i];
    }
    cout << endl;
}
