#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
private:
    typedef struct node {
        T val;
        struct node* next;
        node(T&& val, struct node* next = nullptr)
        {
            this->val = val;
            this->next = next;
        }
    } Node;
    Node* head;
    int size;

public:
    class iterator {
    private:
        Node* current;

    public:
        friend class LinkedList<T>;
        iterator(Node* current)
            : current(current)
        {
        }
        iterator(const iterator& rhs)
            : current(rhs.current)
        {
        }
        iterator operator=(const iterator& rhs)
        {
            current = rhs.current;
            return *this;
        }
        ~iterator() = default;

        T& operator*() const
        {
            return current->val;
        }
        T* operator->() const
        {
            return &(current->val);
        }
        iterator operator++();
        iterator operator++(int);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        operator bool() const;
        iterator operator+(const int& n) const;
    };

    iterator begin() const;
    iterator end() const;

    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList& list);
    LinkedList(const LinkedList&& list);

    LinkedList& operator=(const LinkedList& list);
    LinkedList& operator=(LinkedList&& list);

    void push_back(T& val);

    void push_back(T&& val);

    void clear();

    void resize(int newSize);

    int getSize() const;
};

// <--- implement of LinkedList --->
template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& list)
{
    head = nullptr;
    Node* p = list.head;
    while (p != nullptr) {
        push_back(p->val);
        p = p->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList&& list)
{
    if (this == &list) {
        return;
    }
    head = list.head;
    list.head = nullptr;
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& list)
{
    if (this == &list) {
        return *this;
    }
    clear();
    Node* p = list.head;
    while (p != nullptr) {
        T val = p->val;
        push_back(std::move(val));
        p = p->next;
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& list)
{
    if (this == &list) {
        return *this;
    }
    clear();
    head = list.head;
    list.head = nullptr;
    return *this;
}

template <typename T>
void LinkedList<T>::push_back(T&& val)
{
    Node* p = head;
    if (p == nullptr) {
        head = new Node(std::move(val));
        return;
    }
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = new Node(std::move(val), nullptr);
    size++;
}

template <typename T>
void LinkedList<T>::push_back(T& val)
{
    Node* p = head;
    if (p == nullptr) {
        head = new Node(std::move(val));
        return;
    }
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = new Node(T(val), nullptr);
    size++;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node* p = head;
    while (p != nullptr) {
        head = p->next;
        delete p;
        p = head;
    }
}

template <typename T>
void LinkedList<T>::resize(int newSize)
{
    // do nothing
}

template <typename T>
int LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const
{
    return LinkedList<T>::iterator(head);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() const
{
    return LinkedList<T>::iterator(nullptr);
}

// <--- implement of iterator --->

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++()
{
    // e.g. ++it
    if (current == nullptr) {
        throw "out of range";
    }
    current = current->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int)
{
    // e.g. it++
    if (current == nullptr) {
        throw "out of range";
    }
    LinkedList<T>::iterator it = *this;
    ++(*this);
    return it;
}

template <typename T>
bool LinkedList<T>::iterator::operator==(const LinkedList<T>::iterator& rhs) const
{
    return current == rhs.current;
}

template <typename T>
bool LinkedList<T>::iterator::operator!=(const LinkedList<T>::iterator& rhs) const
{
    return current != rhs.current;
}

template <typename T>
LinkedList<T>::iterator::operator bool() const
{
    return current != nullptr;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator+(const int& n) const
{
    LinkedList<T>::iterator it = *this;
    for (int i = 0; i < n; i++) {
        ++it;
    }
    return it;
}
