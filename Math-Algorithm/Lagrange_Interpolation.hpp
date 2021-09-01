
// ラグランジュ補間(1点)
// 計算量 O(N+log(M))

// 概要
// N次多項式f(x)についてf(0),f(1),...,f(N)の値が与えられたときに、与えられた1点xについてf(x)を求める。
// ラグランジュ補間をすると、
// f(x) = Σy_i*Π{(x-j)/(i-j)}(j≠i)
// であるから、階乗の逆数と(x-i)の累積積を左右から求めることで高速化する。

// verified with
// https://atcoder.jp/contests/arc033/tasks/arc033_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T Lagrange_interpolation(const vector<T> &ys, T x) {
    int n = ys.size();
    vector<T> ifac(n);
    ifac[n - 1] = 1;
    for (int i = 1; i < n; i++) ifac[n - 1] *= i;
    ifac[n - 1] = T(1) / ifac[n - 1];
    for (int i = n - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i;
    vector<T> L(n + 1, 1), R(n + 1, 1);
    for (int i = 0; i < n; i++) L[i + 1] = L[i] * (x - i);
    for (int i = n - 1; i >= 0; i--) R[i] = R[i + 1] * (x - i);
    T ret = 0;
    for (int i = 0; i < n; i++) ret += ys[i] * L[i] * R[i + 1] * ifac[i] * ifac[n - 1 - i] * ((n - 1 - i) & 1 ? -1 : 1);
    return ret;
}
