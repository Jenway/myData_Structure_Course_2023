#include "Queue.h"
#include <iostream>


using namespace std;

using Queue = myQueue<int>;

// 描述
// 假设桌上有一叠扑克牌，依次编号为 1-n（从上至下）。当至少还有两张的时候，可以进行操作：把第一张牌扔掉，然后把新的第一张（原先扔掉的牌下方的那张牌,即第二张牌）放到整叠牌的最后。输入 n，输出最后剩下的牌。

// 格式
// 输入
// 一个整数 n，代表一开始卡片的总数。

// 输出
// 最后一张卡片的值。

class Solution {
private:
    int n;
    Queue q;

public:
    Solution(int n)
        : n(n)
    {
        for (int i = 1; i <= n; i++) {
            q.push(i);
        }
    }
    int solve()
    {
        while (q.size() > 1) {
            q.pop();
            q.push(q.front());
            q.pop();
        }
        return q.front();
    }
};
int main(void)
{
    int n;
    cin >> n;
    cout << Solution(n).solve() << endl;
}