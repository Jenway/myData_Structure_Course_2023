// 实现一个下三角矩阵的乘法
// 已知：该三角矩阵采用一维数组存储

#include "lowerTriangularMatrix.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace ::std;
void AssertEqual(string expected, string actual, string message)
{
    string exp = expected;
    string act = actual;
    // delete all spaces
    expected.erase(remove_if(expected.begin(), expected.end(), ::isspace),
        expected.end());
    actual.erase(remove_if(actual.begin(), actual.end(), ::isspace),
        actual.end());

    if (expected.compare(actual) == 0) {
        cout << message << " passed" << endl;
    } else {
        cout << message << " failed"
             << " expected: " << exp << " actual: " << act << endl;
    }
}

template <typename T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::operator*(lowerTriangularMatrix<T> matrix) const
{
    if (n != matrix.n) {
        throw illegalParameterValue("Matrix size must be equal");
    }
    lowerTriangularMatrix<T> result(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            T sum = 0;
            for (int k = j; k <= i; k++) {
                sum += get(i, k) * matrix.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

int main(void)
{
    // @test lowerTriangularMatrix operator*
    lowerTriangularMatrix<int> matrix1(3);
    matrix1.set(1, 1, 1);
    matrix1.set(2, 1, 2);
    matrix1.set(2, 2, 3);
    matrix1.set(3, 1, 4);
    matrix1.set(3, 2, 5);
    matrix1.set(3, 3, 6);

    lowerTriangularMatrix<int> matrix2(3);
    matrix2.set(1, 1, 1);
    matrix2.set(2, 1, 2);
    matrix2.set(2, 2, 3);
    matrix2.set(3, 1, 4);
    matrix2.set(3, 2, 5);
    matrix2.set(3, 3, 6);

    lowerTriangularMatrix<int> result = matrix1 * matrix2;
    stringstream ss;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= i; j++) {
            ss << result.get(i, j) << " ";
        }
    }
    AssertEqual("1 8 9 38 45 36", ss.str(), "lowerTriangularMatrix operator*");
}
