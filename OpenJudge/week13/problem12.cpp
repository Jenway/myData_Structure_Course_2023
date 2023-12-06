#include "linkedGraph.h"
#include <iostream>

class Solution {
private:
    linkedGraph<int> g;
    int m, s, t;

public:
    Solution(int n)
        : g(n)
    {
        // m (10≤m≤200000) 代表接下来共有 m 个操作
        // s 代表起始点，t 代表终点。
        std::cin >> m >> s >> t;
        // 接下来 m 行，0 代表插入一条边，1 代表删除一条边，接下来两个整数 u，v 代表边的两个端点。
        for (int i = 0; i < m; ++i) {
            int op, u, v;
            std::cin >> op >> u >> v;
            if (op == 0) {
                g.insertEdge(u, v);
            } else {
                g.deleteEdge(u, v);
            }
        }
    }
    void solve()
    {
        // 第一行输出图中有多少个连通分量

        Vector<Vector<int>> components;

        g.connectedComponents(components);
        std::cout << components.size() << "\n";

        // 第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔
        for (auto& component : components) {
            std::cout << *component.begin() << " ";
        }
        std::cout << "\n";

        // 第三行输出从 s 点开始的 dfs 序列长度
        Vector<bool> visited(g.size(), false);
        Vector<int> dfsList;
        g.dfs(s, visited, dfsList);
        std::cout << dfsList.size() << "\n";

        // 第四行输出从 s 点开始的字典序最小的 dfs 序列
        for (auto& v : dfsList) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        // 第五行输出从 t 点开始的 bfs 序列的长度
        visited.assign(g.size(), false);
        Vector<int> bfsList;
        g.bfs(t, visited, bfsList);
        std::cout << bfsList.size() << "\n";

        // 第六行输出从 t 点开始字典序最小的 bfs 序列
        for (auto& v : bfsList) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        // 第七行输出从 s 点到 t 点的最短路径，若是不存在路径则输出-1
        std::cout << g.shortestPath(s, t) << "\n";
    }
};

int main()
{

    int n;
    std::cin >> n;
    Solution s(n);
    s.solve();
    return 0;
}