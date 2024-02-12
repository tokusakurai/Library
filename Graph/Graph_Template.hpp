#pragma once

// グラフテンプレート
// 空間計算量 隣接リスト・隣接リスト (重み付き)：O(n+m)

#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Graph {
    using L = int;

    struct edge {
        int to, id;

        edge(int to, int id) : to(to), id(id) {}

        L get_len() const { return 1; }
    };

    vector<vector<edge>> g;
    const int n;
    int m;

    Graph(int n) : g(n), n(n), m(0) {}

    constexpr bool is_directed() { return directed; }

    inline const vector<edge> &operator[](int k) const { return g[k]; }

    inline vector<edge> &operator[](int k) { return g[k]; }

    void add_edge(int from, int to) {
        g[from].emplace_back(to, m);
        if (!directed) g[to].emplace_back(from, m);
        m++;
    }

    void read(int m, int margin = -1) {
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            add_edge(u + margin, v + margin);
        }
    }

    void read_rooted_tree(int margin = -1) {
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            add_edge(p + margin, i);
        }
    }
};

template <typename T, bool directed = false>
struct Weighted_Graph {
    using L = T;

    struct edge {
        int to, id;
        T len;

        edge(int to, int id, T len) : to(to), id(id), len(len) {}

        L get_len() const { return len; }
    };

    vector<vector<edge>> g;
    const int n;
    int m;

    Weighted_Graph(int n) : g(n), n(n), m(0) {}

    constexpr bool is_directed() { return directed; }

    inline const vector<edge> &operator[](int k) const { return g[k]; }

    inline vector<edge> &operator[](int k) { return g[k]; }

    void add_edge(int from, int to, T len) {
        g[from].emplace_back(to, m, len);
        if (!directed) g[to].emplace_back(from, m, len);
        m++;
    }

    void read(int m, int margin = -1) {
        for (int i = 0; i < m; i++) {
            int u, v;
            T w;
            cin >> u >> v >> w;
            add_edge(u + margin, v + margin, w);
        }
    }

    void read_rooted_tree(int margin = -1) {
        for (int i = 1; i < n; i++) {
            int p;
            T w;
            cin >> p >> w;
            add_edge(p + margin, i, w);
        }
    }
};
