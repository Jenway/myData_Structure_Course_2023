#include "chain.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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
    // @ test chain's set
    chain<int> b;
    b.insert(0, 1);
    b.insert(1, 3);
    b.insert(2, 5);
    b.insert(3, 7);
    b.insert(4, 9);
    b.set(0, 2);
    b.set(1, 4);
    b.set(2, 6);
    b.set(3, 8);
    b.set(4, 10);

    stringstream ss;
    b.output(ss);

    AssertEqual("2  4  6  8  10 ", ss.str(), "set()");

    // @ test chain's reverse
    chain<int> a;
    a.insert(0, 1);
    a.insert(1, 3);
    a.insert(2, 5);
    a.insert(3, 7);
    a.insert(4, 9);
    a.reverse();

    stringstream ss2;
    a.output(ss2);
    AssertEqual("9 7 5 3 1 ", ss2.str(), "reverse()");

    return 0;
}