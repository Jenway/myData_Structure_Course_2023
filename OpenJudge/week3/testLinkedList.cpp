#include "LinkedList.h"
#include <algorithm>
#include <iostream>
#include <regex>
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
int cal(LinkedList<int> list)
{
    int sum = 0, i = 0;
    for (auto item : list) {
        sum += i ^ item;
        i++;
    }
    return sum;
}
int main(void)
{
    // @ test for insert method
    typedef LinkedList<int> slist;
    slist a;
    a.insert(a.begin() + 0, 1);
    a.insert(a.begin() + 1, 3);
    a.insert(a.begin() + 2, 5);
    a.insert(a.begin() + 3, 7);
    a.insert(a.begin() + 4, 9);
    stringstream ss;
    a.LOG_output(ss);
    AssertEqual("1 3 5 7 9 ", ss.str(), "insert()");

    // one more test for insert method
    a.insert(a.begin() + 0, 2);
    a.insert(a.begin() + 1, 4);
    a.insert(a.begin() + 2, 6);
    a.insert(a.begin() + 3, 8);
    a.insert(a.begin() + 4, 10);
    stringstream ss2;
    a.LOG_output(ss2);
    AssertEqual("2 4 6 8 10 1 3 5 7 9 ", ss2.str(), "insert()");

    // twice more test for insert method
    a.insert(a.begin() + 0, 12);
    stringstream ss3;
    a.LOG_output(ss3);
    AssertEqual("12 2 4 6 8 10 1 3 5 7 9 ", ss3.str(), "insert()");

    // @ test for merge method
    slist b;
    b.insert(b.begin() + 0, 2);
    b.insert(b.begin() + 1, 4);
    b.insert(b.begin() + 2, 6);
    b.insert(b.begin() + 3, 8);
    b.insert(b.begin() + 4, 10);
    a.sort();
    stringstream ss6;
    a.LOG_output(ss6);
    AssertEqual("1 2 3 4 5 6 7 8 9 10 12 ", ss6.str(), "sort()");
    b.sort();
    stringstream ss7;
    b.LOG_output(ss7);
    AssertEqual("2 4 6 8 10 ", ss7.str(), "sort()");

    auto c = a.merge(b);
    stringstream ss4;
    c.LOG_output(ss4);
    AssertEqual("1 2 2 3 4 4 5 6 6 7 8 8 9 10 10 12 ", ss4.str(), "merge()");

    // @ one more test for merge method
    slist list1;
    slist list2;
    list1.insert(list1.begin() + 0, 5);
    list1.insert(list1.begin() + 1, 3);
    list1.insert(list1.begin() + 2, 7);
    list1.insert(list1.begin() + 3, 1);
    list1.insert(list1.begin() + 4, 9);

    list2.insert(list2.begin() + 0, 6);
    list2.insert(list2.begin() + 1, 2);
    list2.insert(list2.begin() + 2, 8);
    list2.insert(list2.begin() + 3, 4);
    list2.insert(list2.begin() + 4, 10);
    list1.sort();
    list2.sort();
    auto list3 = list1.merge(list2);
    stringstream ss5;
    list3.LOG_output(ss5);
    AssertEqual("1 2 3 4 5 6 7 8 9 10 ", ss5.str(), "merge()");
    return 0;
}