
// 2-SAT (リテラル数が 2 のクロージャーの乗法標準形の充足可能性を判定する)
// 計算量 O(n)

// 概要
// (x || y) <-> (!x -> y) || (!y -> x)
// であるから、各論理変数 x について x と !x の状態を用意して、x -> y のときに x から y への有向辺を貼ったグラフを考えると
// 各 x について x と !x が同じ強連結成分に含まれなければ充足可能。
// x と !x でトポロジカル順序が大きい方を採用すれば解の 1 つを構築できる。

// verified with
// https://judge.yosupo.jp/problem/two_sat

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Strongly-Connected_Components.hpp"

struct Two_SAT {
    Strongly_Connected_Components G;
    const int n;

    Two_SAT(int n) : G(2 * n), n(n) {}

    // ((is_x_true? x : !x) or (is_y_true? y : !y))
    void add_clause(int x, bool is_x_true, int y, bool is_y_true) {
        G.add_edge(x + (is_x_true ? n : 0), y + (is_y_true ? 0 : n));
        G.add_edge(y + (is_y_true ? n : 0), x + (is_x_true ? 0 : n));
    }

    // (充足可能性、可能ならば解の 1 つ)
    pair<bool, vector<bool>> solve() {
        G.decompose();
        vector<bool> ret(n);
        for (int i = 0; i < n; i++) {
            if (G.comp[i] == G.comp[n + i]) return make_pair(false, ret);
            ret[i] = (G.comp[i] > G.comp[n + i]);
        }
        return make_pair(true, ret);
    }
};
