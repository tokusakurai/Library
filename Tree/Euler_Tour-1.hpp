
// 頂点のオイラーツアー
// 計算量 O(n+m)

// 概要
// 根付き木の頂点を DFS で訪問した順（初めてその頂点に到達した場合のみ）に並べると、各頂点より下の部分木は区間に相当する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2871&lang=ja
// https://judge.yosupo.jp/problem/vertex_add_subtree_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Euler_Tour_Vertex {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> vs;     // DFS 順
    vector<int> ls, rs; // i の部分木は区間 [ls[i],rs[i]) に対応し、vs[ls[i]] = i
    const int n;
    int m;

    Euler_Tour_Vertex(int n) : es(n), n(n), m(0), ls(n), rs(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void build(int now, int pre = -1) {
        ls[now] = vs.size(), vs.push_back(now);
        for (auto &e : es[now]) {
            if (e.to != pre) build(e.to, now);
        }
        rs[now] = vs.size();
    }
};
