#pragma once

// 二重連結成分分解
// 計算量 O(n+m)

// 定義
// 二重連結グラフ：どの 1 頂点 (とそれに接続する辺) を取り除いても連結性が保たれるグラフ
// e_1 ～ e_2 <-> e_1,e_2 を含む点素な閉路が存在する
// という (辺集合における)同値関係における同値類が二重辺連結成分となる。

// 概要
// Low-Link を用いる。
// 関節点を検出し、その頂点を除いたときに連結となる成分は同じ二重辺連結成分となるようにする。

// verified with
// https://judge.yosupo.jp/problem/biconnected_components

#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Low_Link.hpp"

template <typename G>
struct Biconnected_Components : Low_Link<G> {
    using L = Low_Link<G>;
    vector<vector<int>> comp; // 頂点 i を含む成分
    vector<int> comp_edge;
    int components_number;

    Biconnected_Components(const G &g) : L(g), comp(g.n), comp_edge(g.m, -1) {
        int k = 0;
        for (int i = 0; i < g.n; i++) {
            if (comp[i].empty()) k = _dfs(i, -1, k, g);
        }
        components_number = k;
    }

    int _dfs(int now, int top, int k, const G &g) {
        if (g[now].empty()) {
            comp[now].push_back(k);
            return k + 1;
        }
        if (top != -1) comp[now].push_back(top);
        for (auto &e : g[now]) {
            if (comp_edge[e.id] != -1) continue;
            if (this->ord[e.to] < this->ord[now]) {
                comp_edge[e.id] = top;
            } else if (this->low[e.to] >= this->ord[now]) {
                comp_edge[e.id] = k;
                comp[now].push_back(k);
                k = _dfs(e.to, k, k + 1, g);
            } else {
                comp_edge[e.id] = top;
                k = _dfs(e.to, top, k, g);
            }
        }
        return k;
    }

    int operator[](int k) const { return comp_edge[k]; }
};
