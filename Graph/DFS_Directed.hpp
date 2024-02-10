#pragma once

// 有向グラフでの基本的な DFS
// 計算量 パス検出・トポロジカルソート・閉路検出：O(n+m)

// 概要
// 直前に使用した辺を戻らないようにして DFS をする。
// パス検出：目的の点に到達したら探索を打ち切って、来たパスを戻ることで復元する。
// 閉路検出：トポロジカルソートして、逆方向に戻る辺があれば閉路が存在する。

// verified with
// https://judge.yosupo.jp/problem/cycle_detection

#include <bits/stdc++.h>
using namespace std;

struct Graph {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    vector<bool> used;
    vector<int> vs, topo;

    Graph(int n) : es(n), n(n), m(0), used(n), topo(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        m++;
    }

    void _dfs(int now) {
        used[now] = true;
        for (auto &e : es[now]) {
            if (!used[e.to]) _dfs(e.to);
        }
        topo[now] = vs.size(), vs.push_back(now);
    }

    void topological_sort() {
        fill(begin(used), end(used), false);
        for (int i = 0; i < n; i++) {
            if (!used[i]) _dfs(i);
        }
    }

    bool detect_path(int now, int t, vector<int> &ret, bool use_id = false) {
        used[now] = true;
        if (now == t) {
            if (!use_id) ret.push_back(now);
            return true;
        }
        for (auto &e : es[now]) {
            if (used[e.to]) continue;
            if (detect_path(e.to, t, ret, use_id)) {
                ret.push_back(use_id ? e.id : now);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t, bool use_id = false) {
        vector<int> ret;
        fill(begin(used), end(used), false);
        detect_path(s, t, ret, use_id);
        reverse(begin(ret), end(ret));
        return ret;
    }

    vector<int> find_cycle(bool use_id = false) {
        topological_sort();
        for (int i = 0; i < n; i++) {
            for (auto &e : es[i]) {
                if (topo[i] <= topo[e.to]) {
                    vector<int> ret = find_path(e.to, i, use_id);
                    ret.push_back(use_id ? e.id : e.to);
                    return ret;
                }
            }
        }
        return {};
    }
};
