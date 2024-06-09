#pragma once

// 二重辺連結成分分解 (分解後は森になる)
// 計算量 O(n+m)

// 定義
// 二重辺連結グラフ：どの一辺を取り除いても連結性が保たれるグラフ
// v_1 ～ v_2 <-> v_1 から v_2 に至る 2 つの辺素なパスが存在する
// という (頂点集合における) 同値関係における同値類が二重辺連結成分となる。

// 概要
// Low-Link を用いる。
// 辺 {u,v} が橋であれば u と v は別の連結成分、そうでなければ u と v は同じ連結成分に含まれる。

// verified with
// https://atcoder.jp/contests/arc039/tasks/arc039_d
// https://judge.yosupo.jp/problem/two_edge_connected_components

#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Graph_Template.hpp"
#include "../Graph/Low_Link.hpp"

template <typename G>
struct Two_Edge_Connected_Components : Low_Link<G> {
    using L = Low_Link<G>;
    vector<int> comp;
    int components_number;

    Two_Edge_Connected_Components(const G &g) : L(g), comp(g.n, -1) {
        int k = 0;
        for (int i = 0; i < g.n; i++) {
            if (comp[i] == -1) k = _dfs(i, -1, k, g);
        }
        components_number = k;
    }

    int _dfs(int now, int pre, int k, const G &g) {
        if (pre != -1 && this->ord[pre] >= this->low[now]) {
            comp[now] = comp[pre];
        } else {
            comp[now] = k++;
        }
        for (auto &e : g[now]) {
            if (comp[e.to] == -1) k = _dfs(e.to, now, k, g);
        }
        return k;
    }

    Graph<false> make_graph(const G &g) {
        Graph<false> g2(components_number);
        vector<int> is_bridge(g.m, 0);
        for (auto &e : this->bridge) is_bridge[e]++;
        for (int i = 0; i < g.n; i++) {
            for (auto &e : g[i]) {
                if (is_bridge[e.id]-- > 0) g2.add_edge(comp[i], comp[e.to]);
            }
        }
        return g2;
    }

    int operator[](int k) const { return comp[k]; }
};
