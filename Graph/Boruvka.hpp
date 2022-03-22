
// Boruvka 法（最小全域木）
// 計算量 O(m log(n))

// 概要
// 各連結成分について、他の連結成分と自身を結ぶ最小コストの辺を採用する。
// 各ステップで連結成分の数は半分以下になるから、ステップ回数は O(log(n)) 回。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

template <typename T, bool directed = false>
struct Boruvka {
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

    Boruvka(int n) : n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es.emplace_back(from, to, cost, m);
        if (!directed) es.emplace_back(to, from, cost, m);
        m++;
    }

    T min_spanning_tree() {
        Union_Find_Tree uf(n);
        T ret = 0;
        while (uf.size(0) < n) {
            vector<pair<T, int>> mincost(n, make_pair(INF_T, -1));
            for (auto &e : es) {
                int u = uf.root(e.from), v = uf.root(e.to);
                if (u != v && e.cost < mincost[u].first) mincost[u] = make_pair(e.cost, v);
            }
            bool flag = true;
            for (int i = 0; i < n; i++) {
                if (mincost[i].second == -1) continue;
                flag = false;
                if (uf.unite(i, mincost[i].second)) ret += mincost[i].first;
            }
            if (flag) return INF_T;
        }
        return ret;
    }
};
