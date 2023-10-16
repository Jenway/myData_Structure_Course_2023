// sparse matrix using an extended array list

#ifndef sparseMatrix_
#define sparseMatrix_

#include "extendedArrayList.h"
#include "matrixTerm.h"
#include "myExceptions.h"
#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class sparseMatrix {
    friend ostream& operator<<(ostream&, sparseMatrix<int>&);
    friend istream& operator>>(istream&, sparseMatrix<int>&);

public:
    void transpose(sparseMatrix<T>& b);
    void add(sparseMatrix<T>& b, sparseMatrix<T>& c);

    matrixTerm<T> get(int theRow, int theCol)
    {
        // return a(i,j)
        if (theRow < 1 || theRow > rows || theCol < 1 || theCol > cols) {
            ostringstream s;
            s << "theRow = " << theRow << " theCol = " << theCol
              << " are out of range";
            throw illegalParameterValue(s.str());
        }

        // using sequential search
        for (typename arrayList<matrixTerm<T>>::iterator i = terms.begin();
             i != terms.end(); i++) {
            if ((*i).row == theRow && (*i).col == theCol) {
                return *i;
            }
        }

        // element not found, create and return a zero element
        matrixTerm<T> zero;
        zero.row = theRow;
        zero.col = theCol;
        zero.value = 0;
        return zero;
    }
    void set(int theRow, int theCol, const T& theValue)
    {
        matrixTerm<T> mTerm;
        mTerm.row = theRow;
        mTerm.col = theCol;
        mTerm.value = theValue;

        // set a(i,j) = theValue
        int index = 0;
        typename arrayList<matrixTerm<T>>::iterator itr = terms.begin();
        // Find the position in the terms list
        for (; itr != terms.end() && (*itr).row < theRow; itr++, index++) { }

        if (itr != terms.end() && (*itr).row == theRow) {
            // If the row is the same, find the position in the row
            for (; itr != terms.end() && (*itr).row == theRow && (*itr).col < theCol; itr++, index++) { }
            if (itr != terms.end() && (*itr).row == theRow && (*itr).col == theCol) {
                // If the term already exists, replace the value
                (*itr).value = theValue;
                return;
            } else {
                // If we reached the end or found a different row, insert the term
                terms.insert(index, mTerm);
                this->rows = max(this->rows, theRow);
                this->cols = max(this->cols, theCol);
            }
        } else {
            terms.insert(index, mTerm);
            this->rows = max(this->rows, theRow);
            this->cols = max(this->cols, theCol);
        }
    }

private:
    int rows, // number of rows in matrix
        cols; // number of columns in matrix
    arrayList<matrixTerm<T>> terms;
    // list of nonzero terms
};

// overload <<
template <class T>
ostream& operator<<(ostream& out, sparseMatrix<T>& x)
{ // Put x in output stream.

    // put matrix characteristics
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms.size() << endl;

    // put terms, one per line
    for (typename arrayList<matrixTerm<T>>::iterator i = x.terms.begin();
         i != x.terms.end(); i++)
        out << "a(" << (*i).row << ',' << (*i).col
            << ") = " << (*i).value << endl;

    return out;
}

// overload >>
template <class T>
istream& operator>>(istream& in, sparseMatrix<T>& x)
{ // Input a sparse matrix.

    // input matrix characteristics
    int numberOfTerms;
    cout << "Enter number of rows, columns, and #terms"
         << endl;
    in >> x.rows >> x.cols >> numberOfTerms;

    // set size of x.terms and ensure enough capacity
    x.terms.reSet(numberOfTerms);

    // input terms
    matrixTerm<T> mTerm;
    for (int i = 0; i < numberOfTerms; i++) {
        cout << "Enter row, column, and value of term "
             << (i + 1) << endl;
        in >> mTerm.row >> mTerm.col >> mTerm.value;
        x.terms.set(i, mTerm);
    }

    return in;
}

/****************************************************************/
// explict code tooverload with T = int for test as compiler
// unable to generate

// overload <<
template <typename T>
ostream& operator<<(ostream& out, sparseMatrix<int>& x)
{ // Put x in output stream.

    // put matrix characteristics
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms.size() << endl;

    // put terms, one per line
    for (arrayList<matrixTerm<int>>::iterator i = x.terms.begin();
         i != x.terms.end(); i++)
        out << "a(" << (*i).row << ',' << (*i).col
            << ") = " << (*i).value << endl;

    return out;
}

// overload >>
template <typename T>
istream& operator>>(istream& in, sparseMatrix<int>& x)
{ // Input a sparse matrix.

    // input matrix characteristics
    int numberOfTerms;
    cout << "Enter number of rows, columns, and #terms"
         << endl;
    in >> x.rows >> x.cols >> numberOfTerms;

    // set size of x.terms and ensure enough capacity
    x.terms.reSet(numberOfTerms);

    // input terms
    matrixTerm<int> mTerm;
    for (int i = 0; i < numberOfTerms; i++) {
        cout << "Enter row, column, and value of term "
             << (i + 1) << endl;
        in >> mTerm.row >> mTerm.col >> mTerm.value;
        x.terms.set(i, mTerm);
    }

    return in;
}
/****************************************************************/
template <class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{ // Return transpose of *this in b.

    // set transpose characteristics
    b.cols = rows;
    b.rows = cols;
    b.terms.reSet(terms.size());

    // initialize to compute transpose
    int* colSize = new int[cols + 1];
    int* rowNext = new int[cols + 1];

    // find number of entries in each column of *this
    for (int i = 1; i <= cols; i++) // initialize
        colSize[i] = 0;
    for (typename arrayList<matrixTerm<T>>::iterator i = terms.begin();
         i != terms.end(); i++)
        colSize[(*i).col]++;

    // find the starting point of each row of b
    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    // perform the transpose copying from *this to b
    matrixTerm<T> mTerm;
    for (typename arrayList<matrixTerm<T>>::iterator i = terms.begin();
         i != terms.end(); i++) {
        int j = rowNext[(*i).col]++; // position in b
        mTerm.row = (*i).col;
        mTerm.col = (*i).row;
        mTerm.value = (*i).value;
        b.terms.set(j, mTerm);
    }
}

template <class T>
void sparseMatrix<T>::add(sparseMatrix<T>& b, sparseMatrix<T>& c)
{ // Compute c = (*this) + b.

    // verify compatibility
    if (rows != b.rows || cols != b.cols)
        throw matrixSizeMismatch(); // incompatible matrices

    // set characteristics of result c
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    int cSize = 0;

    // define iterators for *this and b
    typename arrayList<matrixTerm<T>>::iterator it = terms.begin();
    typename arrayList<matrixTerm<T>>::iterator ib = b.terms.begin();
    typename arrayList<matrixTerm<T>>::iterator itEnd = terms.end();
    typename arrayList<matrixTerm<T>>::iterator ibEnd = b.terms.end();

    // move through *this and b adding like terms
    while (it != itEnd && ib != ibEnd) {
        // row-major index plus cols of each term
        int tIndex = (*it).row * cols + (*it).col;
        int bIndex = (*ib).row * cols + (*ib).col;

        if (tIndex < bIndex) { // b term comes later
            c.terms.insert(cSize++, *it);
            it++;
        } else {
            if (tIndex == bIndex) { // both in same position

                // append to c only if sum not zero
                if ((*it).value + (*ib).value != 0) {
                    matrixTerm<T> mTerm;
                    mTerm.row = (*it).row;
                    mTerm.col = (*it).col;
                    mTerm.value = (*it).value + (*ib).value;
                    c.terms.insert(cSize++, mTerm);
                }

                it++;
                ib++;
            } else { // a term comes later
                c.terms.insert(cSize++, *ib);
                ib++;
            }
        }
    }

    // copy over remaining terms
    for (; it != itEnd; it++)
        c.terms.insert(cSize++, *it);
    for (; ib != ibEnd; ib++)
        c.terms.insert(cSize++, *ib);
}

#endif
