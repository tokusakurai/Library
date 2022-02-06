
// クラスカル法（最小全域木）
// 計算量 O(n α(n)+m log(m))

// 概要
// 辺をコストの昇順にソートする。
// Union-Find 木を用いる。
// 上から辺を見ていって、両端が別の連結成分に属していればその辺を採用し、そうでなければ棄却する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

template <typename T, bool directed = false>
struct Edges {
    struct edge {
        int from, to;
        T cost;
        int id;
        edge(int from, int to, T cost, int id) : from(from), to(to), cost(cost), id(id) {}
    };

    vector<edge> es;
    const T INF_T;
    const int n;
    int m;

    Edges(int n) : INF_T(numeric_limits<T>::max() / 2), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es.emplace_back(from, to, cost, m);
        if (!directed) es.emplace_back(to, from, cost, m);
        m++;
    }

    T kruscal() {
        sort(begin(es), end(es), [](const edge &e1, const edge &e2) { return e1.cost < e2.cost; });
        Union_Find_Tree uf(n);
        T ret = 0;
        for (auto &e : es) {
            if (uf.unite(e.from, e.to)) ret += e.cost;
        }
        if (uf.size(0) < n) return INF_T;
        return ret;
    }
};
