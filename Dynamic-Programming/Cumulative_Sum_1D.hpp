
// 1 次元累積和
// 計算量 構築：O(n)、imos 法を用いた加算・区間和クエリ：O(1)

// 概要
// 各要素について自分より前の要素の和を累積和 dp で求める。

// verified with
// https://judge.yosupo.jp/problem/static_range_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Cumulative_Sum_1D {
    vector<T> v;
    const int n;

    Cumulative_Sum_1D(const vector<T> &v) : v(v), n((int)v.size()) {}

    Cumulative_Sum_1D(int n) : v(n, 0), n(n) {}

    void build() { // 累積和を構築
        for (int i = 1; i < n; i++) v[i] += v[i - 1];
    }

    void add(int l, int r, T x) { // 区間 [l,r) に imos 法で加算
        l = max(l, 0), r = min(r, n);
        if (r <= l) return;
        v[l] += x;
        if (r < n) v[r] -= x;
    }

    T fold(int a) { return (a <= 0 ? 0 : v[min(n, a) - 1]); }

    T sum(int l, int r) { // 区間 [l,r) の総和
        l = max(l, 0), r = min(r, n);
        if (r <= l) return 0;
        return fold(r) - fold(l);
    }
};
