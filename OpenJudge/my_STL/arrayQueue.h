template <typename T>
class ArrayQueue {
private:
    T* data;
    int _size;
    int capacity;
    int _front;
    int _back;

    void resize(int newCapacity);
    int nextIndex(int index);

public:
    ArrayQueue()
        : _size(0)
        , capacity(10)
        , _front(0)
        , _back(0)
    {
        data = new T[capacity];
    }
    ~ArrayQueue()
    {
        delete[] data;
    }
    void push(const T& val);
    void pop();
    T& front() { return data[_front]; }
    int size() const { return _size; }
    bool empty() const { return _size == 0; }
};

template <typename T>
void ArrayQueue<T>::push(const T& val)
{
    if (_size == capacity) {
        resize(capacity * 2);
    }
    data[_back] = val;
    _back = nextIndex(_back);
    _size++;
}

template <typename T>
void ArrayQueue<T>::pop()
{
    if (_size == 0) {
        throw "pop from empty queue";
    } else {
        _front = nextIndex(_front);
        _size--;
    }
}

template <typename T>
void ArrayQueue<T>::resize(int newCapacity)
{
    if (newCapacity == _size) {
        return;
    } else if (newCapacity < _size) {
        return; // tobe done
    } else {
        T* new_data = new T[newCapacity];
        for (int i = 0; i < _size; i++) {
            new_data[i] = data[(_front + i) % _size];
        }
        delete[] data;
        data = new_data;
        _front = 0;
        _back = _size;
        capacity = newCapacity;
    }
}

template <typename T>
int ArrayQueue<T>::nextIndex(int index)
{
    return (index + 1) % capacity;
}
