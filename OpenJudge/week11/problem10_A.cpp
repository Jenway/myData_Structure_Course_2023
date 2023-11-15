#include "priorityQueue.h"
#include <algorithm>
#include <iostream>
#include <queue>

using std::cin, std::cout, std::endl;

using min_heap = PriorityQueue<int>;
// using min_heap = std::priority_queue<int, std::vector<int>, std::greater<int>>;
// heapSort from algorithm
auto heapSort = [](int* a, int n) {
    PriorityQueue<int>::make_heap(a, a + n, PriorityQueue<int>::less);
    PriorityQueue<int>::sort_heap(a, a + n, PriorityQueue<int>::less);
    // std::make_heap(a, a + n, std::less<int>());
    // std::sort_heap(a, a + n, std::less<int>());
};

class Solution {
private:
    int n;
    min_heap pq;

public:
    Solution(int n)
        : n(n)
    {
    }
    void input()
    {
        // int* a = new int[n];
        for (int i = 0; i < n; i++) {
            // cin >> a[i];
            int x;
            cin >> x;
            pq.push(x);
        }
        // initialize the priority queue from a
        // pq = min_heap(a, a + n);
        // delete[] a;
        cout << pq.top() << endl;
    }
    void runTest()
    {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            // cout << "i: " << i << endl;
            int op;
            cin >> op;
            switch (op) {
            case 1:
                int x;
                cin >> x;
                pq.push(x);
                cout << pq.top() << endl;
                break;
            case 2:
                pq.pop();
                cout << pq.top() << endl;
                break;
            case 3: {
                int sz;
                cin >> sz;
                int* b = new int[sz];
                for (int j = 0; j < sz; j++) {
                    cin >> b[j];
                }
                heapSort(b, sz);
                for (int j = 0; j < sz; j++) {
                    cout << b[j] << " ";
                }
                delete[] b;
                cout << endl;
                break;
            }
            default:
                break;
            }
        }
    }
};

int main(void)
{
    int n;
    cin >> n;
    Solution sol(n);
    sol.input();
    sol.runTest();
    return 0;
}