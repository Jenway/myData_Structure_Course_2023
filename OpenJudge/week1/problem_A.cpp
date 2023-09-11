#include <iostream>

using namespace std;

bool tag[100] = {};
int subArray[100] = {};

void cal_value(int* a, int n, int& value);
int cal_subset(int* a, int n);

int main(void)
{
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << cal_subset(a, n) << endl;
    delete[] a;
    return 0;
}

void cal_value(int* a, int n, int& value)
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

void cal_subset_helper(int* a, int n, int key, int& value)
{
    if (key == n) {
        cal_value(a, n, value);
    } else {
        tag[key] = true;
        cal_subset_helper(a, n, key + 1, value);
        tag[key] = false;
        cal_subset_helper(a, n, key + 1, value);
    }
}

int cal_subset(int* a, int n)
{
    int value = 0;
    cal_subset_helper(a, n, 0, value);
    return value;
}