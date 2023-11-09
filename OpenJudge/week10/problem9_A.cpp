#include "linkedBinaryTree.h"
#include <iostream>

using namespace std;
using BinaryTree = linkedBinaryTree<int>;

class Solution {
private:
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
    void runTest()
    {
        /*
        *格式
        *输入格式
        *第一行为一个数字 n (10<=n<=100000)，表示有这棵树有 n 个节点，编号为 1~n。
        *之后 n 行每行两个数字，第 i 行的两个数字 a、b 表示编号为 i 的节点的左孩子节点为 a，右孩子节点为 b，-1 表示该位置没有节点。
        *保证数据有效，根节点为 1。

        *输出格式
        *第一行，n 个数字，表示该树的前序遍历。
        *第二行，n 个数字，表示该树的中序遍历。
        *第三行，n 个数字，表示该树的后序遍历
        *第四行，n 个数字，表示该树的层次遍历。
        *第五行，n 个数字，第 i 个数字表示以 i 节点为根的子树的节点数目。
        *第六行，n 个数字，第 i 个数字表示以 i 节点为根的子树的高度。
        */
        auto output = [](BinaryTree::Node* node) { cout << node->data << " "; };
        this->tree->input();
        this->tree->preOrder(output);
        cout << endl;
        this->tree->inOrder(output);
        cout << endl;
        this->tree->postOrder(output);
        cout << endl;
        this->tree->levelOrder(output);
        cout << endl;
        this->tree->count_all();
        this->tree->height_all();
        cout << endl;
    }
};

int main(void)
{
    Solution* sol = new Solution();
    sol->runTest();
    delete sol;
    return 0;
}
