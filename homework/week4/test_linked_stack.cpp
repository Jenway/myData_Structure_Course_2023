#include "linkedStack.h"
#include <algorithm>
#include <chrono>
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

int main(void)
{

    // @test linkedStack's pushNode && popNode
    linkedStack<long long> stack;
    chrono::steady_clock sc;
    auto start = sc.now();
    for (long long i = 1; i <= 10000000; i++) {
        chainNode<long long>* node = new chainNode<long long>(i);
        stack.pushNode(node);
    }
    auto end = sc.now();
    cout << "pushNode: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms" << endl;

    auto start2 = sc.now();
    for (long long i = 10000000; i >= 1; i--) {
        // AssertEqual(to_string(i), to_string(stack.popNode().element),
        //     "pop");
        stack.popNode();
    }
    auto end2 = sc.now();
    cout << "popNode: "
         << chrono::duration_cast<chrono::milliseconds>(end2 - start2).count()
         << "s" << endl;
}
