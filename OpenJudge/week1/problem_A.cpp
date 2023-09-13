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
    void input()
    {
        for (int i = 0; i < this->n; i++) {
            cin >> this->a[i];
        }
    }
    void output()
    {
        cout << this->cal_subset() << endl;
    }
    Solution(int size)
        : n(size)
    {
        a = new int[n];
        tag = new bool[n];
        subArray = new int[n];
    }
    Solution() = delete;
    ~Solution()
    {
        delete[] a;
        delete[] tag;
        delete[] subArray;
    }
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
        cal_value(value);
    } else {
        tag[key] = true;
        cal_subset_helper(key + 1, value);
        tag[key] = false;
        cal_subset_helper(key + 1, value);
    }
}

void Solution::cal_value(int& value)
{
    int sum = 0, num = 0;
    for (int i = 0; i < n; i++) {
        if (tag[i]) {
            subArray[num] = a[i];
            num++;
        }
    }
    for (int j = 0; j < num; j++) {
        sum += subArray[j] * (j + 1);
    }
    value ^= sum;
}
