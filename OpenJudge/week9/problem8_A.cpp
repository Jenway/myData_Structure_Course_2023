// 要求
// 使用线性开型寻址实现
// 描述
// 给定散列函数的除数 D和操作数 m，输出每次操作后的状态有以下三种操作:
// 1.插入x，若散列表已存在x，输出“Existed”，否则插入x到散列表中，输出所在的下标。
// 2.查询 x，若散列表不含有 x，输出“-1”，否则输出x对应下标。
// 3.删除x，若散列表不含有 x，输出“Not Found”，否则输出删除 x 过程中移动素的个数
// 格式输入格式
// 第一行两个整数 D，m。分别代表散列函数的除数 D 和操作数 m。接下来 m 行，每行两个整数 opt 和x，分别代表操作类型和操作数若opt为0，代表插入x。若opt为1，代表查询x。若opt为 2，代表删除 x
// 输出格式
// 按要求输出。

#include "hashTable.h"
#include <iostream>

using HashTable = hashTable<int, int>;
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
        

        for (int i = 1, opt, d; i <= m; i++) {
            std::cin >> opt >> d;
            Pair p{ d, 0 };
            if (opt == 0) {
                hashTable.insert(p);
            } else if (opt == 1) {
                hashTable.find(p.first);
            } else if (opt == 2) {
                hashTable.erase(p.first);
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