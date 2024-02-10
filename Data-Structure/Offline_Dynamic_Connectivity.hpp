#pragma once

// オフライン dynamic connectivity (クエリがオフラインで与えられるとき、辺の削除にも対応できる union find)
// 計算量 O(n + q log(q)log(n))

// 概要
// クエリの順に辺を並べると、ある辺が挿入されてから削除されるまでの間は区間になる。
// 時刻の区間をセグ木の様に管理すると、ある辺が存在する区間をセグ木上の O(log(q)) 個の区間に分解できる。
// セグ木上を dfs しながら undo union find を使うことによってクエリに答えることができる。

// verified with
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235

#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Undo_Union_Find_Tree.hpp"

struct Offline_Dynamic_Connectivity {
    struct edge {
        int u, v;
        edge(int u, int v) : u(u), v(v) {}
    };

    int n, q;
    vector<tuple<int, int, int, int>> eve;
    vector<tuple<int, int, int, int>> qs;

    Offline_Dynamic_Connectivity(int n) : n(n), q(0) {}

    // 時刻 t に辺 {u,v} を追加
    void insert(int t, int u, int v) {
        if (u > v) swap(u, v);
        eve.emplace_back(t, 1, u, v);
    }

    // 時刻 t に辺 {u,v} を削除
    void erase(int t, int u, int v) {
        if (u > v) swap(u, v);
        eve.emplace_back(t, -1, u, v);
    }

    // 時刻 t 以前の辺の追加削除が終了した後に辺 u,v が連結かどうかを判定
    void query(int t, int u, int v) { qs.emplace_back(t, q++, u, v); }

    vector<bool> solve() {
        sort(begin(eve), end(eve));
        vector<int> ts;
        for (auto [t, c, u, v] : eve) ts.push_back(t);
        ts.erase(unique(begin(ts), end(ts)), end(ts));

        int m = ts.size();
        ts.push_back(INT_MAX);
        int si = 1;
        while (si < m) si <<= 1;
        vector<vector<pair<int, int>>> seg(2 * si);

        auto add_edge = [&](int u, int v, int l, int r) {
            l += si, r += si;
            while (l < r) {
                if (l & 1) seg[l++].emplace_back(u, v);
                if (r & 1) seg[--r].emplace_back(u, v);
                l >>= 1, r >>= 1;
            }
        };

        map<pair<int, int>, vector<int>> mp;
        for (auto [t, c, u, v] : eve) {
            t = lower_bound(begin(ts), end(ts), t) - begin(ts);
            if (c == 1) {
                mp[pair(u, v)].push_back(t);
            } else {
                auto it = mp.find(pair(u, v));
                if (it != end(mp)) {
                    int s = it->second.back();
                    it->second.pop_back();
                    add_edge(u, v, s, t);
                }
            }
        }
        for (auto [e, v] : mp) {
            for (auto s : v) add_edge(e.first, e.second, s, m);
        }

        Undo_Union_Find_Tree uf(n);
        vector<bool> ret(q, false);
        sort(begin(qs), end(qs));
        int ptr = 0;
        while (ptr < q && get<0>(qs[ptr]) < ts[0]) ptr++;

        auto dfs = [&](auto &&dfs, int i) -> void {
            for (auto [u, v] : seg[i]) uf.unite(u, v);
            if (si <= i && i < si + m) {
                while (ptr < q && get<0>(qs[ptr]) < ts[i - si + 1]) {
                    auto [t, id, u, v] = qs[ptr++];
                    ret[id] = uf.same(u, v);
                }
            }
            if (i < si) {
                dfs(dfs, 2 * i);
                dfs(dfs, 2 * i + 1);
            }
            uf.undo((int)seg[i].size());
        };

        dfs(dfs, 1);
        return ret;
    }
};