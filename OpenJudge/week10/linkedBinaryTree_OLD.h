#include "arrayDeque.h"
#include <iostream>

using std::cin;
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

    void count_all()
    {
        for (int i = 0; i < _size; i++) {
            std::cout << count(i) << " ";
        }
        std::cout << std::endl;
    }
    void height_all()
    {
        for (int i = 0; i < _size; i++) {
            std::cout << height(i) << " ";
        }
        std::cout << std::endl;
    }
    int count(int i = 0) { return count(getNode(i)); }
    int height(int i = 0) { return height(getNode(i)); }

private:
    Node* root;
    int _size;

    void preOrder(Node* node, void (*visit)(Node* node));
    void inOrder(Node* node, void (*visit)(Node* node));
    void postOrder(Node* node, void (*visit)(Node* node));
    void levelOrder(Node* node, void (*visit)(Node* node));

    Node* getNode(int i);
    int count(Node* node);
    int height(Node* node);
};

template <typename T>
void linkedBinaryTree<T>::input()
{
    /*
     * 第一行为一个数字 n(10 <= n <= 100000)，表示有这棵树有 n 个节点，内容为 1 ~n
     * 之后 n 行每行两个数字，第 i 行的两个数字 a、b 表示内容为 i 的节点的左孩子节点的内容为 a，右孩子节点的内容为 b，
     * -1 表示该位置没有节点。保证数据有效，根节点内容为 1
     */
    using queue = ArrayDeque<Node*>;
    queue q;
    int n;
    cin >> n;
    auto func = [&q, n]() {
        Node* root { nullptr };
        int a, b;
        for (int i = 1; i <= n; i++) {
            while (!q.empty()) {
                root = q.front();
                q.pop_front();
                // std::cout << "q.front()->data: " << q.front()->data << std::endl;

                if (root->data == i) {
                    break;
                } else {
                    q.push_back(root);
                }
            }

            cin >> a >> b;
            root->left = (a == -1) ? nullptr : new node { a, nullptr, nullptr };
            root->right = (b == -1) ? nullptr : new node { b, nullptr, nullptr };

            if (root->left != nullptr) {
                q.push_back(root->left);
            }
            if (root->right != nullptr) {
                q.push_back(root->right);
            }
        }
    };
    this->root = new node { 1, nullptr, nullptr };
    this->_size = n;
    q.push_back(root);
    func();
}

template <typename T>
typename linkedBinaryTree<T>::Node* linkedBinaryTree<T>::getNode(int i)
{
    using queue = ArrayDeque<Node*>;
    queue q;
    Node* node = root;
    q.push_back(node);
    while (node != nullptr) {
        node = q.front();
        q.pop_front();
        if (node->data == i) {
            return node;
        }
        if (node->left != nullptr) {
            q.push_back(node->left);
        }
        if (node->right != nullptr) {
            q.push_back(node->right);
        }
    }
    return nullptr;
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
    if (node != nullptr) {
        inOrder(node->left, visit);
        visit(node);
        inOrder(node->right, visit);
    }
}

template <typename T>
void linkedBinaryTree<T>::postOrder(Node* node, void (*visit)(Node* node))
{
    if (node != nullptr) {
        postOrder(node->left, visit);
        postOrder(node->right, visit);
        visit(node);
    }
}
template <typename T>
void linkedBinaryTree<T>::levelOrder(Node* node, void (*visit)(Node* node))
{
    using Queue = ArrayDeque<Node*>;
    Queue q;
    while (node != nullptr) {
        visit(node);
        if (node->left != nullptr) {
            q.push_back(node->left);
        }
        if (node->right != nullptr) {
            q.push_back(node->right);
        }
        if (q.empty()) {
            node = nullptr;
        } else {
            node = q.front();
            q.pop_front();
        }
    }
}

template <typename T>
int linkedBinaryTree<T>::count(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        return 1 + count(node->left) + count(node->right);
    }
}

template <typename T>
int linkedBinaryTree<T>::height(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

template <typename T>
void linkedBinaryTree<T>::buildTree(const int* preOrder, const int* inOrder, int n)
{
    ArrayDeque<Node*> q;

    Node* node;
    int i = 0;
    this->root = new Node { preOrder[i++], nullptr, nullptr };
    q.push_back(root);
    while (i < n) {
        node = q.front();
        q.pop_front();
        if (node->data != inOrder[i]) {
            node->left = new Node { preOrder[i++], nullptr, nullptr };
            q.push_back(node->left);
        } else {
            i++;
        }
        if (i < n && node->data != inOrder[i]) {
            node->right = new Node { preOrder[i++], nullptr, nullptr };
            q.push_back(node->right);
        } else {
            i++;
        }
    }
}