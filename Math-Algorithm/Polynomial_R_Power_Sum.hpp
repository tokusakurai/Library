
// 多項式とべき乗の総和
// 計算量 O(k+log(n))

// 概要
// Σ[0<=i<n] i^k r^i、Σ[0<=i<∞] i^k r^i を計算する。(後者は -1 < r < 1)
// i^k は C(i+k,k),C(i+k-1,k-1),...,C(i,0) の (i によらない) 定数線形結合として表される。
// 従って、a_i = i^k r^i の母関数 a(x) は、k 次以下の多項式 f を用いて a(x) = f(x)/(1-rx)^{k+1} と表される。
// 求める答えは Σ[0<=i<n] a_i = [x^{n-1}] a(x)/(1-x) = [x^{n-1}] f(x)/(1-x)(1-rx)^{k+1} である。
// 上式最右辺を部分分数分解すると、定数 c と k 次以下の多項式 g を用いて f(x)/(1-x)(1-rx)^{k+1} = c/(1-x) + g(x)/(1-rx)^{k+1} と書ける。
// つまり、ある k 次以下の多項式 p が存在して、Σ[0<=i<=j] a_i = p(j) r^j + c の形で書けるため、p(n-1) をラグランジュ補間で計算すればよい。

// verified with
// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial
// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Single_Point_Interpolation.hpp"

// Σ[0<=i<n] f(i) r^i : f は k 次多項式で f(0),..,f(k) を与える
// comb を k+1 まで初期化
template <typename T>
T polynomial_r_power_sum(const vector<T> &f, T r, long long n) {
    using comb_ = Combination<T>;
    assert(!f.empty());
    if (n == 0) return 0;
    if (r == 0) return f[0];
    int k = (int)f.size() - 1;
    if (r == 1) {
        vector<T> g(k + 2, 0);
        for (int i = 1; i <= k + 1; i++) g[i] = g[i - 1] + f[i - 1];
        return single_point_interpolation(g, T(n));
    }
    vector<T> g(k + 1, 0);
    T pw = 1;
    for (int i = 0; i <= k; i++) {
        g[i] = f[i] * pw;
        pw *= r;
    }
    for (int i = 1; i <= k; i++) g[i] += g[i - 1];
    T c = 0, pw2 = 1;
    for (int i = 0; i <= k; i++) {
        c += comb_::C(k + 1, i) * g[k - i] * pw2;
        pw2 *= -r;
    }
    c /= (-r + 1).pow(k + 1);
    T ir = r.inverse(), pw3 = 1;
    for (int i = 0; i <= k; i++) {
        g[i] = (g[i] - c) * pw3;
        pw3 *= ir;
    }
    return single_point_interpolation(g, T(n - 1)) * r.pow(n - 1) + c;
}

// Σ[0<=i<n] i^k r^i
// comb を k+1 まで初期化
template <typename T>
T polynomial_r_power_sum(int k, T r, long long n) {
    vector<int> p(k + 1, -1);
    vector<T> f(k + 1, 1);
    if (k > 0) f[0] = 0;
    for (int i = 2; i <= k; i++) {
        if (p[i] == -1) {
            f[i] = T(i).pow(k);
            for (int j = i + i; j <= k; j += i) p[j] = i;
        } else {
            f[i] = f[p[i]] * f[i / p[i]];
        }
    }
    return polynomial_r_power_sum(f, r, n);
}

// Σ[0<=i<∞] f(i) r^i : f は k 次多項式で f(0),..,f(k) を与える
// comb を k+1 まで初期化
template <typename T>
T polynomial_r_power_sum_infinite(const vector<T> &f, T r) {
    using comb_ = Combination<T>;
    assert(!f.empty());
    assert(r != 1);
    int k = (int)f.size() - 1;
    vector<T> g(k + 1, 0);
    T pw = 1;
    for (int i = 0; i <= k; i++) {
        g[i] = f[i] * pw;
        pw *= r;
    }
    for (int i = 1; i <= k; i++) g[i] += g[i - 1];
    T c = 0, pw2 = 1;
    for (int i = 0; i <= k; i++) {
        c += comb_::C(k + 1, i) * g[k - i] * pw2;
        pw2 *= -r;
    }
    c /= (-r + 1).pow(k + 1);
    return c;
}

// Σ[0<=i<∞] i^k r^i
// comb を k+1 まで初期化
template <typename T>
T polynomial_r_power_sum_infinite(int k, T r) {
    vector<int> p(k + 1, -1);
    vector<T> f(k + 1, 1);
    if (k > 0) f[0] = 0;
    for (int i = 2; i <= k; i++) {
        if (p[i] == -1) {
            f[i] = T(i).pow(k);
            for (int j = i + i; j <= k; j += i) p[j] = i;
        } else {
            f[i] = f[p[i]] * f[i / p[i]];
        }
    }
    return polynomial_r_power_sum_infinite(f, r);
}
