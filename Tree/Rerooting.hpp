
// 全方位木 DP
// 計算量 O(nα) (α は部分木マージと辺追加にかかる計算量)

// 概要
// 1回目の DFS で各部分木における情報を計算する。
// 2回目の DFS では下側の部分木における情報と上側の部分木における情報をマージする。
// この際に、各頂点から出る辺について左右からの累積和を持っておくことで効率的に計算できる。

// verified with
// https://judge.yosupo.jp/problem/tree_path_composite_sum
// https://atcoder.jp/contests/abc160/tasks/abc160_f
// https://atcoder.jp/contests/s8pc-4/tasks/s8pc_4_d
// https://atcoder.jp/contests/dp/tasks/dp_v
// https://atcoder.jp/contests/abc220/tasks/abc220_f
// https://atcoder.jp/contests/abc298/tasks/abc298_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Tree_DP, bool store_subtree = false>
struct Rerooting {
    using T = typename Tree_DP::T;
    using V = typename Tree_DP::V;
    using E = typename Tree_DP::E;

    struct edge {
        int to;
        E data;
        T dp_this;     // from 側の部分木 dp (辺は含まない)
        T dp_opposite; // to 側の部分木 dp (辺も含む)

        edge(int to, const E &data) : to(to), data(data), dp_this(Tree_DP::id), dp_opposite(Tree_DP::id) {}
    };

    vector<vector<edge>> es;
    const int n;
    vector<T> subdp, dp; // 部分木の dp、全方位の dp
    unordered_map<long long, T> mp;
    const vector<V> base; // 1 頂点の場合の dp の値

    Rerooting(int n, const vector<V> &base) : es(n), n(n), subdp(n, Tree_DP::id), dp(n), base(base) {}

    void add_edge(int from, int to, const E &data) {
        es[from].emplace_back(to, data);
        es[to].emplace_back(from, data);
    }

    void dfs_sub(int now, int pre = -1) {
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            dfs_sub(e.to, now);
            subdp[now] = Tree_DP::merge(subdp[now], Tree_DP::attach_edge(subdp[e.to], e.data));
        }
        subdp[now] = Tree_DP::attach_root(subdp[now], base[now]);
    }

    void dfs_all(int now, const T &top, int pre = -1) {
        T s = Tree_DP::id;
        for (int i = 0; i < (int)es[now].size(); i++) {
            auto &e = es[now][i];
            e.dp_this = s;
            e.dp_opposite = Tree_DP::attach_edge(e.to == pre ? top : subdp[e.to], e.data);
            s = Tree_DP::merge(s, e.dp_opposite);
        }
        dp[now] = Tree_DP::attach_root(s, base[now]);
        s = Tree_DP::id;
        for (int i = (int)es[now].size() - 1; i >= 0; i--) {
            auto &e = es[now][i];
            e.dp_this = Tree_DP::merge(e.dp_this, s);
            e.dp_this = Tree_DP::attach_root(e.dp_this, base[now]);
            if (e.to != pre) {
                if (store_subtree) {
                    mp[1LL * n * now + e.to] = e.dp_this;
                    mp[1LL * n * e.to + now] = subdp[e.to];
                }
                dfs_all(e.to, e.dp_this, now);
            }
            s = Tree_DP::merge(s, e.dp_opposite);
        }
    }

    vector<T> solve() {
        dfs_sub(0);
        dfs_all(0, Tree_DP::id);
        return dp;
    }

    // 辺 {u,v} で切った後の u 側の部分木 dp
    T get_subtree(int u, int v) {
        assert(store_subtree);
        return mp[1LL * n * u + v];
    }
};
