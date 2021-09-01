
// 全方位木DP
// 計算量 O(N*α) (αは部分木マージと辺追加にかかる計算量)

// 概要
// 1回目のDFSで各部分木における情報を計算する。
// 2回目のDFSでは下側の部分木における情報と上側の部分木における情報をマージする。
// この際に、各頂点から出る辺について左右からの累積和を持っておくことで効率的に計算できる。

// verified with
// https://atcoder.jp/contests/abc160/tasks/abc160_f
// https://atcoder.jp/contests/s8pc-4/tasks/s8pc_4_d
// https://atcoder.jp/contests/dp/tasks/dp_v

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename sum_t, typename key_t, bool directed = false>
struct Rerooting {
    struct edge {
        int to;
        key_t data;
        sum_t dp, ndp; // to側の部分木dp、from側の部分木dp
        edge(int to, key_t data, sum_t dp, sum_t ndp) : to(to), data(data), dp(dp), ndp(ndp) {}
    };

    using F = function<sum_t(sum_t, sum_t)>;
    using G = function<sum_t(sum_t, key_t)>;
    vector<vector<edge>> es;
    vector<sum_t> subdp, dp; // 部分木のdp、全方位のdp
    const F f;               // 1頂点を間に挟んで隣り合う2つの部分木の情報をマージ
    const G g;               // 部分木の根に1本辺を足す
    const sum_t e1;          // fの単位元

    Rerooting(int n, const F &f, const G &g, const sum_t &e1) : es(n), subdp(n, e1), dp(n, e1), f(f), g(g), e1(e1) {}

    void add_edge(int from, int to, const key_t &data) {
        es[from].emplace_back(to, data, e1, e1);
        if (!directed) es[to].emplace_back(from, data, e1, e1);
    }

    void dfs_sub(int now, int pre = -1) {
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            dfs_sub(e.to, now);
            subdp[now] = f(subdp[now], g(subdp[e.to], e.data));
        }
    }

    void dfs_all(int now, const sum_t &top, int pre = -1) {
        sum_t S = e1;
        for (int i = 0; i < (int)es[now].size(); i++) {
            auto &e = es[now][i];
            e.ndp = S;
            e.dp = g(e.to == pre ? top : subdp[e.to], e.data);
            S = f(S, e.dp);
        }
        dp[now] = S;
        S = e1;
        for (int i = (int)es[now].size() - 1; i >= 0; i--) {
            auto &e = es[now][i];
            e.ndp = f(e.ndp, S);
            if (e.to != pre) dfs_all(e.to, e.ndp, now);
            S = f(S, e.dp);
        }
    }

    vector<sum_t> solve() {
        dfs_sub(0);
        dfs_all(0, e1);
        return dp;
    }
};
