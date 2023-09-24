#include <iostream>

using namespace std;

template <typename T>
class SortClass {
    // 排序数据需使用动态数组存储
    // 排序类需提供以下操作：名次排序、及时终止的选择排序、及时终止的冒泡排序、插入排序
private:
    T* data;
    int size = 1000;
    void compute_rank(int* rank);
    int select_minimum(int start, bool& flag);
    void bubble(int i, bool& flag);
    void insertion(int i);

public:
    // 名次排序
    void rank_sort();
    // 及时终止的选择排序
    void selection_sort();
    // 及时终止的冒泡排序
    void bubble_sort();
    // 插入排序
    void insertion_sort();

    void input();
    void output();
    SortClass(int n);
    ~SortClass();
};

int main(void)
{
    int n;
    cin >> n;
    SortClass<int> sort_class(n);
    sort_class.input();

    // sort_class.rank_sort();
    sort_class.selection_sort();
    // sort_class.bubble_sort();
    // sort_class.insertion_sort();
    sort_class.output();
    return 0;
}

template <typename T>
void SortClass<T>::rank_sort()
{
    int* rank = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        rank[i] = 0;
    }
    compute_rank(rank);

    T* temp = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        temp[rank[i]] = this->data[i];
    }
    for (int i = 0; i < this->size; i++) {
        this->data[i] = temp[i];
    }
    delete[] rank;
    delete[] temp;
}

template <typename T>
void SortClass<T>::compute_rank(int* rank)
{
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = i + 1; j < this->size; j++) {
            if (this->data[i] > this->data[j]) {
                rank[i]++;
            } else {
                rank[j]++;
            }
        }
    }
}

template <typename T>
void SortClass<T>::selection_sort()
{
    for (int i = 0; i < this->size; i++) {
        bool isSorted = true;
        int min = select_minimum(i, isSorted);
        if (min != i) {
            swap(this->data[min], this->data[i]);
        }
        if (isSorted) {
            break;
        }
    }
}

template <typename T>
int SortClass<T>::select_minimum(int start, bool& isSorted)
{
    int min = start;
    for (int j = start + 1; j < this->size; j++) {
        if (this->data[j] > this->data[j + 1]) {
            isSorted = false;
        }
        if (this->data[min] > this->data[j]) {
            min = j;
        }
    }
    return min;
}

template <typename T>
void SortClass<T>::bubble_sort()
{
    for (int i = 0; i < this->size - 1; i++) {
        bool flag = false;
        bubble(i, flag);
        if (!flag) {
            break;
        }
    }
}

template <typename T>
void SortClass<T>::bubble(int i, bool& flag)
{
    for (int j = i + 1; j < size; j++) {
        if (this->data[i] > this->data[j]) {
            swap(this->data[i], this->data[j]);
            flag = true;
        }
    }
}

template <typename T>
void SortClass<T>::insertion_sort()
{
    for (int i = 1; i < this->size; i++) {
        insertion(i);
    }
}

template <typename T>
void SortClass<T>::insertion(int i)
{
    T temp = this->data[i];
    int j;
    for (j = i - 1; j >= 0 && this->data[j] > temp; j--) {
        this->data[j + 1] = this->data[j];
    }
    this->data[j + 1] = temp;
}

template <typename T>
SortClass<T>::SortClass(int n)
    : size(n)
{
    this->data = new T[size];
}

template <typename T>
SortClass<T>::~SortClass()
{
    delete[] this->data;
}

template <typename T>
void SortClass<T>::input()
{
    for (int i = 0; i < this->size; i++) {
        cin >> this->data[i];
    }
}

template <typename T>
void SortClass<T>::output()
{
    for (int i = 0; i < this->size; i++) {
        cout << this->data[i] << " ";
    }
    cout << endl;
}