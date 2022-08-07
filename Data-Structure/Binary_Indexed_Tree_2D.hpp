
// 2 次元 Binary Indexed Tree
// 計算量 構築：O(n log(n)^2)、1 点更新・矩形取得：O(log(n)^2)
// 空間計算量 O(n log(n))

// 概要
// Binary Indexed Tree の各ノードに Binary Indexed Tree を乗せている。
// あらかじめ座標圧縮しておき、必要な部分だけ残すことでメモリを O(n log(n)) に削減できる。
// y 軸方向に計算したあと x 軸方向について計算するので、可換モノイドであれば十分。

// verified with
// https://judge.yosupo.jp/problem/rectangle_sum
// https://judge.yosupo.jp/problem/point_add_rectangle_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Binary_Indexed_Tree.hpp"

// S は座標の型
template <typename T, typename S>
struct Binary_Indexed_Tree_2D {
    int n;
    vector<S> xs;
    vector<pair<S, S>> all_points;
    vector<vector<S>> ys;
    vector<Binary_Indexed_Tree<T>> bits;

    Binary_Indexed_Tree_2D() {}

    // 値を変更する箇所を先に全て挿入しておく
    void insert(const S &x, const S &y) {
        xs.push_back(x);
        all_points.emplace_back(x, y);
    }

    void build() {
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
        n = xs.size();
        ys.resize(n + 1);
        for (auto &p : all_points) {
            auto [x, y] = p;
            int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
            for (i++; i <= n; i += (i & -i)) ys[i].push_back(y);
        }
        for (int i = 0; i <= n; i++) {
            sort(begin(ys[i]), end(ys[i]));
            ys[i].erase(unique(begin(ys[i]), end(ys[i])), end(ys[i]));
            bits.emplace_back((int)ys[i].size(), 0);
        }
    }

    void add(const S &x, const S &y, const T &a) {
        int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
        for (i++; i <= n; i += (i & -i)) {
            int j = lower_bound(begin(ys[i]), end(ys[i]), y) - begin(ys[i]);
            bits[i].add(j, a);
        }
    }

    T sum(const S &x, const S &ly, const S &ry) {
        int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
        T ret = 0;
        for (; i > 0; i -= (i & -i)) {
            int lj = lower_bound(begin(ys[i]), end(ys[i]), ly) - begin(ys[i]);
            int rj = lower_bound(begin(ys[i]), end(ys[i]), ry) - begin(ys[i]);
            ret += bits[i].query(lj, rj);
        }
        return ret;
    }

    T query(const S &lx, const S &rx, const S &ly, const S &ry) { return sum(rx, ly, ry) - sum(lx, ly, ry); }
};
