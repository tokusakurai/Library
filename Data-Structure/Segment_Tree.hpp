
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

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid>
struct Segment_Tree {
    using F = function<Monoid(Monoid, Monoid)>;
    int n;
    vector<Monoid> seg;
    const F f;
    const Monoid e1;

    // f(f(a,b),c) = f(a,f(b,c)), f(e1,a) = f(a,e1) = a

    Segment_Tree(const vector<Monoid> &v, const F &f, const Monoid &e1) : f(f), e1(e1) {
        int m = v.size();
        n = 1;
        while (n < m) n <<= 1;
        seg.assign(2 * n, e1);
        copy(begin(v), end(v), seg.begin() + n);
        for (int i = n - 1; i > 0; i--) seg[i] = f(seg[2 * i], seg[2 * i + 1]);
    }

    Segment_Tree(int m, const Monoid &x, const F &f, const Monoid &e1) : Segment_Tree(vector<Monoid>(m, x), f, e1) {}

    void change(int i, const Monoid &x, bool update = true) {
        if (update) {
            seg[i + n] = x;
        } else {
            seg[i + n] = f(seg[i + n], x);
        }
        i += n;
        while (i >>= 1) seg[i] = f(seg[2 * i], seg[2 * i + 1]);
    }

    Monoid query(int l, int r) const {
        l = max(l, 0), r = min(r, n);
        Monoid L = e1, R = e1;
        l += n, r += n;
        while (l < r) {
            if (l & 1) L = f(L, seg[l++]);
            if (r & 1) R = f(seg[--r], R);
            l >>= 1, r >>= 1;
        }
        return f(L, R);
    }

    Monoid operator[](int i) const { return seg[n + i]; }

    template <typename C>
    int find_subtree(int i, const C &check, const Monoid &x, Monoid &M, int type) const {
        while (i < n) {
            Monoid nxt = type ? f(seg[2 * i + type], M) : f(M, seg[2 * i + type]);
            if (check(nxt, x)) {
                i = 2 * i + type;
            } else {
                M = nxt;
                i = 2 * i + (type ^ 1);
            }
        }
        return i - n;
    }

    // check((区間 [l,r] での演算結果), x) を満たす最小の r (存在しなければ n 以上の値)
    template <typename C>
    int find_first(int l, const C &check, const Monoid &x) const {
        Monoid L = e1;
        int a = l + n, b = n + n;
        while (a < b) {
            if (a & 1) {
                Monoid nxt = f(L, seg[a]);
                if (check(nxt, x)) return find_subtree(a, check, x, L, 0);
                L = nxt, a++;
            }
            a >>= 1, b >>= 1;
        }
        return n;
    }

    // check((区間 [l,r) での演算結果), x) を満たす最大の l (存在しなければ -1)
    template <typename C>
    int find_last(int r, const C &check, const Monoid &x) const {
        Monoid R = e1;
        int a = n, b = r + n;
        while (a < b) {
            if ((b & 1) || a == 1) {
                Monoid nxt = f(seg[--b], R);
                if (check(nxt, x)) return find_subtree(b, check, x, R, 1);
                R = nxt;
            }
            a >>= 1, b >>= 1;
        }
        return -1;
    }
};
