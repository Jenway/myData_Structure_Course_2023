/*
* 给定散列函数的除数 D 和操作数 m，输出每次操作后的状态。
* 有以下三种操作：
* 1. 插入 x，若 x 已存在则输出 Existed
* 2. 查询 x，若散列表不含有 x，输出 "Not Found"，否则输出 x 所在的链表的长度
* 3. 删除 x，若散列表不含有 x，输出 "Delete Failed"，否则输出 x 所在链表删除 x 后的长度

* 输入格式
* 第一行两个整数 D(1<=D<=3000)和 m(1=m<=3000)，其中D为散列函数的除数，m为操作数
* 接下来的 m行，每行两个整数 opt和x，分别代表操作类型和操作数
* 若opt为0，则代表向散列表中插入x;
* 若opt为1，代表查询散列表中x是否存在
* 若opt为2，(如果散列表中含有 x)，删除X。
* 数据保证散列表不会溢出。
*/

#include "hashChains.h"
#include <iostream>

using HashTable = hashChains<int, int>;
using Pair = pair<const int, int>;

class Solution {
private:
    HashTable hashTable;
    int m;

public:
    Solution(int D, int m)
        : hashTable(D)
        , m(m)
    {
    }
    void solve()
    {
        for (int i = 0; i < m; i++) {
            int opt, x;
            std::cin >> opt >> x;
            if (opt == 0) {
                Pair p { x, 0 };
                hashTable.insert(p);
            } else if (opt == 1) {
                hashTable.find(x);
            } else if (opt == 2) {
                hashTable.erase(x);
            }
        }
    }
};

int main()
{
    int D, m;
    std::cin >> D >> m;
    Solution solution(D, m);
    solution.solve();

    return 0;
}