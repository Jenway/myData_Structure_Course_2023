#if !defined(_ARRAYLIST_H)
#define _ARRAYLIST_H

#include <stdexcept> // for std::out_of_range

template <typename T>
class arrayList {
private:
    T* array;
    int _size;
    int _capacity;

public:
    typedef T value_type;
    typedef const T& const_reference;
    typedef T& reference;
    typedef T* pointer;
    typedef int size_type;

    class iterator {
    private:
        T* ptr;

    public:
        iterator(T* ptr);
        ~iterator() = default;
        T& operator*() const;
        T* operator->() const;

        iterator& operator++();
        iterator operator++(int);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

        operator bool() const { return ptr != nullptr; }
    };

    arrayList()
        : _size(0)
        , _capacity(10)
    {
        array = new T[_capacity];
    }

    arrayList(int capacity)
        : _size(capacity)
        , _capacity(capacity)
    {
        array = new T[_capacity];
        for (int i = 0; i < _capacity; i++) {
            array[i] = T();
        }
    }
    arrayList(int count, const T& value)
        : _size(count)
        , _capacity(count * 2)
    {
        array = new T[_capacity];
        for (int i = 0; i < count; i++) {
            array[i] = value;
        }
    }

    ~arrayList();
    arrayList(const arrayList& list);
    arrayList(arrayList&& list);
    arrayList& operator=(const arrayList& list);
    arrayList& operator=(arrayList&& list);
    void assign(int count, const T& value);

    // Element access
    T& at(int index);
    T& operator[](int index);
    T& front();
    T& back();
    T* data();

    // Iterators

    iterator begin() const { return iterator(array); }
    iterator end() const { return iterator(array + _size); }

    // Capacity
    bool empty() const { return _size == 0; }
    int size() const { return _size; }
    void reserve(int new_Capacity);
    int capacity() const { return _capacity; }

    // Modifiers
    void clear();
    iterator insert(const iterator position, const T& val);
    iterator insert(const iterator position, T&& val);
    iterator erase(iterator position);
    void push_back(const T& data);
    void push_back(T&& data);
    void pop_back();
    void resize(int new_Size, const T& defaultValue);
};

template <typename T>
arrayList<T>::~arrayList()
{

    // for (int i = 0; i < _size; ++i) {
    //     array[i].~T();
    // }

    delete[] array;
    array = nullptr;
}

template <typename T>
arrayList<T>& arrayList<T>::operator=(const arrayList& list)
{
    if (this == &list) {
        return *this;
    }
    delete[] array;
    _capacity = list._capacity;
    _size = list._size;
    array = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        array[i] = list.array[i];
    }
    return *this;
}
template <typename T>
arrayList<T>& arrayList<T>::operator=(arrayList&& list)
{
    if (this == &list) {
        return *this;
    }
    delete[] array;
    _capacity = list._capacity;
    _size = list._size;
    array = list.array;
    list.array = nullptr;
    return *this;
}
template <typename T>
arrayList<T>::arrayList(const arrayList& list)
{
    this->operator=(list);
}

template <typename T>
arrayList<T>::arrayList(arrayList&& list)
{
    if (this == &list) {
        return;
    }
    delete[] array;
    _capacity = list._capacity;
    _size = list._size;
    array = list.array;
    list.array = nullptr;
}

template <typename T>
void arrayList<T>::assign(int count, const T& value)
{
    if (count < 0) {
        return;
    }
    if (count > _capacity) {
        reserve(count);
    }
    for (int i = 0; i < count; i++) {
        array[i] = value;
    }
    _size = count;
}

template <typename T>
void arrayList<T>::push_back(const T& data)
{
    if (_size == _capacity) {
        _capacity *= 2;
        T* newArray = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[_size++] = data;
}
template <typename T>
void arrayList<T>::push_back(T&& data)
{
    this->push_back(data);
}

template <typename T>
void arrayList<T>::reserve(int new_Capacity)
{
    if (new_Capacity <= _capacity) {
        return;
    }
    _capacity = new_Capacity;
    T* newArray = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
}

template <typename T>
T& arrayList<T>::at(int index)
{
    return (*this)[index];
}

template <typename T>
T& arrayList<T>::operator[](int index)
{
    if (index < 0 || index >= _size) {
        throw std::out_of_range("index out of range");
    }
    return array[index];
}

template <typename T>
T& arrayList<T>::front()
{
    if (_size == 0) {
        throw std::out_of_range("index out of range");
    }
    return array[0];
}

template <typename T>
T& arrayList<T>::back()
{
    if (_size == 0) {
        throw std::out_of_range("index out of range");
    }
    return array[_size - 1];
}

template <typename T>
T* arrayList<T>::data()
{
    if (_size == 0) {
        return nullptr;
    } else {
        return array;
    }
}

template <typename T>
void arrayList<T>::pop_back()
{
    if (_size == 0) {
        return;
    }
    _size--;
}

template <typename T>
void arrayList<T>::clear()
{
    _size = 0;
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::insert(const iterator position, const T& val)
{
    if (_size == _capacity) {
        _capacity *= 2;
        T* newArray = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    int index = position - begin();
    for (int i = _size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = val;
    _size++;
    return iterator(array + index);
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::insert(const iterator position, T&& val)
{
    return insert(position, val);
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::erase(iterator position)
{
    int index = position - begin();
    for (int i = index; i < _size - 1; i++) {
        array[i] = array[i + 1];
    }
    _size--;
    return iterator(array + index);
}

template <typename T>
void arrayList<T>::resize(int new_Size, const T& defaultValue)
{
    if (new_Size < 0) {
        return;
    }
    if (new_Size > _capacity) {
        reserve(new_Size);
    }
    for (int i = _size; i < new_Size; i++) {
        array[i] = defaultValue;
    }
    _size = new_Size;
}

// iterator

template <typename T>
arrayList<T>::iterator::iterator(T* ptr)
    : ptr(ptr)
{
}

template <typename T>
T& arrayList<T>::iterator::operator*() const
{
    if (ptr == nullptr) {
        throw std::out_of_range("iterator out of range");
    } else {
        return *ptr;
    }
}

template <typename T>
T* arrayList<T>::iterator::operator->() const
{
    if (ptr == nullptr) {
        throw std::out_of_range("iterator out of range");
    } else {
        return ptr;
    }
}

template <typename T>
typename arrayList<T>::iterator& arrayList<T>::iterator::operator++()
{
    if (ptr == nullptr) {
        throw std::out_of_range("iterator out of range");
    } else {
        ptr++;
        return *this;
    }
}

template <typename T>
typename arrayList<T>::iterator arrayList<T>::iterator::operator++(int)
{
    iterator temp = *this;
    ++*this;
    return temp;
}

template <typename T>
bool arrayList<T>::iterator::operator==(const iterator& other) const
{
    return ptr == other.ptr;
}

template <typename T>
bool arrayList<T>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

#endif // _ARRAYLIST_H