// abstact class for stack

#if !defined(MYSTACK_H)
#define MYSTACK_H
#include <cstddef>

template <typename T>
class myStack {
public:
    virtual void push(T& item) = 0;
    virtual void push(T&& item) = 0;
    virtual void pop() = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual T& top() = 0;
};

#endif // MYSTACK_H