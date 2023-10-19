#include <iostream>
using namespace std;

template <typename T>
class arrayList {
private:
    T* array;
    int size;
    int capacity;

public:
    class iterator {
    private:
        T* ptr;

    public:
        iterator(T* ptr)
            : ptr(ptr)
        {
        }

        T& operator*() const
        {
            return *ptr;
        }

        T* operator->() const
        {
            return ptr;
        }

        iterator& operator++()
        {
            ++ptr;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        bool operator!=(const iterator& other) const
        {
            return ptr != other.ptr;
        }
    };

    iterator begin() const
    {
        return iterator(array);
    }

    iterator end() const
    {
        return iterator(array + size);
    }

    arrayList(int capacity = 10)
        : capacity(capacity)
    {
        array = new T[capacity];
        size = 0;
    }
    ~arrayList()
    {
        delete[] array;
    }
    arrayList(const arrayList& list);
    arrayList(const arrayList&& list);
    arrayList& operator=(const arrayList& list);
    arrayList& operator=(arrayList&& list);

    void push_back(const T& data);

    void push_back(T&& data);

    int getSize() const;

    void resize(int newSize);

    void set(int index, T&& data);

    T& operator[](int index);

    void pop_back();

    void clear();
};

template <typename T>
arrayList<T>::arrayList(const arrayList& list)
{
    capacity = list.capacity;
    size = list.size;
    array = new T[capacity];
    for (int i = 0; i < size; i++) {
        array[i] = list.array[i];
    }
}

template <typename T>
arrayList<T>::arrayList(const arrayList&& list)
{
    capacity = list.capacity;
    size = list.size;
    array = list.array;
    list.array = nullptr;
}
template <typename T>
arrayList<T>& arrayList<T>::operator=(const arrayList& list)
{
    if (this == &list) {
        return *this;
    }
    delete[] array;
    capacity = list.capacity;
    size = list.size;
    array = new T[capacity];
    for (int i = 0; i < size; i++) {
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
    capacity = list.capacity;
    size = list.size;
    array = list.array;
    list.array = nullptr;
    return *this;
}

template <typename T>
void arrayList<T>::push_back(const T& data)
{
    if (size == capacity) {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[size++] = T(data);
}
template <typename T>
void arrayList<T>::push_back(T&& data)
{
    if (size == capacity) {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[size++] = std::move(data);
}
template <typename T>
int arrayList<T>::getSize() const
{
    return size;
}
template <typename T>
void arrayList<T>::resize(int newSize)
{
    if (newSize > capacity) {
        capacity = newSize;
        T* newArray = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    size = newSize;
}
template <typename T>
void arrayList<T>::set(int index, T&& data)
{
    if (index < 0 || index >= size) {
        return;
    }
    // hard copy
    array[index] = std::move(data);
}
template <typename T>
T& arrayList<T>::operator[](int index)
{
    return array[index];
}

template <typename T>
void arrayList<T>::pop_back()
{
    if (size == 0) {
        return;
    }
    size--;
}

template <typename T>
void arrayList<T>::clear()
{
    size = 0;
}