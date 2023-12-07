// 描述
// 使用 prim 算法实现最小生成树

// 格式
// 输入
// 第一行两个整数 n,e。n (1≤n≤200000) 代表图中点的个数，e (0≤m≤500000) 代表边的个数。
// 接下来 e 行，每行代表一条边：

// i j w 表示顶点 i 和顶点 j 之间有一条权重为 w 的边
// 输出
// 最小生成树所有边的权重和

#include "linkedWGraph.h"
#include <iostream>

class Solution {
private:
    int e;
    linkedWGraph<int> graph;

public:
    Solution(int n, int e)
        : e(e)
        , graph(linkedWGraph<int>(n))
    {
    }
    void solve()
    {
        for (int i = 0; i < e; i++) {
            int a, b, w;
            std::cin >> a >> b >> w;
            graph.addEdge(a, b, w);
        }
        std::cout << graph.prim() << std::endl;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, e;
    std::cin >> n >> e;
    Solution solution(n, e);
    solution.solve();
    return 0;
}