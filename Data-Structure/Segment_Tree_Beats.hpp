
// Segment Tree Beats
// 計算量：場合によるが、例えば range chmin, chmax, add, range sum クエリの場合はクエリ O(log(n)^2)
// 空間計算量 O(n)

// 概要
// 遅延評価付き Segment Tree において、作用素の作用に失敗する場合がある場合も扱える。 (この場合は作用素クエリを子に回す)
// 計算量評価については載せるデータに依存することが多い。

// verified with
// https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
// https://atcoder.jp/contests/abc256/tasks/abc256_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Acted_Monoid>
struct Segment_Tree_Beats {
    using Monoid = typename Acted_Monoid::Monoid;
    using Operator = typename Acted_Monoid::Operator;
    using M = typename Monoid::V;
    using O = typename Operator::V;
    int n, si, height;
    vector<M> seg;
    vector<O> lazy;

    Segment_Tree_Beats(const vector<M> &v) : n(v.size()) {
        si = 1, height = 0;
        while (si < n) si <<= 1, height++;
        seg.assign(2 * si, Monoid::id), lazy.assign(2 * si, Operator::id);
        copy(begin(v), end(v), seg.begin() + si);
        for (int i = si - 1; i > 0; i--) seg[i] = Monoid::merge(seg[2 * i], seg[2 * i + 1]);
    }

    Segment_Tree_Beats(int n, const M &x) : Segment_Tree_Beats(vector<M>(n, x)) {}

    void update(int i) { seg[i] = Monoid::merge(seg[2 * i], seg[2 * i + 1]); }

    void push(int i) {
        seg[i] = Acted_Monoid::merge(seg[i], lazy[i]); // lazy[i] の作用が失敗したら seg[i].fail を true にする
        if (i < si) {
            lazy[2 * i] = Operator::merge(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = Operator::merge(lazy[2 * i + 1], lazy[i]);
            if (seg[i].fail) {
                push(2 * i), push(2 * i + 1);
                update(i);
            }
        }
        lazy[i] = Operator::id;
    }

    void update(int L, int R, const O &x, int i, int l, int r) {
        if (L >= r || l >= R) return push(i);
        if (L <= l && r <= R) {
            lazy[i] = Operator::merge(lazy[i], x);
            return push(i);
        }
        push(i);
        int m = (l + r) / 2;
        update(L, R, x, 2 * i, l, m), update(L, R, x, 2 * i + 1, m, r);
        update(i);
    }

    void update(int l, int r, const O &x) { return update(l, r, x, 1, 0, si); }

    M query(int L, int R, int i, int l, int r) {
        if (L >= r || l >= R) return Monoid::id;
        push(i);
        if (L <= l && r <= R) return seg[i];
        int m = (l + r) / 2;
        return Monoid::merge(query(L, R, 2 * i, l, m), query(L, R, 2 * i + 1, m, r));
    }

    M query(int l, int r) { return query(l, r, 1, 0, si); }

    M operator[](int i) { return query(i, i + 1); }
};
