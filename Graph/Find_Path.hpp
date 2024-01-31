
// パス検出 (有向・無向 両対応)
// 計算量 O(n + m)

// verified with
// https://atcoder.jp/contests/abc270/tasks/abc270_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

// 任意の s-t パスを検出し、(頂点、辺) の組を返す
template <typename G>
pair<vector<int>, vector<int>> find_path(const G &g, int s, int t) {
    vector<bool> used(g.n, false);
    vector<int> ptr(g.n, 0);
    vector<int> path_v, path_e;
    path_v.reserve(g.n + 1);
    path_e.reserve(g.n);
    path_v.push_back(s);
    used[s] = true;
    while (!path_v.empty()) {
        int v = path_v.back();
        if (v == t) return make_pair(path_v, path_e);
        while (ptr[v] < (int)g[v].size() && used[g[v][ptr[v]].to]) ptr[v]++;
        if (ptr[v] == (int)g[v].size()) {
            path_v.pop_back();
            if (!path_e.empty()) path_e.pop_back();
        } else {
            auto &e = g[v][ptr[v]++];
            used[e.to] = true;
            path_v.push_back(e.to);
            path_e.push_back(e.id);
        }
    }
    return make_pair(vector<int>{}, vector<int>{});
}
