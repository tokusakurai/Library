
// グラフテンプレート
// 空間計算量 隣接リスト・隣接リスト (重み付き)：O(n+m)

#pragma once
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

    vector<vector<edge>> es;
    const int n;
    int m;

    Graph(int n) : es(n), n(n), m(0) {}

    bool is_directed() { return directed; }

    inline const vector<edge> &operator[](int k) const { return es[k]; }

    inline vector<edge> &operator[](int k) { return es[k]; }

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
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

    vector<vector<edge>> es;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), n(n), m(0) {}

    bool is_directed() { return directed; }

    inline const vector<edge> &operator[](int k) const { return es[k]; }

    inline vector<edge> &operator[](int k) { return es[k]; }

    void add_edge(int from, int to, T len) {
        es[from].emplace_back(to, m, len);
        if (!directed) es[to].emplace_back(from, m, len);
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
