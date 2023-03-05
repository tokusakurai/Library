
// 遅延評価付き Segment Tree
// 計算量 構築：O(n)、区間更新・区間取得・二分探索：O(log(n))
// 空間計算量 O(n)

// 概要
// 遅延配列は、上にあるものほど新しく追加されたものであるようにする。
// また、本配列は自身より下の部分の遅延評価をされたときに常に更新されるようにする。
// 区間更新：まず更新される各ノードより上の部分の遅延評価を解消してから遅延配列を更新し、更新した区間より上の部分の本配列を更新する。
// 区間取得：取得する区間の上の部分の遅延評価を解消する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H&lang=ja
// https://judge.yosupo.jp/problem/range_affine_range_sum
// https://codeforces.com/contest/1404/problem/C
// https://atcoder.jp/contests/abc292/tasks/abc292_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Acted_Monoid>
struct Lazy_Segment_Tree {
    using Monoid = typename Acted_Monoid::Monoid;
    using Operator = typename Acted_Monoid::Operator;
    using M = typename Monoid::V;
    using O = typename Operator::V;
    int n, m, height;
    vector<M> seg;
    vector<O> lazy;

    // f(f(a,b),c) = f(a,f(b,c)), f(e1,a) = f(a,e1) = a
    // h(h(p,q),r) = h(p,h(q,r)), h(e2,p) = h(p,e2) = p
    // g(f(a,b),p) = f(g(a,p),g(b,p))
    // g(g(a,p),q) = g(a,h(p,q))

    Lazy_Segment_Tree(const vector<M> &v) : n(v.size()) {
        m = 1, height = 0;
        while (m < n) m <<= 1, height++;
        seg.assign(2 * m, Monoid::id), lazy.assign(2 * m, Operator::id);
        copy(begin(v), end(v), begin(seg) + m);
        for (int i = m - 1; i > 0; i--) seg[i] = Monoid::merge(seg[2 * i], seg[2 * i + 1]);
    }

    Lazy_Segment_Tree(int n, const M &x) : Lazy_Segment_Tree(vector<M>(n, x)) {}

    inline M reflect(int i) const { return (lazy[i] == Operator::id ? seg[i] : Acted_Monoid::merge(seg[i], lazy[i])); }

    inline void recalc(int i) {
        while (i >>= 1) seg[i] = Monoid::merge(reflect(2 * i), reflect(2 * i + 1));
    }

    inline void eval(int i) {
        if (i < m && lazy[i] != Operator::id) {
            lazy[2 * i] = Operator::merge(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = Operator::merge(lazy[2 * i + 1], lazy[i]);
            seg[i] = reflect(i);
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
        int a = l, b = r;
        while (l < r) {
            if (l & 1) lazy[l] = Operator::merge(lazy[l], x), l++;
            if (r & 1) r--, lazy[r] = Operator::merge(lazy[r], x);
            l >>= 1, r >>= 1;
        }
        recalc(a), recalc(b - 1);
    }

    M query(int l, int r) {
        l = max(l, 0), r = min(r, n);
        if (l >= r) return Monoid::id;
        l += m, r += m;
        thrust(l), thrust(r - 1);
        M L = Monoid::id, R = Monoid::id;
        while (l < r) {
            if (l & 1) L = Monoid::merge(L, reflect(l++));
            if (r & 1) R = Monoid::merge(reflect(--r), R);
            l >>= 1, r >>= 1;
        }
        return Monoid::merge(L, R);
    }

    M operator[](int i) { return query(i, i + 1); }

    template <typename C>
    int find_subtree(int i, const C &check, M &x, int type) {
        while (i < m) {
            eval(i);
            M nxt = type ? Monoid::merge(reflect(2 * i + type), x) : Monoid::merge(x, reflect(2 * i + type));
            if (check(nxt)) {
                i = 2 * i + type;
            } else {
                x = nxt;
                i = 2 * i + (type ^ 1);
            }
        }
        return i - m;
    }

    // check(区間 [l,r] での演算結果) を満たす最小の r (なければ n)
    template <typename C>
    int find_first(int l, const C &check) {
        M L = Monoid::id;
        int a = l + m, b = 2 * m;
        thrust(a);
        while (a < b) {
            if (a & 1) {
                M nxt = Monoid::merge(L, reflect(a));
                if (check(nxt)) return find_subtree(a, check, L, 0);
                L = nxt;
                a++;
            }
            a >>= 1, b >>= 1;
        }
        return n;
    }

    // check(区間 [l,r) での演算結果) を満たす最大の l (なければ -1)
    template <typename C>
    int find_last(int r, const C &check) {
        M R = Monoid::id;
        int a = m, b = r + m;
        thrust(b - 1);
        while (a < b) {
            if ((b & 1) || a == 1) {
                M nxt = Monoid::merge(reflect(--b), R);
                if (check(nxt)) return find_subtree(b, check, R, 1);
                R = nxt;
            }
            a >>= 1, b >>= 1;
        }
        return -1;
    }
};
