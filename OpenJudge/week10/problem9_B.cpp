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
#include <iostream>

using std::cin, std::cout, std::endl;
using BinaryTree = linkedBinaryTree<int>;
class Solution {
private:
    int n;
    int* preOrder;
    int* inOrder;
    BinaryTree* tree;

public:
    Solution()
        : tree { new BinaryTree() }
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

    preOrder = new int[n];
    inOrder = new int[n];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> preOrder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inOrder[i];
    }
    this->tree->buildTree(preOrder, inOrder, n);
    this->tree->postOrder([](BinaryTree::Node* node) { cout << node->data << " "; });
    cout << endl;
}

int main(void)
{
    Solution* sol = new Solution();
    sol->runTest();
    delete sol;
    return 0;
}