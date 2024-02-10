#pragma once

// オイラー閉路・オイラー路の検出
// 計算量 オイラー閉路：O(n+m)、オイラー路：O((n+m)α(n))

// 概要
// オイラー路：全ての辺をちょうど一度通るパス
// オイラー閉路：閉路になるオイラー路
// 連結グラフがオイラー閉路をもつ必要十分条件
// 有向グラフ：すべての頂点について (入次数) = (出次数)
// 無向グラフ：全ての頂点の次数が偶数
// 連結グラフがオイラー路をもつ (かつオイラー閉路はもたない) 必要十分条件
// 有向グラフ：(入次数) - (出次数) = +1, -1 である頂点がちょうど 1 つずつあり、それ以外は全て 0
// 無向グラフ：次数が奇数である頂点がちょうど 2 つある

// verified with
// https://codeforces.com/contest/1361/problem/C
// https://yukicoder.me/problems/no/583
// https://atcoder.jp/contests/abc227/tasks/abc227_h
// https://codeforces.com/contest/1610/problem/F

#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

template <bool directed = false>
struct Eulerian_Trail {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<bool> used_e, used_v;
    vector<int> deg;
    const int n;
    int m;

    Eulerian_Trail(int n) : es(n), used_v(n), deg(n, 0), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m++);
        if (directed) {
            deg[from]++, deg[to]--;
        } else {
            es[to].emplace_back(from, m++);
            deg[from]++, deg[to]++;
        }
    }

    vector<int> trace(int s, bool use_id = false) {
        stack<edge> st;
        vector<int> ret;
        st.emplace(s, -1);
        while (!st.empty()) {
            int now = st.top().to;
            used_v[now] = true;
            if (es[now].empty()) {
                ret.push_back(use_id ? st.top().id : now);
                st.pop();
            } else {
                auto &e = es[now].back();
                es[now].pop_back();
                int id = directed ? e.id : e.id / 2;
                if (used_e[id]) continue;
                used_e[id] = true;
                st.push(e);
            }
        }
        if (use_id) ret.pop_back();
        reverse(begin(ret), end(ret));
        return ret;
    }

    // 各連結成分に対してオイラー閉路を列挙
    vector<vector<int>> eulerian_trail(bool use_id = false) {
        vector<vector<int>> ret;
        fill(begin(used_v), end(used_v), false);
        if (directed) {
            for (auto &e : deg) {
                if (e != 0) return {};
            }
        } else {
            for (auto &e : deg) {
                if (e & 1) return {};
            }
        }
        used_e.assign(directed ? m : m / 2, false);
        for (int i = 0; i < n; i++) {
            if (!used_v[i]) ret.push_back(trace(i, use_id));
        }
        return ret;
    }

    // 各連結成分に対してオイラー路を列挙
    vector<vector<int>> semi_eulerian_trail(bool use_id = false) {
        Union_Find_Tree uf(n);
        for (int i = 0; i < n; i++) {
            for (auto &e : es[i]) uf.unite(i, e.to);
        }
        vector<vector<int>> group(n);
        for (int i = 0; i < n; i++) group[uf[i]].push_back(i);
        vector<vector<int>> ret;
        used_e.assign(directed ? m : m / 2, false);
        for (auto &vs : group) {
            if (vs.empty()) continue;
            int s = -1, t = -1;
            if (directed) {
                for (auto &u : vs) {
                    if (abs(deg[u]) > 1) return {};
                    if (deg[u] == 1) {
                        if (s != -1) return {};
                        s = u;
                    }
                }
            } else {
                for (auto &u : vs) {
                    if (deg[u] & 1) {
                        if (s != -1 && t != -1) return {};
                        (s == -1 ? s : t) = u;
                    }
                }
            }
            ret.push_back(trace(s == -1 ? vs.front() : s, use_id));
        }
        return ret;
    }
};
