#include "arrayList.h"

class UnionFind {
private:
    using Vector = arrayList<int>;
    Vector parent;

public:
    UnionFind(int size)
    {
        parent.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        return (parent[x] == x) ? x : (parent[x] = find(parent[x]));
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    bool isConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};