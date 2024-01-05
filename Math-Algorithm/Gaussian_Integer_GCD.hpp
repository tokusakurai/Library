
// ガウス整数環の GCD
// 計算量 O(log(max{||a||, ||b||}))

// 概要
// ガウス整数環 Z[i] を考える。
// Z[i] の元 a,b(b!=0) について、a = qb+r かつ (||r||^2 <= (||b||^2)/2) を満たす q,r ∈ Z[i] が存在する。
// 従って Z[i] はノルムに関してユークリッド環であり、PID, UFD でもあるので単元倍の自由度を除いて gcd を定めることができる。
// さらにノルムが 1/2 以下になることから、ユークリッドの互除法と同様のアルゴリズムが高速に動作することがわかる。

// verified with
// https://judge.yosupo.jp/problem/gcd_of_gaussian_integers

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
complex<T> Gaussian_integer_gcd(complex<T> a, complex<T> b) {
    if (norm(a) < norm(b)) swap(a, b);
    while (b != complex<T>(0, 0)) {
        T b_norm = norm(b);
        complex<T> c = a * conj(b);
        T x = c.real() + b_norm / 2;
        T y = c.imag() + b_norm / 2;
        x = x > 0 ? x / b_norm : (x - b_norm + 1) / b_norm;
        y = y > 0 ? y / b_norm : (y - b_norm + 1) / b_norm;
        a -= b * complex<T>(x, y);
        swap(a, b);
    }
    return a;
}
