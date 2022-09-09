
// (HLD ベース) 最近共通祖先 (LCA)
// 計算量 構築：O(n)、2 頂点の LCA・距離：O(log(n))、level ancestor：O(log(n))
// 空間計算量 O(n)

// 概要
// HL 分解をして、属する成分が同じになるまで片方を引き上げる。
// u,v パスは O(log(n)) 個の列に分解されるため、O(log(n)) 時間で lca を計算できる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
// https://judge.yosupo.jp/problem/lca
// https://judge.yosupo.jp/problem/jump_on_tree
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
    vector<int> par, si, depth;
    vector<int> root;        // 属する連結成分の根
    vector<vector<int>> ids; // 各パスの頂点を並べて保持
    const int n;
    int m;

    Lowest_Common_Ancestor(int n) : es(n), par(n), si(n), depth(n), root(n), ids(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int _dfs1(int now, int pre = -1) {
        par[now] = pre;
        if (pre == -1) depth[now] = 0;
        si[now] = 1;
        for (auto &e : es[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                si[now] += _dfs1(e.to, now);
            }
        }
        return si[now];
    }

    void _dfs2(int now, bool st, int &s, int pre = -1) {
        root[now] = (st ? now : root[pre]);
        ids[root[now]].push_back(now);
        edge heavy = {-1, -1};
        int M = 0;
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            if (M < si[e.to]) M = si[e.to], heavy = e;
        }
        if (heavy.id != -1) _dfs2(heavy.to, false, s, now);
        for (auto &e : es[now]) {
            if (e.to != pre && e.id != heavy.id) _dfs2(e.to, true, s, now);
        }
    }

    void build(int root = 0) {
        _dfs1(root);
        int s = 0;
        _dfs2(root, true, s);
    }

    int lca(int u, int v) {
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        return u;
    }

    int dist(int u, int v) { return depth[u] + depth[v] - depth[lca(u, v)] * 2; }

    // u の k 個前の祖先
    int ancestor(int u, int k) {
        if (k > depth[u]) return -1;
        while (k > 0) {
            int r = root[u];
            int l = depth[u] - depth[r];
            if (k <= l) return ids[r][l - k];
            u = par[r];
            k -= l + 1;
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
