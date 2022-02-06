
// グラフテンプレート（隣接リスト、隣接リスト（重み付き）、隣接行列、辺集合）
// 空間計算量 隣接リスト・隣接リスト（重み付き）：O(n+m)、隣接行列：O(n^2)、辺集合：O(m)

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Graph {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    Graph(int n) : es(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }
};

template <typename T, bool directed = false>
struct Weighted_Graph {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }
};

template <typename T, bool directed = false>
struct Table {
    vector<vector<T>> es;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;

    inline const vector<T> &operator[](int k) const { return es[k]; }

    inline vector<T> &operator[](int k) { return es[k]; }

    Table(int n) : es(n), n(n) {
        for (int i = 0; i < n; i++) es[i].assign(n, INF_T);
        for (int i = 0; i < n; i++) es[i][i] = 0;
    }

    void add_edge(int from, int to, T cost = 1) {
        es[from][to] = min(es[from][to], cost);
        if (!directed) es[to][from] = min(es[to][from], cost);
    }
};

template <typename T, bool directed = false>
struct Edges {
    struct edge {
        int from, to;
        T cost;
        int id;
        edge(int from, int to, T cost, int id) : from(from), to(to), cost(cost), id(id) {}
    };

    vector<edge> es;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;
    int m;

    Edges(int n) : n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es.emplace_back(from, to, cost, m);
        if (!directed) es.emplace_back(to, from, cost, m);
        m++;
    }
};
