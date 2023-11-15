#include "priorityQueue.h"
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int main(void)
{
    // test for priorityQueue.h
    // PriorityQueue<int> pq;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(1);
    pq.push(5);
    pq.push(4);
    pq.push(3);
    pq.push(2);
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
}