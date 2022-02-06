
// 重みなし木の基本的な DFS
// 計算量 根からの距離・部分木のサイズ・直径・パス検出：O(n)

// 直径：最短距離が最大になるような2点間の単純パス

// 概要
// 根からの距離・部分木のサイズ：木上で DP を行っているとみることができる。
// 直径：適当に頂点を決めて、その頂点から最も遠い点を s とし、s から最も遠い点を t とすると、パス s-t は直径となる。

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

    vector<int> d, si;

    Graph(int n) : es(n), n(n), m(0), d(n), si(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void calc_depth(int now, int pre = -1) {
        if (pre == -1) d[now] = 0;
        for (auto &e : es[now]) {
            if (e.to != pre) d[e.to] = d[now] + 1, calc_depth(e.to, now);
        }
    }

    int calc_size(int now, int pre = -1) {
        si[now] = 1;
        for (auto &e : es[now]) {
            if (e != pre) si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    int farthest_point(int s) {
        calc_depth(s);
        int max_d = -1, t = -1;
        for (int i = 0; i < n; i++) {
            if (d[i] > max_d) max_d = d[i], t = i;
        }
        return t;
    }

    pair<int, pair<int, int>> diameter() {
        int a = farthest_point(0), b = farthest_point(a);
        return make_pair(d[b], make_pair(a, b));
    }

    vector<int> ret_path;

    bool detect_path(int now, int t, bool use_id = false, int pre = -1) {
        if (now == t) {
            if (!use_id) ret_path.push_back(now);
            return true;
        }
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            if (detect_path(e.to, t, use_id, now)) {
                ret_path.push_back(use_id ? e.id : now);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t, bool use_id = false) {
        ret_path.clear();
        detect_path(s, t, use_id);
        reverse(begin(ret_path), end(ret_path));
        return ret_path;
    }
};
