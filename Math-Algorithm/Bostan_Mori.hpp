
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

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

// [x^k](P(x)/Q(x))
template <typename T>
T Bostan_Mori(vector<T> P, vector<T> Q, long long k) {
    using NTT_ = Number_Theoretic_Transform<T>;
    int n = max((int)P.size(), (int)Q.size());
    P.resize(n, 0), Q.resize(n, 0);
    assert(n > 0 && Q[0] != 0);
    int t = 1;
    while (t < 2 * n - 1) t <<= 1;
    for (; k > 0; k >>= 1) {
        vector<T> R = Q;
        for (int i = 1; i < n; i += 2) R[i] = -R[i];
        P.resize(t, 0), NTT_::ntt(P);
        Q.resize(t, 0), NTT_::ntt(Q);
        R.resize(t, 0), NTT_::ntt(R);
        vector<T> A(t), B(t);
        for (int i = 0; i < t; i++) {
            A[i] = P[i] * R[i];
            B[i] = Q[i] * R[i];
        }
        NTT_::intt(A), NTT_::intt(B);
        Q.resize(n);
        for (int i = 0; i < n; i++) Q[i] = B[2 * i];
        P.resize(n);
        if (k & 1) {
            for (int i = 0; i < n - 1; i++) P[i] = A[2 * i + 1];
            P[n - 1] = 0;
        } else {
            for (int i = 0; i < n; i++) P[i] = A[2 * i];
        }
    }
    return P[0] / Q[0];
}

// d 項間線形漸化式 a[n] = c[1]*a[n-1]+c[2]*a[n-2]+...+c[d]*a[n-d] の第 k 項 (0-indexed)
template <typename T>
T linear_recurrence(const vector<T> &a, const vector<T> &c, long long k) {
    using NTT_ = Number_Theoretic_Transform<T>;
    int d = a.size();
    vector<T> Q(d + 1, 0);
    Q[0] = 1;
    for (int i = 1; i <= d; i++) Q[i] = -c[i];
    vector<T> P = NTT_::convolve(a, Q);
    P.resize(d);
    return Bostan_Mori(P, Q, k);
}
