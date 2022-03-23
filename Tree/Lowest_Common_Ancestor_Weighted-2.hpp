
// （HLD ベース）最近共通祖先 (LCA)
// 計算量 構築：O(n)、2 頂点の LCA・距離：O(log(n))
// 空間計算量 O(n)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// https://judge.yosupo.jp/problem/lca
// https://atcoder.jp/contests/abc014/tasks/abc014_4

template <typename T, bool directed = false>
struct Lowest_Common_Ancestor {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> par, si, depth;
    vector<int> root; // 属する連結成分の根
    vector<T> d;
    const int n;
    int m;

    Lowest_Common_Ancestor(int n) : es(n), par(n), si(n), depth(n), root(n), d(n), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    int _dfs1(int now, int pre = -1) {
        par[now] = pre;
        if (pre == -1) depth[now] = 0, d[now] = 0;
        si[now] = 1;
        for (auto &e : es[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                d[e.to] = d[now] + e.cost;
                si[now] += _dfs1(e.to, now);
            }
        }
        return si[now];
    }

    void _dfs2(int now, bool st, int &s, int pre = -1) {
        root[now] = (st ? now : root[pre]);
        edge heavy = {-1, 0, -1};
        int M = 0;
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            if (M < si[e.to]) M = si[e.to], heavy = e;
        }
        if (heavy.id != -1) _dfs2(heavy.to, false, s, now);
        for (auto &e : es[now]) {
            if (e.to != pre && e.id != heavy.id) _dfs2(e.to, true, s, now);
        }
    }

    void build(int root = 0) {
        _dfs1(root);
        int s = 0;
        _dfs2(root, true, s);
    }

    int lca(int u, int v) {
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        return u;
    }

    T dist(int u, int v) { return d[u] + d[v] - d[lca(u, v)] * 2; }
};
