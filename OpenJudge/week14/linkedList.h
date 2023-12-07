#if !defined(LINKEDLIST_H)
#define LINKEDLIST_H

#include <stdexcept> // for std::out_of_range

template <typename T>
class LinkedList {
protected:
    typedef struct node {
        T val;
        struct node* next;
        struct node* prev;
        node(T val, struct node* next = nullptr, struct node* prev = nullptr)
            : val(val)
            , next(next)
            , prev(prev)
        {
        }
    } Node;
    Node* head;
    Node* tail;
    int _size;

public:
    class Iterator {
    private:
        Node* current;

    public:
        friend class LinkedList<T>;
        Iterator(Node* current)
            : current(current)
        {
        }
        ~Iterator() = default;

        T operator*() const;
        Iterator operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        operator bool() const;
        Iterator operator+(const int& n) const;
    };

    LinkedList();
    LinkedList(const LinkedList& list);
    ~LinkedList();

    // Element access
    T& front() { return head->val; }
    T& back() { return tail->val; }

    // Iterators
    Iterator begin();
    Iterator end();

    // Capacity
    bool empty() const { return head == nullptr; }
    int size() const { return _size; }

    // Modifiers
    void clear();
    Iterator insert(const Iterator& pos, T val);
    bool erase(Iterator pos);
    void push_back(T& val);
    void push_back(T&& val) { push_back(val); }
    void pop_back();
    void push_front(T& val);
    void push_front(T&& val) { push_front(val); }
    void pop_front();

    // Operation
    LinkedList merge(LinkedList& list);
    bool remove(T val);
    void reverse();
    void sort();

    int getIdx(T val) const;
    Iterator getIndex(T val) const;
};

// <--- implement of LinkedList --->
template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr)
    , tail(nullptr)
    , _size(0)

{
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& list)
{
    head = nullptr;
    tail = nullptr;
    _size = 0;
    Node* p = list.head;
    while (p != nullptr) {
        push_back(p->val);
        p = p->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return LinkedList<T>::Iterator(head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return LinkedList<T>::Iterator(nullptr);
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
    head = nullptr;
    tail = nullptr;
    _size = 0;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::insert(const LinkedList<T>::Iterator& pos, T val)
{
    if (pos == begin()) {
        head = new Node(val, head);
        if (head->next) {
            head->next->prev = head;
        } else {
            tail = head;
        }
        _size++;
        return Iterator(head);
    } else if (pos == end()) {
        push_back(val);
        return Iterator(tail);
    } else {
        Node* newNode = new Node(val, pos.current, pos.current->prev);
        pos.current->prev = newNode;
        newNode->prev->next = newNode;
        _size++;
        return Iterator(newNode);
    }
}

template <typename T>
bool LinkedList<T>::erase(LinkedList<T>::Iterator pos)
{
    if (pos) {
        if (pos.current->prev) {
            pos.current->prev->next = pos.current->next;
        } else {
            head = pos.current->next;
        }
        if (pos.current->next) {
            pos.current->next->prev = pos.current->prev;
        } else {
            tail = pos.current->prev;
        }
        delete pos.current;
        _size--;
        return true;
    } else {
        return false;
    }
}

template <typename T>
void LinkedList<T>::push_back(T& val)
{
    if (head == nullptr) {
        head = new Node(val);
        tail = head;
    } else {
        tail->next = new Node(val, nullptr, tail);
        tail = tail->next;
    }
    _size++;
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if (tail != nullptr) {
        Node* p = tail;
        tail = tail->prev;
        delete p;
        _size--;
    }
    if (tail == nullptr) {
        head = nullptr;
    }
}

template <typename T>
void LinkedList<T>::push_front(T& val)
{
    if (head == nullptr) {
        head = new Node(val);
        tail = head;
    } else {
        head->prev = new Node(val, head);
        head = head->prev;
    }
    _size++;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if (head != nullptr) {
        Node* p = head;
        head = head->next;
        delete p;
        _size--;
    }
    if (head == nullptr) {
        tail = nullptr;
    }
}

template <typename T>
LinkedList<T> LinkedList<T>::merge(LinkedList<T>& list)
{
    LinkedList<T> newList = LinkedList<T>();
    Node *p = head, *q = list.head;
    while (p != nullptr || q != nullptr) {
        if (p == nullptr) {
            newList.push_back(q->val);
            q = q->next;
        } else if (q == nullptr) {
            newList.push_back(p->val);
            p = p->next;
        } else if (p->val < q->val) {
            newList.push_back(p->val);
            p = p->next;
        } else {
            newList.push_back(q->val);
            q = q->next;
        }
    }
    return newList;
}

template <typename T>
bool LinkedList<T>::remove(T val)
{
    return this->erase(this->getIndex(val));
}

template <typename T>
void LinkedList<T>::reverse()
{
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
void LinkedList<T>::sort()
{
    Node *p, *q;
    for (p = head; p != nullptr; p = p->next) {
        for (q = p->next; q != nullptr; q = q->next) {
            if (p->val > q->val) {
                T tmp = p->val;
                p->val = q->val;
                q->val = tmp;
            }
        }
    }
}

template <typename T>
int LinkedList<T>::getIdx(T val) const
{
    Node* p = head;
    int idx = 0;
    while (p != nullptr) {
        if (p->val == val) {
            return idx;
        }
        p = p->next;
        idx++;
    }
    return -1;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::getIndex(T val) const
{

    for (Node* p = head; p != nullptr; p = p->next) {
        if (p->val == val) {
            return LinkedList<T>::Iterator(p);
        }
    }
    return LinkedList<T>::Iterator(nullptr);
}

// <--- implement of iterator --->

template <typename T>
T LinkedList<T>::Iterator::operator*() const
{
    return current->val;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++()
{
    // e.g. ++it
    if (current == nullptr) {
        throw std::out_of_range("out of range");
    }
    current = current->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    // e.g. it++
    if (current == nullptr) {
        throw std::out_of_range("out of range");
    }
    LinkedList<T>::Iterator it = *this;
    ++(*this);
    return it;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const LinkedList<T>::Iterator& rhs) const
{
    return current == rhs.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const LinkedList<T>::Iterator& rhs) const
{
    return current != rhs.current;
}

template <typename T>
LinkedList<T>::Iterator::operator bool() const
{
    return current != nullptr;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator+(const int& n) const
{
    LinkedList<T>::Iterator it = *this;
    for (int i = 0; i < n; i++) {
        ++it;
    }
    return it;
}

#endif // LINKEDLIST_H