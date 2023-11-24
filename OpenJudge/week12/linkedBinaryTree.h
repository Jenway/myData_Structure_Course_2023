#include "arrayQueue.h"
#include "arrayStack.h"
#include <iostream>

template <typename K, typename E>
struct Pair {
    K first;
    E second;
};

template <typename T>
using my_Queue = ArrayQueue<T>;

template <typename T>
using my_Stack = ArrayStack<T>;

template <typename T>
struct node {
    T data;
    node* left;
    node* right;
};

template <typename T, typename Node = node<T>>
class linkedBinaryTree {
    using Queue = my_Queue<Node*>;
    using Stack = my_Stack<Node*>;

public:
    linkedBinaryTree()
        : root { nullptr }
        , _size { 0 }
        , nodeIndex { nullptr }
    {
    }
    linkedBinaryTree(Node* root)
        : root { root }
        , _size { 0 }
        , nodeIndex { nullptr }
    {
    }
    ~linkedBinaryTree()
    {
        clear();
    }
    int size() const { return _size; }

    void input();

    void preOrder(void (*visit)(Node* node)) { preOrder(root, visit); }
    void inOrder(void (*visit)(Node* node)) { inOrder(root, visit); }
    void postOrder(void (*visit)(Node* node)) { postOrder(root, visit); }
    void levelOrder(void (*visit)(Node* node)) { levelOrder(root, visit); }

    void count_all();
    void height_all();

private:
    Node* root;
    int _size;
    Node** nodeIndex;

    void preOrder(Node* node, void (*visit)(Node* node));
    void inOrder(Node* node, void (*visit)(Node* node));
    void postOrder(Node* node, void (*visit)(Node* node));
    void levelOrder(Node* node, void (*visit)(Node* node));

    Node* find(int i)
    {
        if (i > _size) {
            return nullptr;
        } else {
            return nodeIndex[i];
        }
    }
    int count(Node* node);
    int height(Node* node);

    void clear()
    {
        postOrder(root, [](Node* node) { delete node; });
    }
};

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::preOrder(Node* node, void (*visit)(Node* node))
{
    if (node != nullptr) {
        visit(node);
        preOrder(node->left, visit);
        preOrder(node->right, visit);
    }
}

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::inOrder(Node* node, void (*visit)(Node* node))
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::postOrder(Node* node, void (*visit)(Node* node))
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::levelOrder(Node* node, void (*visit)(Node* node))
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

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::count_all()
{

    for (int i = 1; i <= size(); i++) {
        std::cout << count(find(i)) << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename Node>
int linkedBinaryTree<T, Node>::count(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        return 1 + count(node->left) + count(node->right);
    }
}

template <typename T, typename Node>
void linkedBinaryTree<T, Node>::height_all()
{
    for (int i = 1; i <= size(); i++) {
        std::cout << height(find(i)) << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename Node>
int linkedBinaryTree<T, Node>::height(Node* node)
{
    if (node == nullptr) {
        return 0;
    } else {
        int left = height(node->left);
        int right = height(node->right);
        return 1 + (left > right ? left : right);
    }
}
