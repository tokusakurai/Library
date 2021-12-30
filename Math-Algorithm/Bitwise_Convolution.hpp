
// ビット演算による添字畳込み
// 計算量 AND 畳み込み・OR 畳み込み・XOR 畳み込み：O(n log(n))、subset 畳み込み：O(n log(n)^2)
// 空間計算量 AND 畳み込み・OR 畳み込み・XOR 畳み込み：O(n)、subset 畳み込み：O(n log(n))

// 概要
// AND 畳み込み：a,b を上位集合で高速ゼータ変換 -> 両者の各項の積を取る -> 上位集合で高速メビウス変換
// OR 畳み込み：a,b を下位集合で高速ゼータ変換 -> 両者の各項の積を取る -> 下位集合で高速メビウス変換
// XOR 畳み込み：a,b を高速アダマール変換 -> 両者の各項の積を取る -> 高速逆アダマール変換
// subset 畳み込み：A(S) = a(S)*x^|S| とした多項式を考えると、A と B の OR 畳み込みを求めれば良い。

// verified with
// https://judge.yosupo.jp/problem/bitwise_and_convolution
// https://judge.yosupo.jp/problem/bitwise_xor_convolution
// https://judge.yosupo.jp/problem/subset_convolution

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Zeta_Mobius_Hadamard.hpp"

template <typename T>
vector<T> bitwise_and_convolve(vector<T> a, vector<T> b) {
    int n = a.size();
    assert(b.size() == n && (n & (n - 1)) == 0);
    fast_zeta_transform(a, true), fast_zeta_transform(b, true);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    fast_mobius_transform(a, true);
    return a;
}

template <typename T>
vector<T> bitwise_or_convolve(vector<T> a, vector<T> b) {
    int n = a.size();
    assert(b.size() == n && (n & (n - 1)) == 0);
    fast_zeta_transform(a, false), fast_zeta_transform(b, false);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    fast_mobius_transform(a, false);
    return a;
}

template <typename T>
vector<T> bitwise_xor_convolve(vector<T> a, vector<T> b) {
    int n = a.size();
    assert(b.size() == n && (n & (n - 1)) == 0);
    fast_hadamard_transform(a), fast_hadamard_transform(b);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    fast_hadamard_transform(a, true);
    return a;
}

template <typename T>
vector<T> subset_convolve(const vector<T> &a, const vector<T> &b) {
    int n = a.size();
    assert(b.size() == n && (n & (n - 1)) == 0);
    int k = __builtin_ctz(n);
    vector<vector<T>> A(k + 1, vector<T>(n, 0)), B(k + 1, vector<T>(n, 0)), C(k + 1, vector<T>(n, 0));
    for (int i = 0; i < n; i++) {
        int t = __builtin_popcount(i);
        A[t][i] = a[i], B[t][i] = b[i];
    }
    for (int i = 0; i <= k; i++) fast_zeta_transform(A[i], false), fast_zeta_transform(B[i], false);
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k - i; j++) {
            for (int l = 0; l < n; l++) C[i + j][l] += A[i][l] * B[j][l];
        }
    }
    for (int i = 0; i <= k; i++) fast_mobius_transform(C[i], false);
    vector<T> c(n);
    for (int i = 0; i < n; i++) c[i] = C[__builtin_popcount(i)][i];
    return c;
}
