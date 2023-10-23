#include <iostream>
using namespace std;

template <class T>
struct matrixTerm {
    int row;
    int col;
    T value;
};

template <class T>
class arrayList {
public:
    class Iterator {
    private:
        T* p;

    public:
        Iterator(T* t)
        {
            p = t;
        }
        T operator*()
        {
            return *p;
        }
        bool operator!=(const Iterator& i) const
        {
            return p != i.p;
        }
        T* operator->() const
        {
            return p;
        }
        Iterator operator++()
        {
            ++p;
            return p;
        }
        Iterator operator++(int)
        {
            Iterator temp = p;
            ++p;
            return temp;
        }
    };
    Iterator begin()
    {
        return Iterator(data);
    };
    Iterator end()
    {
        return Iterator(data + listsize);
    }
    arrayList(int initCapacity = 1000)
    {
        arrayLength = initCapacity;
        data = new T[arrayLength];
        listsize = 0;
    }
    ~arrayList()
    {
        delete[] data;
    }
    void clear()
    {
        delete[] data;
        listsize = 0;
    }
    void newset(int n)
    {
        data = new T[n];
        arrayLength = n;
    }
    void news(int n)
    {
        data = new T[n];
        arrayLength = n;
        listsize = n;
    }
    void push(T n)
    {
        data[listsize] = n;
        listsize++;
    }
    int arraylist()
    {
        return listsize;
    }

    T& operator[](int n)
    {
        return data[n];
    }

private:
    int arrayLength;
    int listsize;
    T* data;
};
template <class T>
class sparseMatrix {
public:
    sparseMatrix(int initrows = 0, int initcols = 0)
    {
        rows = initrows;
        cols = initcols;
    }
    ~sparseMatrix()
    {
    }

    void reset(int n, int m, T* element);
    void muti(sparseMatrix& B);
    void transpose();
    void add(sparseMatrix& B);
    void output();

    void insert(int n, int m, T val);
    void reset(int n, int m);
    void deb() { cout << rows << ' ' << cols; }

private:
    int rows, cols;
    arrayList<matrixTerm<T>> terms;
};

int main()
{
    sparseMatrix<int> test;
    sparseMatrix<int> B;
    int w, ope, n, m, t;
    int* ele;
    cin >> w;
    for (int i = 0; i < w; i++) {
        cin >> ope;
        switch (ope) {
        case 1:
            cin >> n >> m;
            ele = new int[n * m];
            for (int i = 0; i < n * m; i++) {
                cin >> ele[i];
            }
            test.reset(n, m, ele);
            delete[] ele;
            break;
        case 2:
            cin >> n >> m >> t;
            B.reset(n, m);
            ele = new int[3 * t];
            for (int i = 0; i < 3 * t; i++) {
                cin >> ele[i];
            }
            for (int i = 0; i < t; i++) {
                B.insert(ele[3 * i], ele[3 * i + 1], ele[3 * i + 2]);
            }
            test.muti(B);
            delete[] ele;
            break;
        case 3:
            cin >> n >> m >> t;
            B.reset(n, m);
            ele = new int[3 * t];
            for (int j = 0; j < 3 * t; j++) {
                cin >> ele[j];
            }
            for (int j = 0; j < t; j++) {
                B.insert(ele[3 * j], ele[3 * j + 1], ele[3 * j + 2]);
            }
            test.add(B);
            delete[] ele;
            break;
        case 4:
            test.output();
            break;
        case 5:
            test.transpose();
            break;
        default:
            break;
        }
    }
}

template <class T>
void sparseMatrix<T>::insert(int n, int m, T val)
{
    terms.push(matrixTerm<int> { n, m, val });
}
template <class T>
void sparseMatrix<T>::reset(int n, int m, T* element)
{
    terms.clear();
    terms.newset(n * m);
    rows = n;
    cols = m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (element[(i - 1) * m + j - 1] != 0) {
                terms.push(matrixTerm<int> { i, j, element[(i - 1) * m + (j - 1)] });
            }
        }
    }
}
template <class T>
void sparseMatrix<T>::reset(int n, int m)
{
    terms.clear();
    terms.newset(n * m);
    rows = n;
    cols = m;
}
template <class T>
void sparseMatrix<T>::output()
{
    cout << rows << ' ' << cols << endl;
    int p = 0;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (terms[p].row == i) {
                if (terms[p].col == j) {
                    cout << terms[p].value << ' ';
                    p++;
                    continue;
                }
            }
            cout << 0 << ' ';
        }
        cout << endl;
    }
}
template <class T>
void sparseMatrix<T>::muti(sparseMatrix& B)
{
    if (cols != B.rows) {
        reset(B.rows, B.cols);
        for (int i = 0; i < B.terms.arraylist(); i++)
            terms.push(B.terms[i]);
        cout << -1 << endl;
        return;
    }
    arrayList<matrixTerm<int>> temp;
    temp.newset(rows * B.cols);
    B.transpose();
    for (int i = 1; i <= this->rows; i++) {
        typename arrayList<matrixTerm<int>>::Iterator itA_i = this->terms.begin();
        typename arrayList<matrixTerm<int>>::Iterator itAEnd = this->terms.end();
        for (; itA_i != itAEnd && (*itA_i).row != i; ++itA_i) { }
        typename arrayList<matrixTerm<int>>::Iterator itA = itA_i;
        typename arrayList<matrixTerm<int>>::Iterator itB = B.terms.begin();
        typename arrayList<matrixTerm<int>>::Iterator itBEnd = B.terms.end();
        for (int j = 1; j <= B.rows; j++) {
            int sum = 0;
            for (; itA != itAEnd && (*itA).row == i && itB != itBEnd && (*itB).row == j;) {
                if ((*itA).col == (*itB).col) {
                    sum += (*itA).value * (*itB).value;
                    ++itA;
                    ++itB;
                } else if ((*itA).col < (*itB).col) {
                    ++itA;
                } else {
                    ++itB;
                }
            }
            if (sum != 0) {
                temp.push(matrixTerm<int> { i, j, sum });
            }
            itA = itA_i;
        }
    }
    this->reset(this->rows, B.rows);
    for (int i = 0; i < temp.arraylist(); i++)
        terms.push(temp[i]);
}
template <class T>
void sparseMatrix<T>::transpose()
{
    sparseMatrix<int> B;
    B.cols = rows;
    B.rows = cols;
    B.terms.news(terms.arraylist());

    int* colsize = new int[cols + 1];
    for (int i = 1; i <= cols; i++)
        colsize[i] = 0;
    for (auto i = terms.begin(); i != terms.end(); i++)
        colsize[(*i).col]++;
    int* rownext = new int[cols + 1];
    rownext[1] = 0;
    for (int i = 2; i <= cols; i++) {
        rownext[i] = rownext[i - 1] + colsize[i - 1];
    }
    for (auto i = terms.begin(); i != terms.end(); i++) {
        int j = rownext[(*i).col]++;
        B.terms[j] = matrixTerm<int> { (*i).col, (*i).row, (*i).value };
    }
    delete[] colsize;
    delete[] rownext;
    this->reset(this->cols, this->rows);
    for (int i = 0; i < B.terms.arraylist(); i++)
        terms.push(B.terms[i]);
}
template <class T>
void sparseMatrix<T>::add(sparseMatrix& B)
{
    if (rows != B.rows || cols != B.cols) {
        reset(B.rows, B.cols);
        for (int i = 0; i < B.terms.arraylist(); i++)
            terms.push(B.terms[i]);
        cout << -1 << endl;
        return;
    }
    arrayList<matrixTerm<int>> temp;
    typename arrayList<matrixTerm<int>>::Iterator itA = this->terms.begin();
    typename arrayList<matrixTerm<int>>::Iterator itAEnd = this->terms.end();
    typename arrayList<matrixTerm<int>>::Iterator itB = B.terms.begin();
    typename arrayList<matrixTerm<int>>::Iterator itBEnd = B.terms.end();
    temp.newset(rows * cols);
    while (itA != itAEnd || itB != itBEnd) {
        if (itA != itAEnd && itB != itBEnd) {
            if ((*itA).row == (*itB).row) {
                if ((*itA).col == (*itB).col) {
                    int sum = (*itA).value + (*itB).value;
                    if (sum != 0) {
                        temp.push(matrixTerm<int> { (*itA).row, (*itA).col, sum });
                    }
                    ++itA;
                    ++itB;
                } else if ((*itA).col < (*itB).col) {
                    temp.push(*itA);
                    ++itA;
                } else {
                    temp.push(*itB);
                    ++itB;
                }

            } else if ((*itA).row < (*itB).row) {
                temp.push(*itA);
                ++itA;
            } else {
                temp.push(*itB);
                ++itB;
            }

        } else {
            if (itA != itAEnd) {
                temp.push(*itA);
                ++itA;
            } else {
                temp.push(*itB);
                ++itB;
            }
        }
    }
    this->reset(this->rows, this->cols);
    for (int i = 0; i < temp.arraylist(); i++)
        terms.push(temp[i]);
}