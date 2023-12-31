// linked implementation of an extended linear list
// derives from abstract class extendedLinearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for extendedChain included

#ifndef extendedChain_
#define extendedChain_

#include "chain.h"
#include "chainWithIterator.h"
#include "extendedLinearList.h"
#include "myExceptions.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T>
class extendedChain : public chain<T>, public extendedLinearList<T> {
public:
    // constructor and copy constructor
    extendedChain(int initialCapacity = 10)
        : chain<T>(initialCapacity)
    {
    }
    extendedChain(const extendedChain<T>& c)
        : chain<T>(c)
    {
    }

    // ADT methods
    bool empty() const { return this->listSize == 0; }
    int size() const { return this->listSize; }
    T& get(int theIndex) const
    {
        return chain<T>::get(theIndex);
    }
    int indexOf(const T& theElement) const
    {
        return chain<T>::indexOf(theElement);
    }
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void clear()
    { // Delete all nodes in chain.
        while (this->firstNode != NULL) { // delete this->firstNode
            chainNode<T>* nextNode = this->firstNode->next;
            delete this->firstNode;
            this->firstNode = nextNode;
        }
        this->listSize = 0;
    }
    void push_back(const T& theElement);
    void output(ostream& out) const
    {
        chain<T>::output(out);
    }

    // additional method
    void zero()
    {
        this->firstNode = NULL;
        this->listSize = 0;
    }

protected:
    chainNode<T>* lastNode; // pointer to last node in chain
};

template <typename T>
extendedChain<T> meld(extendedChain<T> a, extendedChain<T> b)
{
    extendedChain<T> c = extendedChain<T>();
    int sizeA = a.size(), sizeB = b.size();
    while (sizeA > 0 || sizeB > 0) {
        if (sizeA > 0) {
            c.push_back(a.get(a.size() - sizeA));
            sizeA--;
        }
        if (sizeB > 0) {
            c.push_back(b.get(b.size() - sizeB));
            sizeB--;
        }
    }
    return c;
}

template <class T>
void extendedChain<T>::erase(int theIndex)
{ // Delete the element whose index is theIndex.
  // Throw illegalIndex exception if no such element.
    this->checkIndex(theIndex);

    // valid index, locate node with element to delete
    chainNode<T>* deleteNode;
    if (theIndex == 0) { // remove first node from chain
        deleteNode = this->firstNode;
        this->firstNode = this->firstNode->next;
    } else { // use p to get to predecessor of desired node
        chainNode<T>* p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next; // remove deleteNode from chain
        if (deleteNode == lastNode)
            lastNode = p;
    }
    this->listSize--;
    delete deleteNode;
}

template <class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{ // Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > this->listSize) { // invalid index
        ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0) { // insert at front
        this->firstNode = new chainNode<T>(theElement, this->firstNode);
        if (this->listSize == 0)
            lastNode = this->firstNode;
    } else { // find predecessor of new element
        chainNode<T>* p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        // insert after p
        p->next = new chainNode<T>(theElement, p->next);
        if (this->listSize == theIndex)
            lastNode = p->next;
    }
    this->listSize++;
}

template <class T>
void extendedChain<T>::push_back(const T& theElement)
{ // Insert theElement at the end of the chain.
    chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
    if (this->firstNode == NULL)
        // chain is empty
        this->firstNode = lastNode = newNode;
    else { // attach next to lastNode
        lastNode->next = newNode;
        lastNode = newNode;
    }
    this->listSize++;
}

#endif
