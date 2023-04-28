
// Manhattan 最小全域木
// 計算量 O(n log(n))

// 概要
// 辺 {i,j} の重みが |x_i-x_j|+|y_i-y_j| である完全グラフの MST
// 各頂点 x_i,y_i を中心として平面を 8 領域に分けたときの右側 4 領域について i に最も近い点を求め、i との間に辺を張る。
// こうして得られたグラフ (高々 4n 辺) の MST を計算すれば元のグラフの MST が得られる。

// verified with
// https://judge.yosupo.jp/problem/manhattanmst

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

// (MST の重み、MST に含まれる辺)
template <typename T>
pair<T, vector<pair<int, int>>> Manhattan_mst(vector<T> xs, vector<T> ys) {
    assert(xs.size() == ys.size());
    int n = xs.size();
    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    vector<pair<int, int>> es;
    for (int s = 0; s < 2; s++) {
        auto comp = [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; };
        sort(begin(ord), end(ord), comp);
        for (int t = 0; t < 2; t++) {
            map<T, int> mp;
            for (auto &i : ord) {
                for (auto it = mp.lower_bound(-ys[i]); it != end(mp); it = mp.erase(it)) {
                    int j = it->second;
                    if (xs[i] - ys[i] < xs[j] - ys[j]) break;
                    es.emplace_back(i, j);
                }
                mp[-ys[i]] = i;
            }
            if (t == 0) swap(xs, ys);
        }
        for (auto &e : xs) e = -e;
    }

    auto dist = [&](int i, int j) { return abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]); };

    auto comp = [&](const pair<int, int> &p, const pair<int, int> &q) {
        auto &[i, j] = p;
        auto &[k, l] = q;
        return dist(i, j) < dist(k, l);
    };

    sort(begin(es), end(es), comp);
    Union_Find_Tree uf(n);
    T ret = 0;
    vector<pair<int, int>> mst;
    for (auto &[i, j] : es) {
        if (uf.unite(i, j)) {
            ret += dist(i, j);
            mst.emplace_back(i, j);
        }
    }
    return make_pair(ret, mst);
};
