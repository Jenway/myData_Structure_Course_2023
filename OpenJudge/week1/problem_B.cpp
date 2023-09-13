#include <iostream>

using namespace std;

class Solution {
private:
    int n;
    int* a;
    void cal_value(int& value);
    void cal_permutation_helper(int key, int& value);

public:
    int cal_permutation();
    void input();
    void output();
    Solution(int size);
    Solution() = delete;
    ~Solution() = default;
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
    for (int i = 0; i < n; i++) {
        sum += a[i] ^ (i + 1);
    }
    value |= sum;
}

void Solution::cal_permutation_helper(int key, int& value)
{
    if (key == n) {
        cal_value(value);
    } else {
        for (int i = key; i < n; i++) {
            swap(a[key], a[i]);
            cal_permutation_helper(key + 1, value);
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