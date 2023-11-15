#if !defined(LINKEDDEQUE_H)
#define LINKEDDEQUE_H

#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <utility> // std::move

template <typename T>
class linkedDeque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };
    Node* _front;
    Node* _rear;
    size_t _size;

public:
    linkedDeque()
        : _front(nullptr)
        , _rear(nullptr)
        , _size(0)
    {
    }
    ~linkedDeque()
    {
        while (!empty()) {
            pop_front();
        }
    }

    linkedDeque(const linkedDeque& other) = delete;
    linkedDeque& operator=(const linkedDeque& other) = delete;
    linkedDeque& operator=(linkedDeque&& other);
    linkedDeque(linkedDeque&& other);

    void push_front(T& item);
    void push_front(T&& item);
    void push_back(T& item);
    void push_back(T&& item);
    void pop_front();
    void pop_back();

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }

    T& front();
    T& back();
};

template <typename T>
linkedDeque<T>& linkedDeque<T>::operator=(linkedDeque&& other)
{
    _front = other._front;
    _rear = other._rear;
    _size = other._size;
    other._front = nullptr;
    other._rear = nullptr;
    other._size = 0;
    return *this;
}

template <typename T>
linkedDeque<T>::linkedDeque(linkedDeque&& other)
{
    *this = std::move(other);
}

template <typename T>
void linkedDeque<T>::push_front(T& item)
{
    Node* newNode = new Node { item, nullptr, nullptr };
    if (empty()) {
        _front = newNode;
        _rear = newNode;
    } else {
        newNode->next = _front;
        _front->prev = newNode;
        _front = newNode;
    }
    ++_size;
}

template <typename T>
void linkedDeque<T>::push_front(T&& item)
{
    this->push_front(item);
}

template <typename T>
void linkedDeque<T>::push_back(T& item)
{
    Node* newNode = new Node { item, nullptr, nullptr };
    if (empty()) {
        _front = newNode;
        _rear = newNode;
    } else {
        newNode->prev = _rear;
        _rear->next = newNode;
        _rear = newNode;
    }
    ++_size;
}

template <typename T>
void linkedDeque<T>::push_back(T&& item)
{
    this->push_back(item);
}

template <typename T>
void linkedDeque<T>::pop_front()
{
    if (empty()) {
        throw std::out_of_range("pop_front: empty deque");
    }
    Node* temp = _front;
    _front = _front->next;
    if (_front == nullptr) {
        _rear = nullptr;
    } else {
        _front->prev = nullptr;
    }
    delete temp;
    --_size;
}

template <typename T>
void linkedDeque<T>::pop_back()
{
    if (empty()) {
        throw std::out_of_range("pop_back: empty deque");
    }
    Node* temp = _rear;
    _rear = _rear->prev;
    if (_rear == nullptr) {
        _front = nullptr;
    } else {
        _rear->next = nullptr;
    }
    delete temp;
    --_size;
}

template <typename T>
T& linkedDeque<T>::front()
{
    if (empty()) {
        throw std::out_of_range("front: empty deque");
    }
    return _front->data;
}

template <typename T>
T& linkedDeque<T>::back()
{
    if (empty()) {
        throw std::out_of_range("back: empty deque");
    }
    return _rear->data;
}

#endif // LINKEDDEQUE_H