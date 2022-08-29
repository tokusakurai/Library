
// 全方位木 DP
// 計算量 O(nα) (α は部分木マージと辺追加にかかる計算量)

// 概要
// 1回目の DFS で各部分木における情報を計算する。
// 2回目の DFS では下側の部分木における情報と上側の部分木における情報をマージする。
// この際に、各頂点から出る辺について左右からの累積和を持っておくことで効率的に計算できる。

// verified with
// https://atcoder.jp/contests/abc160/tasks/abc160_f
// https://atcoder.jp/contests/s8pc-4/tasks/s8pc_4_d
// https://atcoder.jp/contests/dp/tasks/dp_v
// https://atcoder.jp/contests/abc220/tasks/abc220_f

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename sum_t, typename key_t, bool directed = false>
struct Rerooting {
    struct edge {
        int to;
        key_t data;
        sum_t dp, ndp; // to 側の部分木 dp (辺も含む)、from 側の部分木 dp (辺は含まない)
        edge(int to, key_t data, sum_t dp, sum_t ndp) : to(to), data(data), dp(dp), ndp(ndp) {}
    };

    using F = function<sum_t(sum_t, sum_t)>;
    using G = function<sum_t(sum_t, key_t)>;
    vector<vector<edge>> es;
    vector<sum_t> subdp, dp;  // 部分木の dp、全方位の dp
    const F f;                // 1 頂点を間に挟んで隣り合う 2 つの部分木の情報をマージ
    const G g;                // 部分木の根に 1 本辺を足す
    const sum_t e1;           // f の単位元
    const vector<sum_t> base; // 1 頂点の場合の dp の値

    Rerooting(int n, const F &f, const G &g, const sum_t &e1, const vector<sum_t> &base) : es(n), subdp(base), dp(n), f(f), g(g), e1(e1), base(base) {}

    void add_edge(int from, int to, const key_t &data) {
        es[from].emplace_back(to, data, e1, base[from]);
        if (!directed) es[to].emplace_back(from, data, e1, base[to]);
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
            e.ndp = f(e.ndp, S);
            e.dp = g(e.to == pre ? top : subdp[e.to], e.data);
            S = f(S, e.dp);
        }
        dp[now] = f(base[now], S);
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
