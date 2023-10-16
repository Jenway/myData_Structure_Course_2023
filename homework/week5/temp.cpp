#include <iostream>

using namespace std;

template <typename T>
class queue {
public:
    virtual ~queue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;

    // 以下为扩充的函数

    virtual void input() = 0;
    virtual void output() = 0;
    virtual void split(queue<T>& q1, queue<T>& q2) = 0;
    virtual void merge(queue<T>& q1, queue<T>& q2) = 0;
};

template <typename T>
class extendedQueue : public queue<T> {
public:
    virtual void input() = 0;
    virtual void output() = 0;
    virtual void split(queue<T>& q1, queue<T>& q2) = 0;
    virtual void merge(queue<T>& q1, queue<T>& q2) = 0;
};

template <typename T>
class arrayQueue;

template <typename T>
class extendedarrayQueue : public arrayQueue<T>, public extendedQueue<T> {
public:
    // 以下为扩充的函数
    void input() override
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            T temp;
            cin >> temp;
            this->push(temp);
        }
    }
    void output() override
    {
        while (!this->empty()) {
            cout << this->front() << " ";
            this->pop();
        }
        cout << endl;
    }
    void split(queue<T>& q1, queue<T>& q2) override
    {
        // 1 个队列包含 1 3 5 另一个队列包含 2 4 6..
        int cnt = 0;
        while (!this->empty()) {
            if (cnt % 2 == 0) {
                q1.push(this->front());
            } else {
                q2.push(this->front());
            }
            this->pop();
            cnt++;
        }
    }
    void merge(queue<T>& q1, queue<T>& q2) override
    {
        // 合并前后，每一个队列的元素其相对顺序不变
        while (!q1.empty() || !q2.empty()) {
            if (!q1.empty()) {
                this->push(q1.front());
                q1.pop();
            }
            if (!q2.empty()) {
                this->push(q2.front());
                q2.pop();
            }
        }
    }
};