
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

// T: 木 DP のデータ型、E: 辺のデータ型、V: 頂点のデータ
template <typename T, typename V, typename E>
struct Rerooting {
    struct edge {
        int to;
        E data;
        T dp_this;     // from 側の部分木 dp (辺は含まない)
        T dp_opposite; // to 側の部分木 dp (辺も含む)

        edge(int to, const E &data, const T &dp_this, const T &dp_opposite) : to(to), data(data), dp_this(dp_this), dp_opposite(dp_opposite) {}
    };

    using Func_TT = function<T(T, T)>;
    using Func_TV = function<T(T, V)>;
    using Func_TE = function<T(T, E)>;

    vector<vector<edge>> es;
    const int n;
    vector<T> subdp, dp; // 部分木の dp、全方位の dp
    unordered_map<long long, T> mp;
    const Func_TT merge;       // 根なし木のマージ
    const Func_TV attach_root; // 根なし木に根を追加して根付き木にする
    const Func_TE attach_edge; // 根付き木に辺を追加して根なし木にする
    const T e1;                // merge, attach_root の単位元
    const vector<V> base;      // 1 頂点の場合の dp の値

    Rerooting(int n, const Func_TT &merge, const Func_TV &attach_root, const Func_TE &attach_edge, const T &e1, const vector<V> &base) : es(n), n(n), subdp(n, e1), dp(n), merge(merge), attach_root(attach_root), attach_edge(attach_edge), e1(e1), base(base) {}

    void add_edge(int from, int to, const E &data) {
        es[from].emplace_back(to, data, e1, e1);
        es[to].emplace_back(from, data, e1, e1);
    }

    void dfs_sub(int now, int pre = -1) {
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            dfs_sub(e.to, now);
            subdp[now] = merge(subdp[now], attach_edge(subdp[e.to], e.data));
        }
        subdp[now] = attach_root(subdp[now], base[now]);
    }

    void dfs_all(int now, const T &top, int pre = -1) {
        T s = e1;
        for (int i = 0; i < (int)es[now].size(); i++) {
            auto &e = es[now][i];
            e.dp_this = s;
            e.dp_opposite = attach_edge(e.to == pre ? top : subdp[e.to], e.data);
            s = merge(s, e.dp_opposite);
        }
        dp[now] = attach_root(s, base[now]);
        s = e1;
        for (int i = (int)es[now].size() - 1; i >= 0; i--) {
            auto &e = es[now][i];
            e.dp_this = merge(e.dp_this, s);
            e.dp_this = attach_root(e.dp_this, base[now]);
            if (e.to != pre) {
                mp[1LL * n * now + e.to] = e.dp_this;
                mp[1LL * n * e.to + now] = subdp[e.to];
                dfs_all(e.to, e.dp_this, now);
            }
            s = merge(s, e.dp_opposite);
        }
    }

    vector<T> solve() {
        dfs_sub(0);
        dfs_all(0, e1);
        return dp;
    }

    // 辺 {u,v} で切った後の u 側の部分木 dp
    T get_subtree(int u, int v) { return mp[1LL * n * u + v]; }
};
