#include "extendedChain.h"
#include <algorithm>
#include <iostream>
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
    // @ test extendedChain's meld
    extendedChain<int> a, b;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    a.push_back(7);
    a.push_back(9);
    b.push_back(2);
    b.push_back(4);
    b.push_back(6);
    b.push_back(8);
    b.push_back(10);
    extendedChain<int> c = meld(a, b);
    stringstream ss;
    c.output(ss);
    AssertEqual("1  2  3  4  5  6  7  8  9  10 ", ss.str(), "meld()");

    return 0;
}