#include "priorityQueue.h"

#include <iostream>

using min_heap = PriorityQueue<int>;
using namespace std;

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
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            pq.push(x);
        }
        cout << pq.top() << endl;
    }
    void runTest()
    {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
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
                heapSort<int, std::greater<int>>(b, sz);
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