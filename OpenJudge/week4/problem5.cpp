#include "arrayList.h"
#include <iostream>

using namespace std;

typedef struct matrixTerm {
    int row;
    int col;
    int value;
} MatrixTerm;

using List = arrayList<MatrixTerm>;

class SparesMatrix {
private:
    int rows = 0;
    int cols = 0;
    List mArray;

public:
    void input_raw();
    void input_nonzero(int terms);

    void reset(int rows, int cols);
    void multiply(SparesMatrix& B);
    void add(SparesMatrix& B);
    void output();
    void transpose();
};

class Solution {
private:
    SparesMatrix* sm;

public:
    Solution() { sm = new SparesMatrix(); }
    ~Solution() { delete sm; }
    void runTest();
    void SwitchCase(int option);
};

int main(void)
{
    Solution s;
    s.runTest();
}

void Solution::runTest()
{
    int w;
    cin >> w;
    for (int i = 0; i < w; i++) {
        int option;
        cin >> option;
        SwitchCase(option);
    }
}
void Solution::SwitchCase(int option)
{
    enum options {
        RESET = 1,
        MULTIPLY,
        ADD,
        OUTPUT,
        TRANSPOSE
    };
    int rows, cols, t;
    SparesMatrix B;
    switch (option) {
    case RESET:
        cin >> rows >> cols;
        sm->reset(rows, cols);
        sm->input_raw();
        break;
    case MULTIPLY:
        cin >> rows >> cols >> t;
        B.reset(rows, cols);
        B.input_nonzero(t);
        sm->multiply(B);
        break;
    case ADD:
        cin >> rows >> cols >> t;
        B.reset(rows, cols);
        B.input_nonzero(t);
        sm->add(B);
        break;
    case OUTPUT:
        sm->output();
        break;
    case TRANSPOSE:
        sm->transpose();
        break;
    default:
        break;
    }
}

// implement of Spare Matrix

void SparesMatrix::reset(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    mArray.clear();
}
void SparesMatrix::input_raw()
{
    int val;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cin >> val;
            if (val != 0) {
                mArray.push_back(matrixTerm { i, j, val });
            }
        }
    }
}

void SparesMatrix::input_nonzero(int terms)
{
    int row, col, val;
    for (int i = 0; i < terms; i++) {
        cin >> row >> col >> val;
        mArray.push_back(matrixTerm { row, col, val });
    }
}

void SparesMatrix::output()
{
    cout << this->rows << " " << this->cols << endl;
    List::iterator it = mArray.begin();
    List::iterator itEnd = mArray.end();
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (it != itEnd && (*it).row == i && (*it).col == j) {
                cout << (*(it++)).value << " ";
            } else {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }
}

void SparesMatrix::add(SparesMatrix& B)
{
    if (this->rows != B.rows || this->cols != B.cols) {
        this->reset(B.rows, B.cols);
        this->mArray = B.mArray;
        cout << -1 << endl;
        return;
    }
    List tempArray;

    typename List::iterator itA = this->mArray.begin();
    typename List::iterator itB = B.mArray.begin();
    typename List::iterator itAEnd = this->mArray.end();
    typename List::iterator itBEnd = B.mArray.end();

    while (itA != itAEnd || itB != itBEnd) {
        if (itA != itAEnd && itB != itBEnd) {
            if ((*itA).row == (*itB).row) {
                if ((*itA).col == (*itB).col) {
                    int sum = (*itA).value + (*itB).value;
                    if (sum != 0) {
                        tempArray.push_back(matrixTerm { (*itA).row, (*itA).col, sum });
                    }
                    ++itA;
                    ++itB;
                } else if ((*itA).col < (*itB).col) {
                    tempArray.push_back(*itA);
                    ++itA;
                } else {
                    tempArray.push_back(*itB);
                    ++itB;
                }

            } else if ((*itA).row < (*itB).row) {
                tempArray.push_back(*itA);
                ++itA;
            } else {
                tempArray.push_back(*itB);
                ++itB;
            }

        } else {
            if (itA != itAEnd) {
                tempArray.push_back(*itA);
                ++itA;
            } else {
                tempArray.push_back(*itB);
                ++itB;
            }
        }
    }

    this->reset(this->rows, this->cols);
    this->mArray = std::move(tempArray);
}

void SparesMatrix::multiply(SparesMatrix& B)
{

    if (this->cols != B.rows) {
        this->reset(B.rows, B.cols);
        this->mArray = B.mArray;
        cout << -1 << endl;
        return;
    }
    List tempArray;

    B.transpose();

    for (int i = 1; i <= this->rows; i++) {
        typename List::iterator itA_i = this->mArray.begin();
        typename List::iterator itAEnd = this->mArray.end();
        for (; itA_i != itAEnd && (*itA_i).row != i; ++itA_i) { }
        typename List::iterator itA = itA_i;
        typename List::iterator itB = B.mArray.begin();
        typename List::iterator itBEnd = B.mArray.end();
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
                tempArray.push_back(matrixTerm { i, j, sum });
            }
            itA = itA_i;
        }
    }
    this->reset(this->rows, B.rows);
    this->mArray = std::move(tempArray);
}

void SparesMatrix::transpose()
{
    // 书上的方法

    // 新建一个矩阵来存储转置后的矩阵
    SparesMatrix b;
    b.cols = rows;
    b.rows = cols;
    b.mArray.resize(mArray.getSize());

    // 统计每一列的非零元素个数
    int* colSize = new int[cols + 1];
    for (int i = 1; i <= cols; i++)
        colSize[i] = 0;
    for (auto i = mArray.begin(); i != mArray.end(); i++)
        colSize[i->col]++;

    // 计算每一行的第一个非零元素在b中的位置
    int* rowNext = new int[cols + 1];
    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++) {
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];
    }

    // 将矩阵的每一行的非零元素按照列的顺序放入b中
    for (auto i = mArray.begin(); i != mArray.end(); i++) {
        int j = rowNext[i->col]++;
        b.mArray[j] = matrixTerm { (*i).col, (*i).row, (*i).value };
    }

    delete[] colSize;
    delete[] rowNext;

    this->reset(this->cols, this->rows);
    this->mArray = std::move(b.mArray);
}