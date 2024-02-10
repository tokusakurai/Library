#pragma once

// 木の重心分解 (雛形)
// 計算量 O(n)

// 概要
// DFS を用いて、各頂点についてその点を除いたときの残る部分木のサイズの最大値を列挙することで重心を求める。

// verified with
// https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c
// https://judge.yosupo.jp/problem/frequency_table_of_tree_distance

#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Centroid_Decomposition {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    vector<int> si;
    vector<bool> used;

    Centroid_Decomposition(int n) : es(n), n(n), m(0), si(n), used(n, false) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int calc_size(int now, int pre = -1) {
        si[now] = 1;
        for (auto &e : es[now]) {
            if (e.to == pre || used[e.to]) continue;
            si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    // (残りの最大部分木の頂点数、重心)
    pair<int, int> search_centroid(int now, int sz, int pre = -1) {
        pair<int, int> ret = make_pair(INT_MAX, -1);
        int M = 0, S = 1;
        for (auto &e : es[now]) {
            if (e.to == pre || used[e.to]) continue;
            ret = min(ret, search_centroid(e.to, sz, now));
            M = max(M, si[e.to]);
            S += si[e.to];
        }
        M = max(M, sz - S);
        ret = min(ret, make_pair(M, now));
        return ret;
    }

    // 頂点 s を含む連結成分の重心を返す
    int centroid(int s) {
        calc_size(s);
        return search_centroid(s, si[s]).second;
    }

    void decompose(int root = 0) {
        int c = centroid(root);
        used[c] = true;
        for (auto &e : es[c]) {
            if (!used[e.to]) decompose(e.to);
        }
    }
};
