
// Heavy-Light分解
// 計算量 HL分解 : O(V)、パス検出・パスが通る区間の個数 : O(log(V))

// 概要
// 根付き木の各頂点の重みを、その頂点を根とする部分木の頂点数とする。
// 各頂点について、子のうち重みが最大のものとの間の辺のみを残す。
// 結果として木はいくつかの列に分割され、任意の2頂点間の単純パスについて通る列の個数は最大でO(log(V))個となる。

// verified with
// https://judge.yosupo.jp/problem/vertex_add_path_sum
// https://judge.yosupo.jp/problem/vertex_set_path_composite

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
    vector<int> par, si, depth;
    vector<int> root;       // 属する連結成分の根
    vector<int> id_v, id_e; // 各頂点、各辺が一列に並べたときに何番目に相当するか
    const int n;
    int m;

    Graph(int n) : es(n), par(n), si(n), depth(n), root(n), id_v(n), id_e(n - 1), n(n), m(0) {}

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
        id_v[now] = s++;
        edge heavy = {-1, -1};
        int M = 0;
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            if (M < si[e.to]) M = si[e.to], heavy = e;
        }
        if (heavy.id != -1) {
            id_e[heavy.id] = s;
            _dfs2(heavy.to, false, s, now);
        }
        for (auto &e : es[now]) {
            if (e.to != pre && e.id != heavy.id) {
                id_e[e.id] = s;
                _dfs2(e.to, true, s, now);
            }
        }
    }

    void decompose(int root = 0) {
        _dfs1(root);
        int s = 0;
        _dfs2(root, true, s);
    }

    vector<pair<int, int>> get_path(int u, int v, bool use_edge = false) { //パスに対応する区間たちを列挙
        vector<pair<int, int>> ret;
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            ret.emplace_back(id_v[root[v]], id_v[v] + 1);
            v = par[root[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        ret.emplace_back(id_v[u] + use_edge, id_v[v] + 1);
        return ret;
    }

    vector<pair<int, int>> get_path_noncommutative(int u, int v, bool use_edge = false) { // クエリが非可換の場合
        vector<pair<int, int>> l, r;
        while (root[u] != root[v]) {
            if (depth[root[u]] > depth[root[v]]) {
                l.emplace_back(id_v[u] + 1, id_v[root[u]]);
                u = par[root[u]];
            } else {
                r.emplace_back(id_v[root[v]], id_v[v] + 1);
                v = par[root[v]];
            }
        }
        if (depth[u] > depth[v])
            l.emplace_back(id_v[u] + 1, id_v[v] + use_edge);
        else
            r.emplace_back(id_v[u] + use_edge, id_v[v] + 1);
        reverse(begin(r), end(r));
        for (auto &e : r) l.push_back(e);
        return l;
    }
};
