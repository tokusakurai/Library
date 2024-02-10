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
