#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <utility> // std::move

template <typename T>
class linkedQueue {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* _front;
    Node* _rear;
    size_t _size;

public:
    linkedQueue()
        : _front(nullptr)
        , _rear(nullptr)
        , _size(0)
    {
    }
    ~linkedQueue()
    {
        while (!empty()) {
            pop();
        }
    }

    linkedQueue(const linkedQueue& other) = delete;
    linkedQueue& operator=(const linkedQueue& other) = delete;
    linkedQueue& operator=(linkedQueue&& other);
    linkedQueue(linkedQueue&& other);

    void push(T& item);
    void push(T&& item);
    void pop();

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }

    T& front();
    T& rear();
};

template <typename T>
linkedQueue<T>& linkedQueue<T>::operator=(linkedQueue&& other)
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
linkedQueue<T>::linkedQueue(linkedQueue&& other)
{
    *this = std::move(other);
}

template <typename T>
void linkedQueue<T>::push(T& item)
{
    Node* newNode = new Node { item, nullptr };
    if (empty()) {
        _front = newNode;
        _rear = newNode;
    } else {
        _rear->next = newNode;
        _rear = newNode;
    }
    _size++;
}

template <typename T>
void linkedQueue<T>::push(T&& item)
{
    this->push(std::forward<T&>(item));
}

template <typename T>
void linkedQueue<T>::pop()
{
    if (empty()) {
        throw std::out_of_range("queue is empty");
    }
    Node* temp = _front;
    _front = _front->next;
    delete temp;
    _size--;
}

template <typename T>
T& linkedQueue<T>::front()
{
    if (empty()) {
        throw std::out_of_range("queue is empty");
    }
    return _front->data;
}

template <typename T>
T& linkedQueue<T>::rear()
{
    if (empty()) {
        throw std::out_of_range("queue is empty");
    }
    return _rear->data;
}