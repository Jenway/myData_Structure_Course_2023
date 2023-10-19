#include <iostream>

using namespace std;

class Solution {
private:
    int n;
    int* a;
    void cal_value(int& value);
    void cal_permutation_helper(int key, int& value);
    int cal_permutation();

public:
    void input();
    void output();
    Solution(int size);
    Solution() = delete;
    ~Solution();
};

int main(void)
{

    int n;
    cin >> n;

    Solution solution(n);
    solution.input();
    solution.output();

    return 0;
}

void Solution::cal_value(int& value)
{
    int sum = 0;
    // 计算当前排列的价值
    for (int i = 0; i < n; i++) {
        sum += a[i] ^ (i + 1);
    }
    // 加入到总价值中
    value |= sum;
}

void Solution::cal_permutation_helper(int key, int& value)
{
    if (key == n) {
        // 当 key 等于 n 时，说明已经对每一个元素进行了交换/不交换的操作
        // 此时，计算当前排列的值
        cal_value(value);
        // for (int i = 0;i < n;i++) {
        //     cout << a[i];
        // }
    } else {
        for (int i = key; i < n; i++) {
            // 此时递归调用的分支是交换 a[key] 和 a[i] 的情况分支
            swap(a[key], a[i]);
            cal_permutation_helper(key + 1, value);
            // 递归调用结束后，将 a[key] 和 a[i] 恢复原来的值
            swap(a[key], a[i]);
        }
    }
}

int Solution::cal_permutation()
{
    int value = 0;
    cal_permutation_helper(0, value);
    return value;
}

Solution::Solution(int size)
    : n(size)
{
    a = new int[n];
}

Solution::~Solution()
{
    delete[] a;
}


void Solution::input()
{
    for (int i = 0; i < this->n; i++) {
        cin >> this->a[i];
    }
}

void Solution::output()
{
    cout << this->cal_permutation() << endl;
}