#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
template <class T>

class Solution {
public:
    void input() // 输入
    {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }
    void output() // 输出
    {
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
    }
    void rank()
    {
        // 初始化所有排名为0
        for (int i = 0; i < n; i++)
            r[i] = 0;
        // 计算排名
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++) {
                // 相当于每两个元素都进行且只进行一次比较，大的名次+1
                // 因为是小于等于，所以输入的时候相同值靠后的名次更大
                if (a[j] <= a[i])
                    r[i]++;
                else
                    r[j]++;
            }
        // 依据排名交换
        for (int i = 0; i < n;) {
            // 根据排名交换，直到交换到属于自己名次的元素
            // 本质上排名的交换是若干个等价类
            if (r[i] == i)
                i++;
            else {
                swap(a[i], a[r[i]]);
                swap(r[i], r[r[i]]);
            }
        }
        // 稳定排序
    }
    void selection()
    {
        // 选择排序
        // 每次遍历找最大的，之后放到相应的位置
        bool sorted = false;
        for (int size = n; !sorted && (size > 1); size--) {
            int indexofmax = 0;
            // 假设已经排序好了，那么从左到右是依次增大的，a[indexofmax]要小于等于后一个元素。
            sorted = true;
            for (int i = 1; i < size; i++) {
                if (a[indexofmax] <= a[i])
                    indexofmax = i;
                else
                    sorted = false;
            }
            swap(a[indexofmax], a[size - 1]);
        }
        // 稳定排序
    }
    void bubble()
    {
        bool sorted = false;
        for (int i = n - 1; i > 0; i--) {
            sorted = true;
            for (int j = 0; j < i; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    sorted = false;
                }
            }
            if (sorted)
                break;
        }
    }
    void insert()
    {
        // 操作方法上是相当于把所有元素“拿”出来之后一个一个的往数组里插入
        for (int i = 1; i < n; i++) {
            // i=1是因为第一个插入不用考虑
            int ins = a[i];
            // 相当于拿出第i个元素
            for (int j = i - 1; j >= 0; j--) {
                if (ins < a[j]) {
                    swap(a[j], a[j + 1]);
                    a[j] = ins;
                } else {
                    a[j + 1] = ins;
                    break;
                }
            }
            // 实际上不用ins=a[i]也能实现，是多余的步骤
        }
    }
    ~Solution()
    {
        delete[] a;
        delete[] r;
    }

private:
    int n = 0; // 元素个数
    T* a = new T[1000];
    T* r = new T[1000]; // 名次排序存储的名次
};

int main()
{
    Solution<int> test;
    test.input();
    test.rank();
    test.output();
    test.~Solution();
}
