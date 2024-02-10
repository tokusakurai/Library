#pragma once

// 重み付き木の基本的な DFS
// 計算量 根からの距離・部分木のサイズ・直径・パス検出：O(n)

// 直径：最短距離が最大になるような 2 点間の単純パス

// 概要
// 直径：適当に頂点を決めて、その頂点から最も遠い点を s とし、s から最も遠い点を t とすると、パス s-t は直径となる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=ja
// https://judge.yosupo.jp/problem/tree_diameter
// https://atcoder.jp/contests/abc270/tasks/abc270_c
// https://codeforces.com/contest/455/problem/C

#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Weighted_Tree {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T INF_T;
    const int n;
    int m;

    vector<T> d;
    vector<int> si;

    Weighted_Tree(int n) : es(n), INF_T(numeric_limits<T>::max() / 2), n(n), m(0), d(n), si(n) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    // 始点から最も遠い点を出力
    int calc_depth(int now, int pre = -1) {
        if (pre == -1) d[now] = 0;
        int ret = now;
        for (auto &e : es[now]) {
            if (e.to != pre) {
                d[e.to] = d[now] + e.cost;
                int t = calc_depth(e.to, now);
                if (d[t] > d[ret]) ret = t;
            }
        }
        return ret;
    }

    int calc_size(int now, int pre = -1) {
        si[now] = 1;
        for (auto &e : es[now]) {
            if (e != pre) si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    pair<T, pair<int, int>> diameter(int root) {
        int a = calc_depth(root), b = calc_depth(a);
        return make_pair(d[b], make_pair(a, b));
    }

    bool detect_path(int now, int t, vector<int> &ret, bool use_id = false, int pre = -1) {
        if (now == t) {
            if (!use_id) ret.push_back(now);
            return true;
        }
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            if (detect_path(e.to, t, ret, use_id, now)) {
                ret.push_back(use_id ? e.id : now);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t, bool use_id = false) {
        vector<int> ret;
        detect_path(s, t, ret, use_id);
        reverse(begin(ret), end(ret));
        return ret;
    }
};
