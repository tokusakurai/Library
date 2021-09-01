
// 頂点のオイラーツアー
// 計算量 O(V)

// 概要
// 根付き木の頂点をDFSで訪問した順(初めてその頂点に到達した場合のみ)に並べると、各頂点より下の部分木は区間に相当する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2871&lang=ja
// https://judge.yosupo.jp/problem/vertex_add_subtree_sum

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

    vector<int> vs;     // DFS順
    vector<int> ls, rs; // iの部分木は区間[ls[i],rs[i])に対応し、vs[ls[i]] = i

    Graph(int n) : es(n), n(n), m(0), ls(n), rs(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void euler_tour(int now, int pre = -1) {
        ls[now] = vs.size(), vs.push_back(now);
        for (auto &e : es[now]) {
            if (e.to != pre) euler_tour(e.to, now);
        }
        rs[now] = vs.size();
    }
};
