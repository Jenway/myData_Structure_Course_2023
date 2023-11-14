#include "myStack.h"
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <utility> // std::move

template <typename T>
class LinkedStack : public myStack<T> {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* _top;
    size_t _size;

public:
    LinkedStack()
        : _top(nullptr)
        , _size(0)
    {
    }
    ~LinkedStack();

    LinkedStack(const LinkedStack& other) = delete;
    LinkedStack& operator=(const LinkedStack& other) = delete;
    LinkedStack& operator=(LinkedStack&& other);
    LinkedStack(LinkedStack&& other);

    void push(T& item);
    void push(T&& item);
    void pop();

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }

    T& top();
};

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    while (!empty()) {
        pop();
    }
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack&& other)
{
    _top = other._top;
    _size = other._size;
    other._top = nullptr;
    other._size = 0;
    return *this;
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack&& other)
{
    *this = std::move(other);
}

template <typename T>
void LinkedStack<T>::push(T& item)
{
    Node* newNode = new Node;
    newNode->data = item;
    newNode->next = _top;
    _top = newNode;
    ++_size;
}

template <typename T>
void LinkedStack<T>::push(T&& item)
{
    this->push(std::forward<T>(item));
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    Node* temp = _top;
    _top = _top->next;
    delete temp;
    --_size;
}

template <typename T>
T& LinkedStack<T>::top()
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    } else {
        return _top->data;
    }
}