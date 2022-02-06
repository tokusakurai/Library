
// 双対 Segment Tree
// 計算量 構築：O(n)、区間更新・1 点取得：O(log(n))
// 空間計算量 O(n)

// 概要
// 遅延配列は、上にあるものほど新しく追加されたものであるようにする。
// 区間更新：まず更新される各ノードより上の部分の遅延評価を解消してから遅延配列を更新する。
// 1 点取得：取得する点より上の部分の遅延評価を解消する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Operator_Monoid>
struct Dual_Segment_Tree {
    using H = function<Operator_Monoid(Operator_Monoid, Operator_Monoid)>;
    int n, height;
    vector<Operator_Monoid> lazy;
    const H h;
    const Operator_Monoid e2;

    // h(h(p,q),r) = h(p,h(q,r)), h(e2,p) = h(p,e2) = p

    Dual_Segment_Tree(int m, const H &h, const Operator_Monoid &e2) : h(h), e2(e2) {
        n = 1, height = 0;
        while (n < m) n <<= 1, height++;
        lazy.assign(2 * n, e2);
    }

    inline void eval(int i) {
        if (i < n && lazy[i] != e2) {
            lazy[2 * i] = h(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = h(lazy[2 * i + 1], lazy[i]);
            lazy[i] = e2;
        }
    }

    inline void thrust(int i) {
        for (int j = height; j > 0; j--) eval(i >> j);
    }

    void apply(int l, int r, const Operator_Monoid &x) {
        l = max(l, 0), r = min(r, n);
        if (l >= r) return;
        l += n, r += n;
        thrust(l), thrust(r - 1);
        while (l < r) {
            if (l & 1) lazy[l] = h(lazy[l], x), l++;
            if (r & 1) r--, lazy[r] = h(lazy[r], x);
            l >>= 1, r >>= 1;
        }
    }

    Operator_Monoid get(int i) {
        thrust(i + n);
        return lazy[i + n];
    }

    Operator_Monoid operator[](int i) { return get(i); }
};
