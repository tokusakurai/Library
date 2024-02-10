#pragma once

// 多点評価 (評価点が幾何級数の場合)
// 計算量 O((m+n) log(m+n))

// 概要
// f(x) = ∑[0<=i<n]f_i*x^i に対して、f(a), f(ar),..., f(ar^{m-1}) を計算する。
// f(ar^j) = ∑[0<=i<n]f_i*a^i*r^{ij} であり、ij = (i+j)(i+j-1)/2 - i(i+1)/2 - j(j+1)/2 であるため、
// f(ar^j) * r^{j(j+1)/2} = ∑[0<=i<n]f_i*a^i*r^{i(i+1)/2} * r^{(i+j)(i+j+1)/2}
// であり、この右辺を j=0,...,m-1 に対して計算するのは畳み込みで実現できる。

// verified with
// https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence

#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> multipoint_evaluation_geometric_series(vector<T> f, T a, T r, int m) {
    if (m == 0) return {};
    int n = f.size();
    T c = 1;
    for (int i = 0; i < n; i++) {
        f[i] *= c;
        c *= a;
    }
    if (r == T(0)) {
        vector<T> ret(m, 0);
        for (int i = 0; i < n; i++) ret[0] += f[i];
        for (int j = 1; j < m; j++) ret[j] = f[0];
        return ret;
    }
    int s = 1;
    while (s < n + m - 1) s <<= 1;
    T ir = r.inverse();
    vector<T> pw(n + m - 1, 1);
    for (int i = 1; i < n + m - 1; i++) pw[i] = pw[i - 1] * r;
    for (int i = 1; i < n + m - 1; i++) pw[i] *= pw[i - 1];
    vector<T> ipw(max(n, m), 1);
    for (int i = 1; i < max(n, m); i++) ipw[i] = ipw[i - 1] * ir;
    for (int i = 1; i < max(n, m); i++) ipw[i] *= ipw[i - 1];
    vector<T> g1(s, 0), g2(s, 0);
    for (int i = 0; i < n; i++) g1[n - 1 - i] = f[i] * ipw[i];
    for (int k = 0; k < n + m - 1; k++) g2[k] = pw[k];
    NTT::ntt(g1), NTT::ntt(g2);
    for (int i = 0; i < s; i++) g1[i] *= g2[i];
    NTT::intt(g1);
    vector<T> ret(m, 0);
    for (int j = 0; j < m; j++) ret[j] = g1[n - 1 + j] * ipw[j];
    return ret;
}
