#ifndef binaryTreeNode_
#define binaryTreeNode_
template <typename T>
struct binaryTreeNode {
    T element;
    binaryTreeNode<T>* leftChild;
    binaryTreeNode<T>* rightChild;

    binaryTreeNode(const T& theElement,
        binaryTreeNode* theLeftChild = nullptr,
        binaryTreeNode* theRightChild = nullptr)
        : element(theElement)
        , leftChild(theLeftChild)
        , rightChild(theRightChild)
    {
    }
};

#endif
