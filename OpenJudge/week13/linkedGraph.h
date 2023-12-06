#include "arrayList.h"
#include "sortedLinkedList.h"
#include <cassert>

template <typename T>
using Vector = arrayList<T>;

template <typename T>
using List = sortedLinkedList<T>;

template <typename T>
class linkedGraph {
private:
    int vertexNum;
    Vector<List<T>> adjList;

public:
    // 创建无向图类，存储结构使用邻接链表，提供操作：插入一条边，删除一条边，BFS，DFS。
    linkedGraph(int n)
        : vertexNum { n }
        , adjList(n + 1)
    {
    }
    ~linkedGraph() = default;

    int size() const { return adjList.size(); }

    void insertEdge(T u, T v)
    {
        assert(u > 0 && u <= this->vertexNum && v > 0 && v <= this->vertexNum);
        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    void deleteEdge(T u, T v)
    {
        assert(u > 0 && u <= this->vertexNum && v > 0 && v <= this->vertexNum);
        adjList[u].remove(v);
        adjList[v].remove(u);
    }

    void dfs(T u, Vector<bool>& visited, Vector<T>& dfsList)
    {
        visited[u] = true;
        dfsList.push_back(u);
        for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
            if (!visited[*it]) {
                dfs(*it, visited, dfsList);
            }
        }
    }

    // 第六行输出从 t 点开始字典序最小的 bfs 序列
    void bfs(T u, Vector<bool>& visited, Vector<T>& bfsList)
    {
        visited[u] = true;
        List<T> queue;
        queue.push_back(u);
        while (!queue.empty()) {
            T u = queue.front();
            queue.pop_front();
            bfsList.push_back(u);
            for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    queue.push_back(*it);
                }
            }
        }
    }

    void connectedComponents(Vector<Vector<T>>& components)
    {
        Vector<bool> visited(adjList.size(), false);
        for (int i = 1; i <= this->vertexNum; ++i) {
            if (!visited[i]) {
                Vector<T> component;
                dfs(i, visited, component);
                components.push_back(component);
            }
        }
    }

    int shortestPath(T s, T t)
    {
        Vector<bool> visited(adjList.size(), false);
        Vector<int> distance(adjList.size(), 0);
        List<T> queue;
        visited[s] = true;
        queue.push_back(s);
        while (!queue.empty()) {
            T u = queue.front();
            queue.pop_front();
            for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    distance[*it] = distance[u] + 1;
                    queue.push_back(*it);
                }
            }
        }
        return distance[t] ? distance[t] : -1;
    }
};
