#pragma once

// 双対 Segment Tree
// 計算量 構築：O(n)、区間更新・1 点取得：O(log(n))
// 空間計算量 O(n)

// 概要
// 遅延配列は、上にあるものほど新しく追加されたものであるようにする。
// 区間更新：まず更新される各ノードより上の部分の遅延評価を解消してから遅延配列を更新する。
// 1 点取得：取得する点より上の部分の遅延評価を解消する。

// verified with
// https://judge.yosupo.jp/problem/range_affine_point_get
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename Operator>
struct Dual_Segment_Tree {
    using O = typename Operator::V;
    int n, m, height;
    vector<O> lazy;

    Dual_Segment_Tree(int n) : n(n) {
        m = 1, height = 0;
        while (m < n) m <<= 1, height++;
        lazy.assign(2 * m, Operator::id);
    }

    inline void eval(int i) {
        if (i < m) {
            lazy[2 * i] = Operator::merge(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = Operator::merge(lazy[2 * i + 1], lazy[i]);
            lazy[i] = Operator::id;
        }
    }

    inline void thrust(int i) {
        for (int j = height; j > 0; j--) eval(i >> j);
    }

    void update(int l, int r, const O &x) {
        l = max(l, 0), r = min(r, n);
        if (l >= r) return;
        l += m, r += m;
        thrust(l), thrust(r - 1);
        while (l < r) {
            if (l & 1) lazy[l] = Operator::merge(lazy[l], x), l++;
            if (r & 1) r--, lazy[r] = Operator::merge(lazy[r], x);
            l >>= 1, r >>= 1;
        }
    }

    O get(int i) {
        thrust(i + m);
        return lazy[i + m];
    }

    O operator[](int i) { return get(i); }
};
