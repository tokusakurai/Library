
// 最近共通祖先(LCA)
// 計算量 構築 : O(V*log(V))、2頂点のLCA・距離 : O(log(V))
// 空間計算量 O(V*log(V))

// 概要
// par[i][j] := 頂点jの2^i個前の祖先とすると、ダブリングでテーブルを埋めることができる。
// 頂点u,vで根からuの方がvより深いとする。
// まずuをvと同じ深さになるまで引き上げ、その後uとvが同じ頂点に来ない範囲で両者を同じ高さだけ引き上げる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// https://judge.yosupo.jp/problem/lca
// https://atcoder.jp/contests/abc014/tasks/abc014_4

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

    vector<vector<int>> par; // par[i][j] := 頂点jの2^i個前の祖先
    vector<int> depth;
    int height;

    Graph(int n) : es(n), n(n), m(0), depth(n) {
        height = 1;
        while ((1 << height) < n) height++;
        par.assign(height, vector<int>(n));
    }

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void prepare(int now, int pre = -1) {
        if (pre == -1) depth[now] = 0;
        par[0][now] = pre;
        for (auto &e : es[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                prepare(e.to, now);
            }
        }
    }

    void build(int root = 0) { // rootを根として前準備する
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
        int D = depth[u] - depth[v];
        for (int i = 0; i < height; i++) {
            if ((D >> i) & 1) u = par[i][u];
        }
        if (u == v) return u;
        for (int i = height - 1; i >= 0; i--) {
            if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
        }
        return par[0][u];
    }

    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};
