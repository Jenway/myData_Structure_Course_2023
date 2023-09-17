#include <iostream>

using namespace std;

class Solution {
private:
    int n;
    int* a;
    bool* tag;
    int* subArray;
    void cal_value(int& value);
    void cal_subset_helper(int key, int& value);
    int cal_subset();

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

int Solution::cal_subset()
{
    int value = 0;
    cal_subset_helper(0, value);
    return value;
}

void Solution::cal_subset_helper(int key, int& value)
{
    if (key == n) {
        // 此时，已经考虑了每一个元素的选取情况
        // 计算当前子集的值
        cal_value(value);
    } else {
        /*
         * 这里分两种情况，一种是a[key]不在子集中，一种是a[key]在子集中
         */
        tag[key] = true;
        cal_subset_helper(key + 1, value);
        tag[key] = false;
        cal_subset_helper(key + 1, value);
    }
}

void Solution::cal_value(int& value)
{
    int sum = 0, num = 0;
    // 为子集赋值
    for (int i = 0; i < n; i++) {
        if (tag[i]) {
            subArray[num] = a[i];
            num++;
        }
    }
    // 计算子集的值
    for (int j = 0; j < num; j++) {
        sum += subArray[j] * (j + 1);
    }
    // 加和（异或）
    value ^= sum;
}

void Solution::input()
{
    for (int i = 0; i < this->n; i++) {
        cin >> this->a[i];
    }
}
void Solution::output()
{
    cout << this->cal_subset() << endl;
}
Solution::Solution(int size)
    : n(size)
{
    a = new int[n];
    tag = new bool[n];
    subArray = new int[n];
}
Solution::~Solution()
{
    delete[] a;
    delete[] tag;
    delete[] subArray;
}