#pragma once

// Bostan-Mori のアルゴリズム (d 階の線形漸化式で与えられる数列の第 k 項を求める)
// 計算量 O(d log(d)log(k))

// 概要
// G(x) := a[0]+a[1]x+a[2]x^2+...
// Q(x) := 1-c[1]x-c[2]x^2-...-c[d]x^d
// P(x) := G(x)*Q(x)
// とすると、P(x) は d-1 次以下になっているので、a[n] = [x^k](P(x)/Q(x)) を求める。
// 一般に P,Q の次数をそれぞれ n,m とすると、[x^k](P(x)/Q(x)) を Bostan-Mori のアルゴリズムで計算量 O((n+m)log(n+m)log(k)) で求められる。

// verified with
// https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

template <typename T>
T Bostan_Mori(vector<T> f, vector<T> g, long long k) {
    assert(!g.empty() && g[0] != 0);
    if (f.empty()) return 0;
    using NTT_ = Number_Theoretic_Transform<T>;
    int n = 2;
    while (n < max((int)f.size(), (int)g.size())) n <<= 1;
    f.resize(n, 0), g.resize(n, 0);
    vector<T> h(n, 0);
    h[1] = 1;
    NTT_::ntt(h);
    while (k > 0) {
        vector<T> fe(n, 0), fo(n, 0), ge(n, 0), go(n, 0);
        for (int i = 0; i < n; i += 2) {
            fe[i >> 1] = f[i];
            ge[i >> 1] = g[i];
        }
        for (int i = 1; i < n; i += 2) {
            fo[i >> 1] = f[i];
            go[i >> 1] = g[i];
        }
        NTT_::ntt(fe), NTT_::ntt(fo), NTT_::ntt(ge), NTT_::ntt(go);
        if (k & 1) {
            for (int i = 0; i < n; i++) {
                f[i] = fo[i] * ge[i] - fe[i] * go[i];
                g[i] = ge[i] * ge[i] - go[i] * go[i] * h[i];
            }
        } else {
            for (int i = 0; i < n; i++) {
                f[i] = fe[i] * ge[i] - fo[i] * go[i] * h[i];
                g[i] = ge[i] * ge[i] - go[i] * go[i] * h[i];
            }
        }
        NTT_::intt(f), NTT_::intt(g);
        k >>= 1;
    }
    return f[0] / g[0];
}

// d 項間漸化式 a_n = ∑[1<=i<=d]c_i * a_{n-i} を満たす数列
// a_0,...,a_{d-1} を与えたときに、a_k を計算する
template <typename T>
T linear_recurrence(const vector<T> &a, const vector<T> &c, long long k) {
    int d = a.size();
    assert((int)c.size() == d + 1);
    using NTT_ = Number_Theoretic_Transform<T>;
    vector<T> g(d + 1, 0);
    g[0] = 1;
    for (int i = 1; i <= d; i++) g[i] = -c[i];
    vector<T> f = NTT_::convolve(a, g);
    f.resize(d, 0);
    return Bostan_Mori(f, g, k);
}
