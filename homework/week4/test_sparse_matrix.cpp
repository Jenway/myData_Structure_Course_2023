#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "sparseMatrix.h"

// test get && set for sparseMatrix

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
int main(void)
{
    // @test sparseMatrix get && set
    sparseMatrix<int> matrix;
    matrix.set(1, 1, 1);
    matrix.set(2, 1, 2);
    matrix.set(2, 2, 3);
    matrix.set(3, 1, 4);
    matrix.set(3, 2, 5);
    matrix.set(3, 3, 6);

    AssertEqual("1", to_string(matrix.get(1, 1).value), "get(1,1)");
    AssertEqual("2", to_string(matrix.get(2, 1).value), "get(2,1)");
    AssertEqual("3", to_string(matrix.get(2, 2).value), "get(2,2)");
    AssertEqual("4", to_string(matrix.get(3, 1).value), "get(3,1)");
    AssertEqual("5", to_string(matrix.get(3, 2).value), "get(3,2)");
    AssertEqual("6", to_string(matrix.get(3, 3).value), "get(3,3)");

    //  random access
    matrix.set(2, 1, 0);
    matrix.set(3, 2, 0);
    AssertEqual("0", to_string(matrix.get(2, 1).value), "get(2,1)");
    AssertEqual("0", to_string(matrix.get(3, 2).value), "get(3,2)");
    
}