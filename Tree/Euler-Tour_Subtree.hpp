
// 部分木に対するオイラーツアー
// 計算量 O(n)

// 概要
// 根付き木の頂点を DFS で訪問した順（初めてその頂点に到達した場合のみ）に並べると、各頂点より下の部分木は区間に相当する。

// verified with
// https://judge.yosupo.jp/problem/vertex_add_subtree_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Euler_Tour_Subtree {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> l, r; // 部分木 i は区間 [l[i],r[i]) に対応する。また、頂点 i は l[i] に対応する。
    const int n;
    int m;

    Euler_Tour_Subtree(int n) : es(n), l(n), r(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void _dfs(int now, int pre, int &cnt) {
        l[now] = cnt++;
        for (auto &e : es[now]) {
            if (e.to != pre) _dfs(e.to, now, cnt);
        }
        r[now] = cnt;
    }

    void build(int root = 0) {
        int cnt = 0;
        _dfs(root, -1, cnt);
    }
};
