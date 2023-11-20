#include "PriorityQueue.h"
#include "linkedBinaryTree.h"
#include "string.hpp"

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode *left, *right;
    HuffmanNode(char data = '\0', int frequency = 0)
        : data(data)
        , frequency(frequency)
        , left(nullptr)
        , right(nullptr)
    {
    }
};
class compare {
public:
    bool operator()(HuffmanNode*& a, HuffmanNode*& b)
    {
        return a->frequency < b->frequency;
    }
};

using BinaryTree = linkedBinaryTree<char, HuffmanNode>;
using minHeap = PriorityQueue<HuffmanNode*, compare>;
using String = my_string;

class HuffmanTree {
private:
    HuffmanNode* root;
    BinaryTree* tree;
    String codes[26];

    void assignCode(HuffmanNode* n, String code)
    {
        if (n == nullptr) {
            return;
        }
        if (n->left == nullptr && n->right == nullptr) {
            codes[n->data - 'a'] = code;
        }
        if (n->left) {
            assignCode(n->left, code + "0");
        }
        if (n->right) {
            assignCode(n->right, code + "1");
        }
    }

public:
    HuffmanTree()
        : root(nullptr)
        , tree(nullptr)
    {
    }

    ~HuffmanTree()
    {
        delete tree;
        tree = nullptr;
    }

    static minHeap calFrequency(const char* input, int length)
    {
        int weight[26] = { 0 };
        for (int i = 0; i < length; i++) {
            weight[input[i] - 'a']++;
        }

        minHeap weightHeap;
        for (int i = 0; i < 26; i++) {
            if (weight[i] != 0) {
                HuffmanNode* h = new HuffmanNode;
                h->data = 'a' + i;
                h->frequency = weight[i];
                weightHeap.push(h);
            }
        }
        return weightHeap;
    }

    void buildTree(minHeap& weightHeap)
    {
        if (tree != nullptr) {
            delete tree;
            tree = nullptr;
            root = nullptr;
        }
        while (weightHeap.size() > 1) {
            HuffmanNode* node1 = weightHeap.top();
            weightHeap.pop();
            HuffmanNode* node2 = weightHeap.top();
            weightHeap.pop();

            HuffmanNode* newNode = new HuffmanNode('\0', node1->frequency + node2->frequency);
            newNode->left = node1;
            newNode->right = node2;

            weightHeap.push(newNode);
        }
        this->tree = new BinaryTree(weightHeap.top());
        this->root = weightHeap.top();
        weightHeap.pop();
    }

    void assignCode()
    {
        assignCode(root, "");
    }

    int calLength(String& input)
    {
        int length = 0;
        for (auto& i : input) {
            length += codes[i - 'a'].size();
        }
        return length;
    }

    void showCode()
    {
        for (int i = 0; i < 26; i++) {
            if (codes[i].size() != 0) {
                std::cout << char('a' + i) << " " << codes[i] << std::endl;
            }
        }
    }

    String compress(const String& input)
    {
        String res;
        for (const auto& i : input) {
            res += codes[i - 'a'];
        }
        return res;
    }
    String decompress(const String& input)
    {
        String res;
        HuffmanNode* p = root;
        for (const auto& i : input) {
            if (i == '0') {
                p = p->left;
            } else {
                p = p->right;
            }
            if (p->left == nullptr && p->right == nullptr) {
                res += p->data;
                p = root;
            }
        }
        return res;
    }
};
