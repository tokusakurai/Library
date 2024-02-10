#pragma once

// (ダブリング) 最近共通祖先 (LCA)
// 計算量 構築：O(n log(n))、2 頂点の LCA・距離：O(log(n))、level ancestor：O(log(n))
// 空間計算量 O(n log(n))

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// https://judge.yosupo.jp/problem/lca
// https://atcoder.jp/contests/abc014/tasks/abc014_4

#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Lowest_Common_Ancestor {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<vector<int>> par; // par[i][j] := 頂点 j の 2^i 個前の祖先
    vector<int> depth;
    vector<T> d;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;
    int m, height;

    Lowest_Common_Ancestor(int n) : es(n), depth(n), d(n), n(n), m(0) {
        height = 1;
        while ((1 << height) < n) height++;
        par.assign(height, vector<int>(n));
    }

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    void prepare(int now, int pre = -1) {
        if (pre == -1) depth[now] = 0, d[now] = 0;
        par[0][now] = pre;
        for (auto &e : es[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                d[e.to] = d[now] + e.cost;
                prepare(e.to, now);
            }
        }
    }

    void build(int root = 0) {
        prepare(root);
        for (int j = 0; j < height - 1; j++) {
            for (int i = 0; i < n; i++) {
                if (par[j][i] == -1) {
                    par[j + 1][i] = -1;
                } else {
                    par[j + 1][i] = par[j][par[j][i]];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = ancestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = height - 1; i >= 0; i--) {
            if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
        }
        return par[0][u];
    }

    T dist(int u, int v) { return d[u] + d[v] - d[lca(u, v)] * 2; }

    // u の k 個前の祖先
    int ancestor(int u, int k) {
        if (k > depth[u]) return -1;
        for (int i = 0; i < height; i++) {
            if ((k >> i) & 1) u = par[i][u];
        }
        return u;
    }

    // u から v の方向へ k 回移動
    int move(int u, int v, int k) {
        int w = lca(u, v);
        int l = depth[u] + depth[v] - depth[w] * 2;
        if (k > l) return -1;
        if (k <= depth[u] - depth[w]) return ancestor(u, k);
        return ancestor(v, l - k);
    }
};
