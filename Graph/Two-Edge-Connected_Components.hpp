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

struct Two_Edge_Connected_Components : Low_Link {
    using L = Low_Link;
    vector<int> comp;
    const int n;

    Two_Edge_Connected_Components(int n) : L(n), comp(n), n(n) {}

    int _dfs(int now, int pre, int k) {
        if (pre != -1 && this->ord[pre] >= this->low[now]) {
            comp[now] = comp[pre];
        } else {
            comp[now] = k++;
        }
        for (auto &e : this->es[now]) {
            if (comp[e.to] == -1) k = _dfs(e.to, now, k);
        }
        return k;
    }

    Graph<false> decompose() {
        this->build();
        fill(begin(comp), end(comp), -1);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (comp[i] == -1) k = _dfs(i, -1, k);
        }
        Graph<false> ret(k);
        vector<int> is_bridge(this->m, 0);
        for (auto &e : this->bridge) is_bridge[e]++;
        for (int i = 0; i < n; i++) {
            for (auto &e : this->es[i]) {
                if (is_bridge[e.id]-- > 0) ret.add_edge(comp[i], comp[e.to]);
            }
        }
        return ret;
    }

    int operator[](int i) const { return comp[i]; }
};
