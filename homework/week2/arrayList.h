// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE

#ifndef arrayList_
#define arrayList_

#include "changeLength1D.h"
#include "linearList.h"
#include "myExceptions.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>


using namespace std;

template <class T>
class arrayList : public linearList<T> {
public:
    // constructor, copy constructor and destructor
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() { delete[] element; }

    // ADT methods
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    // additional method
    int capacity() const { return arrayLength; }

    /*---------FOR HOMEWORK 2---------*/

    // 11 编写方法arrayList<T>::push_back，它把元素 theElcment 插到线性表的右端。不要利用 insert 方法。方法的时间复杂度是多少? 测试你的代码。
    void push_back(const T& theElement)
    {
        if (listSize == arrayLength) { // no space, double capacity
            changeLength1D(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }
        element[listSize] = theElement;
        listSize++;
    }
    // 12) 编写方法arrayList<T>:pop back，剔蚌敝茨炳宝版按抚驳线性表右端的元素删除。不要利用erase 方法。法的时间复杂度是多少?测试你的代码。
    void pop_back()
    {
        if (listSize == 0) {
            throw illegalIndex("listSize == 0");
        }
        listSize--;
    }
    // 14编写方法arrayList<T>:reserve(theCapacity)，它把数组的容量改变为当前容量和theCapacit的较大者。测试你的代码。
    void reserve(int theCapacity)
    {
        if (theCapacity < 1) {
            ostringstream s;
            s << "Initial capacity = " << theCapacity << " Must be > 0";
            throw illegalParameterValue(s.str());
        }
        if (theCapacity > arrayLength) {
            changeLength1D(element, arrayLength, theCapacity);
            arrayLength = theCapacity;
        }
    }
    // 16 编写方法arrayList<T>::clear，它使线性表为空。方法的复杂度是多少?测试你的代码
    void clear()
    {
        listSize = 0;
    }

    /*————————————————THE END--——————————*/
protected:
    void checkIndex(int theIndex) const;
    // throw illegalIndex if theIndex invalid
    T* element; // 1D array to hold list elements
    int arrayLength; // capacity of the 1D array
    int listSize; // number of elements in list
};

template <class T>
arrayList<T>::arrayList(int initialCapacity)
{ // Constructor.
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{ // Copy constructor.
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const
{ // Verify that theIndex is between 0 and listSize - 1.
    if (theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T& arrayList<T>::get(int theIndex) const
{ // Return element whose index is theIndex.
  // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T& theElement) const
{ // Return index of first occurrence of theElement.
  // Return -1 if theElement not in list.

    // search for theElement
    int theIndex = (int)(find(element, element + listSize, theElement)
        - element);

    // check if theElement was found
    if (theIndex == listSize)
        // not found
        return -1;
    else
        return theIndex;
}

template <class T>
void arrayList<T>::erase(int theIndex)
{ // Delete the element whose index is theIndex.
  // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // valid index, shift elements with higher index
    copy(element + theIndex + 1, element + listSize,
        element + theIndex);

    element[--listSize].~T(); // invoke destructor
}

template <class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{ // Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > listSize) { // invalid index
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // valid index, make sure we have space
    if (listSize == arrayLength) { // no space, double capacity
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // shift elements right one position
    copy_backward(element + theIndex, element + listSize,
        element + listSize + 1);

    element[theIndex] = theElement;

    listSize++;
}

template <class T>
void arrayList<T>::output(ostream& out) const
{ // Put the list into the stream out.
    copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}

#endif
