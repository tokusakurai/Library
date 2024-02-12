#pragma once

// (ダブリング) 最近共通祖先 (LCA)
// 計算量 構築：O(n log(n))、2 頂点の LCA・距離：O(log(n))、level ancestor：O(log(n))
// 空間計算量 O(n log(n))

// 概要
// par[i][j] := 頂点 j の 2^i 個前の祖先とすると、ダブリングでテーブルを埋めることができる。
// 頂点 u,v で根から u の方が v より深いとする。
// まず u を v と同じ深さになるまで引き上げ、その後 u と v が同じ頂点に来ない範囲で両者を同じ高さだけ引き上げる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// https://judge.yosupo.jp/problem/lca
// https://judge.yosupo.jp/problem/jump_on_tree
// https://atcoder.jp/contests/abc014/tasks/abc014_4

#include <bits/stdc++.h>
using namespace std;

template <typename G>
struct Lowest_Common_Ancestor {
    using L = typename G::L;

    vector<vector<int>> par; // par[i][j] := 頂点 j の 2^i 個前の祖先
    vector<int> depth;
    vector<L> d;
    int height;

    Lowest_Common_Ancestor(const G &g, int root = 0) : depth(g.n, 0), d(g.n, 0) {
        height = 1;
        while ((1 << height) < g.n) height++;
        par.assign(height, vector<int>(g.n));
        build(g, root);
    }

    void dfs(const G &g, int now, int pre = -1) {
        par[0][now] = pre;
        for (auto &e : g[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                d[e.to] = d[now] + e.get_len();
                dfs(g, e.to, now);
            }
        }
    }

    void build(const G &g, int root) {
        dfs(g, root);
        for (int j = 0; j < height - 1; j++) {
            for (int i = 0; i < g.n; i++) {
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

    L dist(int u, int v) { return d[u] + d[v] - d[lca(u, v)] * 2; }

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
