#include "arrayList.h"
#include <iostream>

using namespace std;
// 11 编写方法arrayList<T>::push_back，它把元素 theElcment 插到线性表的右端。不要利用 insert 方法。方法的时间复杂度是多少? 测试你的代码。
// @Test
void testPushBack()
{
    arrayList<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    bool flag = true;
    flag = (a.size() == 4) ? true : false;
    for (int i = 0; i < a.size(); i++) {
        if (a.get(i) != i + 1) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "testPushBack() passed" << endl;
    } else {
        cout << "testPushBack() failed" << endl;
    }
}
// 12) 编写方法arrayList<T>:pop back，剔蚌敝茨炳宝版按抚驳线性表右端的元素删除。不要利用erase 方法。法的时间复杂度是多少?测试你的代码。
// @Test
void testPopBack()
{
    arrayList<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.pop_back();
    bool flag = true;
    flag = (a.size() == 3) ? true : false;
    if (flag) {
        cout << "testPopBack() passed" << endl;
    } else {
        cout << "testPopBack() failed" << endl;
    }
}
// 14编写方法arrayList<T>:reserve(theCapacity)，它把数组的容量改变为当前容量和theCapacit的较大者。测试你的代码。
// @Test
void testReserve()
{
    arrayList<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.reserve(10);
    bool flag = true;
    flag = (a.capacity() == 10) ? true : false;
    a.reserve(5);
    flag = (a.capacity() == 10) ? true : false;
    if (flag) {
        cout << "testReserve() passed" << endl;
    } else {
        cout << "testReserve() failed" << endl;
    }
}
// 16 编写方法arrayList<T>::clear，它使线性表为空。方法的复杂度是多少?测试你的代码
// @Test
void testClear()
{
    arrayList<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.clear();
    bool flag = true;
    flag = (a.size() == 0) ? true : false;
    if (flag) {
        cout << "testClear() passed" << endl;
    } else {
        cout << "testClear() failed" << endl;
    }
}
int main(void)
{
    testPushBack();
    testPopBack();
    testReserve();
    testClear();
    return 0;
}