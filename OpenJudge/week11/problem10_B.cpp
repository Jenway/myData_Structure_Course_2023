// 格式
// 输入
// 一串小写字母组成的字符串（不超过 1000000)。

// 输出
// 输出这个字符串通过 Huffman 编码后的长度。
#include "HuffmanTree.h"
#include <iostream>

class Solution {
private:
    String input;

public:
    Solution(const String& input)
        : input(input)
    {
    }
    ~Solution() = default;
    void runtest()
    {
        int weight[26] = { 0 };
        for (auto& i : input) {
            weight[i - 'a']++;
        }
        minHeap weightHeap = HuffmanTree::calFrequency(input.c_str(), input.size());
        HuffmanTree h;
        h.buildTree(weightHeap);
        h.assignCode();
        std::cout << h.calLength(input) << std::endl;
    }
};

int main(void)
{
    String input;
    std::cin >> input;
    Solution s { input };
    s.runtest();
}