#include <iostream>

using namespace std;

void cal_value(int* a, int n, int& value);
int cal_permutation(int* a, int n);

int main(void)
{
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << cal_permutation(a, n) << endl;

    delete[] a;
    return 0;
}

void cal_value(int* a, int n, int& value)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] ^ (i + 1);
    }
    value |= sum;
}

void cal_permutation_helper(int* a, int n, int key, int& value)
{
    if (key == n) {
        cal_value(a, n, value);
    } else {
        for (int i = key; i < n; i++) {
            swap(a[key], a[i]);
            cal_permutation_helper(a, n, key + 1, value);
            swap(a[key], a[i]);
        }
    }
}
int cal_permutation(int* a, int n){
    int value = 0;
    cal_permutation_helper(a, n, 0, value);
    return value;
}