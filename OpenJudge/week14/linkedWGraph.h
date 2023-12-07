#include "PriorityQueue.h"
#include "arrayList.h"
#include "linkedList.h"
#include "unionFind.h"

struct wEdge {
    int a, b, w;

    bool operator<(const wEdge& other) const { return w < other.w; }
    bool operator>(const wEdge& other) const { return w > other.w; }
};
using wEge = struct wEdge;

template <typename T>
using Vector = arrayList<T>;

using List = LinkedList<wEdge>;
using PQueue = PriorityQueue<wEdge, my_less<wEdge>>;

template <typename T>
class linkedWGraph {
private:
    int n;
    Vector<List> graph;

public:
    linkedWGraph(int n)
        : n(n)
        , graph(Vector<List>(n + 1))
    {
    }

    int size() const { return n; }

    void addEdge(int a, int b, int w)
    {
        graph[a].push_back(wEdge { a, b, w });
        graph[b].push_back(wEdge { b, a, w });
    }

    long long prim()
    {
        Vector<bool> visited(n + 1, false);
        PQueue q;
        q.push(wEdge { 0, 1, 0 });
        long long ans = 0;
        while (!q.empty()) {
            wEdge e = q.top();
            q.pop();
            if (visited[e.b]) {
                continue;
            }
            visited[e.b] = true;
            ans += e.w;
            for (auto edge : graph[e.b]) {
                if (!visited[edge.b]) {
                    q.push(edge);
                }
            }
        }
        return ans;
    }

    long long kruskal()
    {
        UnionFind uf(n + 1);
        Vector<wEdge> arr;
        for (int i = 1; i <= n; i++) {
            for (auto edge : graph[i]) {
                arr.push_back(edge);
            }
        }
        heapSort<wEdge, my_greater<wEdge>>(arr.data(), arr.size());
        long long ans = 0;
        for (auto e : arr) {
            int rootX = uf.find(e.a);
            int rootY = uf.find(e.b);

            if (rootX != rootY) {
                uf.unite(e.a, e.b);
                ans += e.w;
            }
        }

        return ans;
    }
};