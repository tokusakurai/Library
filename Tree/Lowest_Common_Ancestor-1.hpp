
// （ダブリング）最近共通祖先 (LCA)
// 計算量 構築：O(n log(n))、2 頂点の LCA・距離：O(log(n))
// 空間計算量 O(n log(n))

// 概要
// par[i][j] := 頂点 j の 2^i 個前の祖先とすると、ダブリングでテーブルを埋めることができる。
// 頂点 u,v で根から u の方が v より深いとする。
// まず u を v と同じ深さになるまで引き上げ、その後 u と v が同じ頂点に来ない範囲で両者を同じ高さだけ引き上げる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// https://judge.yosupo.jp/problem/lca
// https://atcoder.jp/contests/abc014/tasks/abc014_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Lowest_Common_Ancestor {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<vector<int>> par; // par[i][j] := 頂点 j の 2^i 個前の祖先
    vector<int> depth;
    const int n;
    int height, m;

    Lowest_Common_Ancestor(int n) : es(n), depth(n), n(n), m(0) {
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

    void build(int root = 0) { // root を根として前準備する
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

    int ancestor(int u, int k) { // u の k 個前の祖先
        for (int i = 0; i < height; i++) {
            if ((k >> i) & 1) u = par[i][u];
            if (u == -1) return -1;
        }
        return u;
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

    int dist(int u, int v) { return depth[u] + depth[v] - depth[lca(u, v)] * 2; }
};
