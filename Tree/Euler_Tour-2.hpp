
// 辺のオイラーツアー
// 計算量 O(n)

// 概要
// 根付き木の頂点と辺を DFS で訪問した順（戻るときに使った辺や頂点もカウントする）に並べる。
// 辺 (u,v) と辺 (v,u) が互いに打ち消し合うようにできればパスを区間としてみなすことができる。

// verified with
// https://atcoder.jp/contests/abc014/tasks/abc014_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Weighted_Graph {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T INF_T;
    const int n;
    int m;

    vector<int> vs, edges;     // 辺を親方向にたどるときは -m して記録
    vector<int> ls, rs, depth; // vs の中で i のものの index の最小値が ls[i]、最大値が rs[i]

    Weighted_Graph(int n) : es(n), INF_T(numeric_limits<T>::max() / 2), n(n), m(0), ls(n), rs(n), depth(n) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    void euler_tour(int now, int pre = -1) {
        if (pre == -1) depth[now] = 0;
        vs.push_back(now);
        ls[now] = edges.size();
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            edges.push_back(e.id);
            depth[e.to] = depth[now] + 1, euler_tour(e.to, now);
            vs.push_back(now), edges.push_back(e.id - m);
        }
        rs[now] = edges.size();
    }
};
