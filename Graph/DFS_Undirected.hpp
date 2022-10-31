
// 無向グラフでの基本的な DFS
// 計算量 パス検出・閉路検出：O(n+m)

// 概要
// 直前に使用した辺を戻らないようにして DFS をする。
// パス検出：目的の点に到達したら探索を打ち切って、来たパスを戻ることで復元する。
// 閉路検出：同じ点に2回到達したら探索を打ち切って、その頂点に来るまで来たパスを戻ることで復元する。

// verified with
// https://judge.yosupo.jp/problem/cycle_detection_undirected

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Graph {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    vector<int> used;

    Graph(int n) : es(n), n(n), m(0), used(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
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

    // 点素な s-t パスを 1 つ検出
    vector<int> find_path(int s, int t, bool use_id = false) {
        vector<int> ret;
        fill(begin(used), end(used), 0);
        detect_path(s, t, ret, use_id);
        reverse(begin(ret), end(ret));
        return ret;
    }

    int detect_cycle(int now, vector<int> &ret, int pre = -1, bool use_id = false) {
        if (used[now]++) return 1;
        for (auto &e : es[now]) {
            if (e.id == pre) continue;
            int k = detect_cycle(e.to, ret, e.id, use_id);
            if (k == 2) return 2;
            if (k == 1) {
                ret.push_back(use_id ? e.id : now);
                return used[now];
            }
        }
        return 0;
    }

    // 辺素な閉路を 1 つ検出
    vector<int> find_cycle(bool use_id = false) {
        vector<int> ret;
        fill(begin(used), end(used), 0);
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            detect_cycle(i, ret, -1, use_id);
            if (!ret.empty()) {
                reverse(begin(ret), end(ret));
                return ret;
            }
        }
        return {};
    }
};
