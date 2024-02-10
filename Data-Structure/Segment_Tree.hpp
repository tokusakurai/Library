#pragma once

// Segment Tree
// 計算量 構築：O(n)、1 点更新・区間取得・二分探索：O(log(n))
// 空間計算量 O(n)

// 概要
// ノードを区間に対応させることで、任意の区間が O(log(n)) 個のノードが表す区間の disjoint な和集合として表現される。
// 各点を被覆するノードは O(log(n)) 個。
// 1 点更新：その点を含むノードの値を全て更新する。
// 区間取得：区間をちょうど被覆するノードたちの値を用いて演算を行う。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
// https://judge.yosupo.jp/problem/point_add_range_sum
// https://judge.yosupo.jp/problem/point_set_range_composite
// https://atcoder.jp/contests/practice2/tasks/practice2_j
// https://codeforces.com/contest/1407/problem/D

#include <bits/stdc++.h>
using namespace std;

template <typename Monoid>
struct Segment_Tree {
    using M = typename Monoid::V;
    int n, m;
    vector<M> seg;

    // f(f(a,b),c) = f(a,f(b,c)), f(e1,a) = f(a,e1) = a

    Segment_Tree(const vector<M> &v) : n(v.size()) {
        m = 1;
        while (m < n) m <<= 1;
        seg.assign(2 * m, Monoid::id);
        copy(begin(v), end(v), begin(seg) + m);
        build();
    }

    Segment_Tree(int n, M x = Monoid::id) : Segment_Tree(vector<M>(n, x)) {}

    void set(int i, const M &x) { seg[m + i] = x; }

    void build() {
        for (int i = m - 1; i > 0; i--) seg[i] = Monoid::merge(seg[2 * i], seg[2 * i + 1]);
    }

    void update(int i, const M &x, bool apply = false) {
        seg[i + m] = apply ? Monoid::merge(seg[i + m], x) : x;
        i += m;
        while (i >>= 1) seg[i] = Monoid::merge(seg[2 * i], seg[2 * i + 1]);
    }

    M query(int l, int r) const {
        l = max(l, 0), r = min(r, n);
        M L = Monoid::id, R = Monoid::id;
        l += m, r += m;
        while (l < r) {
            if (l & 1) L = Monoid::merge(L, seg[l++]);
            if (r & 1) R = Monoid::merge(seg[--r], R);
            l >>= 1, r >>= 1;
        }
        return Monoid::merge(L, R);
    }

    M operator[](int i) const { return seg[m + i]; }

    template <typename C>
    int find_subtree(int i, const C &check, M &x, int type) const {
        while (i < m) {
            M nxt = type ? Monoid::merge(seg[2 * i + type], x) : Monoid::merge(x, seg[2 * i + type]);
            if (check(nxt)) {
                i = 2 * i + type;
            } else {
                x = nxt;
                i = 2 * i + (type ^ 1);
            }
        }
        return i - m;
    }

    // check(区間 [l,r] での演算結果) を満たす最小の r (存在しなければ n)
    template <typename C>
    int find_first(int l, const C &check) const {
        M L = Monoid::id;
        int a = l + m, b = 2 * m;
        while (a < b) {
            if (a & 1) {
                M nxt = Monoid::merge(L, seg[a]);
                if (check(nxt)) return find_subtree(a, check, L, 0);
                L = nxt;
                a++;
            }
            a >>= 1, b >>= 1;
        }
        return n;
    }

    // check((区間 [l,r) での演算結果)) を満たす最大の l (存在しなければ -1)
    template <typename C>
    int find_last(int r, const C &check) const {
        M R = Monoid::id;
        int a = m, b = r + m;
        while (a < b) {
            if ((b & 1) || a == 1) {
                M nxt = Monoid::merge(seg[--b], R);
                if (check(nxt)) return find_subtree(b, check, R, 1);
                R = nxt;
            }
            a >>= 1, b >>= 1;
        }
        return -1;
    }
};
