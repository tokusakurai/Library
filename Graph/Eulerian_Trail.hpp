
// オイラー閉路・オイラー路の検出
// 計算量 オイラー閉路、オイラー路：O(n+m)

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
// https://judge.yosupo.jp/problem/eulerian_trail_directed
// https://judge.yosupo.jp/problem/eulerian_trail_undirected

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename G>
pair<vector<int>, vector<int>> find_trail(const G &g, int s, vector<int> &ptr, vector<bool> &used_v, vector<bool> &used_e) {
    stack<int> st_v, st_e;
    vector<int> trail_v, trail_e;
    st_v.push(s);
    st_e.push(-1);
    while (!st_v.empty()) {
        int now = st_v.top();
        used_v[now] = true;
        if (ptr[now] == (int)g[now].size()) {
            trail_v.push_back(now);
            trail_e.push_back(st_e.top());
            st_v.pop();
            st_e.pop();
        } else {
            auto &e = g[now][ptr[now]++];
            if (used_e[e.id]) continue;
            used_e[e.id] = true;
            st_v.push(e.to);
            st_e.push(e.id);
        }
    }
    trail_e.pop_back();
    reverse(begin(trail_v), end(trail_v));
    reverse(begin(trail_e), end(trail_e));
    return make_pair(trail_v, trail_e);
}

// 各連結成分に対してオイラー閉路を列挙
template <typename G>
vector<pair<vector<int>, vector<int>>> Eulerian_circuit(const G &g) {
    vector<int> deg(g.n, 0);
    for (int i = 0; i < g.n; i++) {
        for (auto &e : g[i]) {
            deg[i]++;
            deg[e.to] += (g.is_directed() ? -1 : 1);
        }
    }
    if (!g.is_directed()) {
        for (int i = 0; i < g.n; i++) deg[i] >>= 1;
    }
    vector<pair<vector<int>, vector<int>>> ret;
    if (g.is_directed()) {
        for (auto &e : deg) {
            if (e != 0) return {};
        }
    } else {
        for (auto &e : deg) {
            if (e & 1) return {};
        }
    }
    vector<int> ptr(g.n, 0);
    vector<bool> used_v(g.n, false), used_e(g.m, false);
    for (int i = 0; i < g.n; i++) {
        if (!used_v[i]) ret.push_back(find_trail(g, i, ptr, used_v, used_e));
    }
    return ret;
}

// 各連結成分に対してオイラー路を列挙
template <typename G>
vector<pair<vector<int>, vector<int>>> Eulerian_trail(const G &g) {
    vector<int> deg(g.n, 0);
    vector<vector<int>> rs(g.n);
    for (int i = 0; i < g.n; i++) {
        for (auto &e : g[i]) {
            deg[i]++;
            if (g.is_directed()) {
                deg[e.to]--;
                rs[e.to].push_back(i);
            } else {
                deg[e.to]++;
            }
        }
    }
    if (!g.is_directed()) {
        for (int i = 0; i < g.n; i++) deg[i] >>= 1;
    }
    vector<vector<int>> group;
    vector<int> ptr(g.n, 0);
    vector<bool> used_v(g.n, false), used_e(g.m, false);
    for (int i = 0; i < g.n; i++) {
        if (!used_v[i]) {
            queue<int> que;
            group.emplace_back();

            auto insert = [&](int v) {
                if (used_v[v]) return;
                used_v[v] = true;
                que.push(v);
                group.back().push_back(v);
            };

            insert(i);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto &e : g[v]) insert(e.to);
                for (auto &e : rs[v]) insert(e);
            }
        }
    }
    vector<pair<vector<int>, vector<int>>> ret;
    fill(begin(used_v), end(used_v), false);
    for (auto &vs : group) {
        int s = -1, t = -1;
        if (g.is_directed()) {
            for (auto &v : vs) {
                if (abs(deg[v]) > 1) return {};
                if (deg[v] == 1) {
                    if (s != -1) return {};
                    s = v;
                }
            }
        } else {
            for (auto &v : vs) {
                if (deg[v] & 1) {
                    if (s != -1 && t != -1) return {};
                    (s == -1 ? s : t) = v;
                }
            }
        }
        if (s == -1) s = vs.front();
        ret.push_back(find_trail(g, s, ptr, used_v, used_e));
    }
    return ret;
}
