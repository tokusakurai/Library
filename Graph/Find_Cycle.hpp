
// サイクル検出 (有向・無向 両対応)
// 計算量 O(n + m)

// verified with
// https://judge.yosupo.jp/problem/cycle_detection_undirected
// https://judge.yosupo.jp/problem/cycle_detection

#pragma once
#include <bits/stdc++.h>
using namespace std;

// 任意のサイクルを検出し、(頂点、辺) の組を返す
template <typename G>
pair<vector<int>, vector<int>> find_cycle(const G &g) {
    vector<int> used(g.n, 0), ptr(g.n, 0);
    vector<int> path_v, path_e;
    path_v.reserve(g.n + 1);
    path_e.reserve(g.n);
    for (int s = 0; s < g.n; s++) {
        path_v.push_back(s);
        used[s]++;
        while (!path_v.empty()) {
            int v = path_v.back();
            if (used[v] == 2) {
                for (int i = 0;; i++) {
                    if (path_v[i] == v) {
                        vector<int> cycle_v(begin(path_v) + i, end(path_v));
                        vector<int> cycle_e(begin(path_e) + i, end(path_e));
                        return make_pair(cycle_v, cycle_e);
                    }
                }
            }
            int pre_id = (path_e.empty() ? -1 : path_e.back());
            while (ptr[v] < (int)g[v].size() && g[v][ptr[v]].id == pre_id) ptr[v]++;
            if (ptr[v] == (int)g[v].size()) {
                used[v]--;
                path_v.pop_back();
                if (!path_e.empty()) path_e.pop_back();
            } else {
                auto &e = g[v][ptr[v]++];
                used[e.to]++;
                path_v.push_back(e.to);
                path_e.push_back(e.id);
            }
        }
    }
    return make_pair(vector<int>{}, vector<int>{});
}
