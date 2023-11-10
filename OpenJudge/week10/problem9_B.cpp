/*
 * 接收二叉树前序序列和中序序列(各元素各不相同)，输出该二叉树的后序序列。
 *输入：
 *第一行为数字 n；
 *第二行有 n 个数字，表示二叉树的前序遍历；
 *第三行有 n 个数字，表示二叉树的中序遍历。
 *输出：
 *输出一行，表示该二叉树的后序遍历序列
 */

#include "linkedBinaryTree.h"
#include "unordered_map.h"
#include <iostream>

using namespace std;
using BinaryTree = linkedBinaryTree<int>;
using Unordered_map = my_unordered_map<int, int>;
class Solution {
private:
    int n;
    int* preOrder;
    int* inOrder;
    Unordered_map* inOrderIndex;
    BinaryTree* tree;

public:
    Solution(int num)
        : n { num }
        , preOrder { new int[n] }
        , inOrder { new int[n] }
        , inOrderIndex { new Unordered_map(n) }
        , tree { new BinaryTree() }
    {
    }
    ~Solution()
    {
        delete tree;
    }
    void runTest();
};

void Solution::runTest()
{
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        preOrder[i] = temp;
    }
    for (int i = 0; i < n; i++) {
        cin >> temp;
        inOrder[i] = temp;
        inOrderIndex->insert({ temp, i });
    }

    this->tree->buildTree(preOrder, inOrder, n, *inOrderIndex);
    this->tree->postOrder([](BinaryTree::Node* node) { cout << node->data << " "; });
    cout << endl;
}

int main(void)
{
    int n;
    cin >> n;
    Solution* sol = new Solution(n);
    sol->runTest();
    delete sol;
    return 0;
}