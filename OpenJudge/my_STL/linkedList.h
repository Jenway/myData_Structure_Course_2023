#include <iostream>

template <typename T>
class LinkedList {
private:
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

    Iterator begin();
    Iterator end();

    LinkedList();
    LinkedList(const LinkedList& list);
    ~LinkedList();

    int getIdx(T val) const;
    Iterator getIndex(T val) const;

    void push_back(T val);

    void insert(Iterator pos, T val);

    bool erase(Iterator pos);
    bool remove(T val);
    void clear();

    void sort();
    void reverse();
    LinkedList merge(LinkedList& list);

    // for test
    void LOG_output()
    {
        for (auto i : *this) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    void LOG_output(std::stringstream& ss)
    {
        for (auto i : *this) {
            ss << i << " ";
        }
    }
};

// <--- implement of LinkedList --->
template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
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
LinkedList<T>::~LinkedList()
{
    clear();
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

template <typename T>
void LinkedList<T>::push_back(T val)
{
    Node* p = head;
    if (p == nullptr) {
        head = new Node(val);
        return;
    }
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = new Node(val, nullptr, p);
}

template <typename T>
void LinkedList<T>::insert(LinkedList<T>::Iterator pos, T val)
{
    if (pos == begin()) {
        head = new Node(val, head);
        if (head->next) {
            head->next->prev = head;
        }
    } else if (pos == end()) {
        push_back(val);
    } else {
        Node* newNode = new Node(val, pos.current, pos.current->prev);
        pos.current->prev = newNode;
        newNode->prev->next = newNode;
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
        }
        delete pos.current;
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool LinkedList<T>::remove(T val)
{
    return this->erase(this->getIndex(val));
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
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return LinkedList<T>::Iterator(head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
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
        throw "out of range";
    }
    current = current->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    // e.g. it++
    if (current == nullptr) {
        throw "out of range";
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
