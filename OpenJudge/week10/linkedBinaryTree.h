#include "arrayQueue.h"
#include "arrayStack.h"
#include "unordered_map.h"

#include <iostream>

using std::cin;

template <typename K, typename E>
using unordered_map = my_unordered_map<K, E>;
/*
 *创建二叉树类。二叉树的存储结构使用链表。提供操作:前序遍历、中序遍历、后序遍历、层次遍历、计算二叉树结点数目、计算二叉树高度。
 */

template <typename T>
class linkedBinaryTree {
public:
    typedef struct node {
        T data;
        node* left;
        node* right;
    } Node;
    linkedBinaryTree()
        : root { nullptr }
        , _size { 0 }
    {
    }
    ~linkedBinaryTree()
    {
        clear();
    }

    void buildTree(const int* preOrder, const int* inOrder, int n);

    void clear()
    {
        postOrder(root, [](Node* node) { delete node; });
    }

    void input();

    void preOrder(void (*visit)(Node* node)) { preOrder(root, visit); }
    void inOrder(void (*visit)(Node* node)) { inOrder(root, visit); }
    void postOrder(void (*visit)(Node* node)) { postOrder(root, visit); }
    void levelOrder(void (*visit)(Node* node)) { levelOrder(root, visit); }

    int size() const { return _size; }

    void count_all();
    void height_all();

private:
    Node* root;
    int _size;

    void preOrder(Node* node, void (*visit)(Node* node));
    void inOrder(Node* node, void (*visit)(Node* node));
    void postOrder(Node* node, void (*visit)(Node* node));
    void levelOrder(Node* node, void (*visit)(Node* node));

    int count(Node* node, unordered_map<int, int>& counts)
    {
        if (node == nullptr) {
            return 0;
        }

        if (counts.find(node->data) != counts.end()) {
            return counts[node->data];
        }
        int leftCount = count(node->left, counts);
        int rightCount = count(node->right, counts);

        int totalCount = leftCount + rightCount + 1;
        counts[node->data] = totalCount;

        return totalCount;
    }

    int height(Node* node, unordered_map<int, int>& heights)
    {
        if (node == nullptr) {
            return 0;
        }

        if (heights.find(node->data) != heights.end()) {
            return heights[node->data];
        }

        int leftHeight = height(node->left, heights);
        int rightHeight = height(node->right, heights);
        int maxHeight = std::max(leftHeight, rightHeight) + 1;

        heights[node->data] = maxHeight;

        return maxHeight;
    }
};

template <typename T>
using my_Queue = ArrayQueue<T>;

template <typename T>
using my_Stack = ArrayStack<T>;

using Queue = my_Queue<linkedBinaryTree<int>::Node*>;
using Stack = my_Stack<linkedBinaryTree<int>::Node*>;

template <typename T>
void linkedBinaryTree<T>::input()
{
    /*
     * 第一行为一个数字 n(10 <= n <= 100000)，表示有这棵树有 n 个节点，内容为 1 ~n
     * 之后 n 行每行两个数字，第 i 行的两个数字 a、b 表示内容为 i 的节点的左孩子节点的内容为 a，右孩子节点的内容为 b，
     * -1 表示该位置没有节点。保证数据有效，根节点内容为 1
     */
    Queue q;
    int n;
    cin >> n;
    this->_size = n;
    unordered_map<int, Node*> nodes { unordered_map<int, Node*>(n) };
    this->root = new Node { 1, nullptr, nullptr };
    nodes.insert({ 1, root });
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        auto it = nodes.find(i);
        if (it != nodes.end()) {
            Node* node = it->second;
            if (a != -1) {
                node->left = new Node { a, nullptr, nullptr };
                nodes.insert({ a, node->left });
            }
            if (b != -1) {
                node->right = new Node { b, nullptr, nullptr };
                nodes.insert({ b, node->right });
            }
        }
    }
}

template <typename T>
void linkedBinaryTree<T>::preOrder(Node* node, void (*visit)(Node* node))
{
    if (node != nullptr) {
        visit(node);
        preOrder(node->left, visit);
        preOrder(node->right, visit);
    }
}

template <typename T>
void linkedBinaryTree<T>::inOrder(Node* node, void (*visit)(Node* node))
{
    Stack stack;
    Node* current = node;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        visit(current);

        current = current->right;
    }
}

template <typename T>
void linkedBinaryTree<T>::postOrder(Node* node, void (*visit)(Node* node))
{
    if (node == nullptr) {
        return;
    }
    Stack stack1, stack2;
    stack1.push(node);

    while (!stack1.empty()) {
        Node* temp = stack1.top();
        stack1.pop();
        stack2.push(temp);

        if (temp->left) {
            stack1.push(temp->left);
        }
        if (temp->right) {
            stack1.push(temp->right);
        }
    }

    while (!stack2.empty()) {
        Node* temp = stack2.top();
        stack2.pop();
        visit(temp);
    }
}

template <typename T>
void linkedBinaryTree<T>::levelOrder(Node* node, void (*visit)(Node* node))
{
    Queue q;
    while (node != nullptr) {
        visit(node);
        if (node->left != nullptr) {
            q.push(node->left);
        }
        if (node->right != nullptr) {
            q.push(node->right);
        }
        if (q.empty()) {
            node = nullptr;
        } else {
            node = q.front();
            q.pop();
        }
    }
}

template <typename T>
void linkedBinaryTree<T>::count_all()
{
    unordered_map<int, int> counts { unordered_map<int, int>(size()) };
    count(root, counts);
    for (int i = 1; i <= size(); i++) {
        std::cout << counts[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void linkedBinaryTree<T>::height_all()
{
    unordered_map<int, int> heights { unordered_map<int, int>(size()) };
    height(root, heights);
    for (int i = 1; i <= size(); i++) {
        std::cout << heights[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void linkedBinaryTree<T>::buildTree(const int* preOrder, const int* inOrder, int n)
{
    Queue q;
    Node* node;
    int i = 0;
    this->root = new Node { preOrder[i++], nullptr, nullptr };
    q.push(root);
    while (i < n) {
        node = q.front();
        q.pop();
        if (node->data != inOrder[i]) {
            node->left = new Node { preOrder[i++], nullptr, nullptr };
            q.push(node->left);
        } else {
            i++;
        }
        if (i < n && node->data != inOrder[i]) {
            node->right = new Node { preOrder[i++], nullptr, nullptr };
            q.push(node->right);
        } else {
            i++;
        }
    }
}