
// ラグランジュ補間（多点）
// 計算量 O((n+m)log(n+m))

// 概要
// n-1 次以下の多項式 f(x) について、f(0),f(1),...,f(n-1) の値が与えられたときに、与えられた 1 点 c と自然数 M について f(c),f(c+1),...,f(c+m-1) を求める。
// F[i] = f(i)/Π[j!=i](i-j), G[i] = 1/(c-n+1+i)
// とすると、F と G を畳み込みした後の N-1+i 項目が f(c+i) に相当する。
// 0 <= c+i < N のときは 0 除算が発生するので、場合分けする必要がある。

// verified with
// https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

template <typename T>
vector<T> multipoint_interpolation(const vector<T> &ys, const T &c, const int &m) {
    using NTT_ = Number_Theoretic_Transform<T>;
    int n = ys.size();
    vector<T> ifac(n);
    ifac[n - 1] = 1;
    for (int i = 1; i < n; i++) ifac[n - 1] *= i;
    ifac[n - 1] = T(1) / ifac[n - 1];
    for (int i = n - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i;
    vector<T> f(n);
    for (int i = 0; i < n; i++) {
        if ((n - 1 - i) & 1)
            f[i] = -ys[i] * ifac[i] * ifac[n - 1 - i];
        else
            f[i] = ys[i] * ifac[i] * ifac[n - 1 - i];
    }
    vector<T> p(n + m, 1), ip(n + m);
    for (int i = 1; i < n + m; i++) {
        if (c - n + i == 0)
            p[i] = p[i - 1];
        else
            p[i] = p[i - 1] * (c - n + i);
    }
    ip[n + m - 1] = T(1) / p[n + m - 1];
    for (int i = n + m - 1; i > 0; i--) {
        if (c - n + i == 0)
            ip[i - 1] = ip[i];
        else
            ip[i - 1] = ip[i] * (c - n + i);
    }
    vector<T> g(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) g[i] = p[i] * ip[i + 1];
    f = NTT_::convolve(f, g);
    vector<T> ret(m);
    for (int i = 0; i < m; i++) {
        int x = (c + i).x;
        if (0 <= x && x < n)
            ret[i] = ys[x];
        else
            ret[i] = f[n - 1 + i] * p[n + i] * ip[i];
    }
    return ret;
}
