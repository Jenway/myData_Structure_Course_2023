#include "indexedBSTree.h"
#include <iostream>

using namespace std;

/*
* 创建带索引的二叉搜索树类。存储结构使用链表，提供操作:插入、删除、按名次删除、查找、按名次查找、升序输出所有元素。
格式
*输入格式
输入第一行一个数字 m (m<=1000000)，表示有 m 个操作。
*接下来 m 行，每一行有两个数字 a，b：

*当输入的第一个数字 a 为 0 时，输入的第二个数字 b 表示向搜索树中插入 b
*当输入的第一个数字 a 为 1 时，输入的第二个数字 b 表示向搜索树中查找 b
*当输入的第一个数字 a 为 2 时，输入的第二个数字 b 表示向搜索树中删除 b
*当输入的第一个数字 a 为 3 时，输入的第二个数字 b 表示查找搜索树中名次为 b 的元素
*当输入的第一个数字 a 为 4 时，输入的第二个数字 b 表示删除搜索树中名次为 b 的元素

输出格式
*对于输入中的每一种操作，输出执行操作的过程中依次比较的元素值的异或值。

注意

* 查询与删除操作中，待查询的元素也需要异或入答案中
* 查找（删除）操作中，如果未找到，或者插入操作，已存在，输出 0（不插入），不需要输出异或和
* 查找（删除）第 b 大，如果不存在，输出 0
* 删除操作中，如果当前元素有两个孩子，替换的为 右子树中最小的，如果只有一个孩子，直接用该孩子替换当前元素，如果没有孩子，直接删除
* 删除操作的替换过程中所有比较操作不计入答案
*/

class Solution {
private:
    int n;
    indexedBSTree<int> bst;

public:
    Solution(int n)
        : n(n)
    {
    }
    void runTest()
    {
        int a, b;
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            enum options { INSERT = 0,
                FIND_VIA_NAME,
                DELETE_VIA_NAME,
                FIND_VIA_RANK,
                DELETE_VIA_RANK };
            switch (a) {
            case INSERT:
                bst.insert(b);
                break;
            case FIND_VIA_NAME:
                bst.find_via_name(b);
                break;
            case DELETE_VIA_NAME:
                bst.remove(b);
                break;
            case FIND_VIA_RANK:
                bst.find_via_rank(b);
                break;
            case DELETE_VIA_RANK:
                bst.remove_via_rank(b);
                break;
            default:
                break;
            }
        }
    }
};

int main()
{
    int m;
    cin >> m;
    Solution sol { Solution(m) };
    sol.runTest();
    return 0;
}