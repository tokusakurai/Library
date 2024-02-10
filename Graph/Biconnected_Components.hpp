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

struct Biconnected_Components : Low_Link {
    using L = Low_Link;
    vector<int> comp;
    vector<bool> used;
    const int n;

    Biconnected_Components(int n) : L(n), used(n), n(n) {}

    int _dfs(int now, int pre, int top, int k) {
        used[now] = true;
        for (auto &e : this->es[now]) {
            if (comp[e.id] != -1) continue;
            if (this->ord[e.to] < this->ord[now]) {
                comp[e.id] = top;
            } else if (this->low[e.to] >= this->ord[now]) {
                comp[e.id] = k;
                k = _dfs(e.to, now, k, k + 1);
            } else {
                comp[e.id] = top;
                k = _dfs(e.to, now, top, k);
            }
        }
        return k;
    }

    int decompose() {
        this->build();
        comp.assign(this->m, -1);
        fill(begin(used), end(used), false);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (!used[i]) k = _dfs(i, -1, -1, k);
        }
        return k;
    }
};
