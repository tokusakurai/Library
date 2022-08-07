
// Segment Tree Beats
// 計算量：場合によるが、例えば range chmin, chmax, add, range sum クエリの場合はクエリ O(log(n)^2)
// 空間計算量 O(n)

// 概要
// 遅延評価付き Segment Tree において、作用素の作用に失敗する場合がある場合も扱える。（この場合は作用素クエリを子に回す）
// 計算量評価については載せるデータに依存することが多い。

// verified with
// https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
// https://atcoder.jp/contests/abc256/tasks/abc256_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid, typename Operator>
struct Segment_Tree_Beats {
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid, Operator)>;
    using H = function<Operator(Operator, Operator)>;
    int n, height;
    vector<Monoid> seg;
    vector<Operator> lazy;
    const F f;
    const G g;
    const H h;
    const Monoid e1;
    const Operator e2;

    Segment_Tree_Beats(const vector<Monoid> &v, const F &f, const G &g, const H &h, const Monoid &e1, const Operator &e2) : f(f), g(g), h(h), e1(e1), e2(e2) {
        int m = v.size();
        n = 1, height = 0;
        while (n < m) n <<= 1, height++;
        seg.assign(2 * n, e1), lazy.assign(2 * n, e2);
        copy(begin(v), end(v), seg.begin() + n);
        for (int i = n - 1; i > 0; i--) seg[i] = f(seg[2 * i], seg[2 * i + 1]);
    }

    Segment_Tree_Beats(int m, const Monoid &x, const F &f, const G &g, const H &h, const Monoid &e1, const Operator &e2) : Segment_Tree_Beats(vector<Monoid>(m, x), f, g, h, e1, e2) {}

    void update(int i) { seg[i] = f(seg[2 * i], seg[2 * i + 1]); }

    void push(int i) {
        seg[i] = g(seg[i], lazy[i]); // lazy[i] の作用が失敗したら seg[i].fail を true にする
        if (i < n) {
            lazy[2 * i] = h(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = h(lazy[2 * i + 1], lazy[i]);
            if (seg[i].fail) {
                push(2 * i), push(2 * i + 1);
                update(i);
            }
        }
        lazy[i] = e2;
    }

    void apply(int L, int R, const Operator &x, int i, int l, int r) {
        if (L >= r || l >= R) return push(i);
        if (L <= l && r <= R) {
            lazy[i] = h(lazy[i], x);
            return push(i);
        }
        push(i);
        int m = (l + r) / 2;
        apply(L, R, x, 2 * i, l, m), apply(L, R, x, 2 * i + 1, m, r);
        update(i);
    }

    void apply(int l, int r, const Operator &x) { return apply(l, r, x, 1, 0, n); }

    Monoid query(int L, int R, int i, int l, int r) {
        if (L >= r || l >= R) return e1;
        push(i);
        if (L <= l && r <= R) return seg[i];
        int m = (l + r) / 2;
        return f(query(L, R, 2 * i, l, m), query(L, R, 2 * i + 1, m, r));
    }

    Monoid query(int l, int r) { return query(l, r, 1, 0, n); }

    Monoid operator[](int i) { return query(i, i + 1); }
};
