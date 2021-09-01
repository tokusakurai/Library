
// 疎行列の行列式
// 計算量 O(N^2+K*N) (Kは行列の非零成分の個数)

// 概要
// 行列Aの固有多項式にAを代入すると、ケーリーハミルトンの定理より0行列となる。
// これより、行列の列A^0,A^1,....は線形漸化式で表されるので、この最小多項式をBerlekamp-Masseyで求められる。
// 最小多項式の次数がAの次数nと一致していればその定数項に(-1)^nをかければAの行列式が得られる。
// Aの最小多項式がn次でなくても対角成分が非零の対角行列Dをランダムに取るとADの最小多項式の次数がnになる確率は高いので、乱択する。

// verified with
// https://judge.yosupo.jp/problem/sparse_matrix_det

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Berlekamp_Massey.hpp"
#include "../Other/Random.hpp"

template <typename T>
T determinant(const vector<vector<pair<int, T>>> &A) {
    int n = A.size();
    Random_Number_Generator rng;
    int MAX = T(-1).x;
    vector<T> a(n), b(n), d(n);
    for (int i = 0; i < n; i++) a[i] = T(rng(1, MAX + 1)), b[i] = T(rng(1, MAX + 1)), d[i] = T(rng(1, MAX + 1));
    T r = 1;
    for (int i = 0; i < n; i++) r *= d[i];
    vector<T> x(2 * n, 0);
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < n; j++) x[i] += a[j] * b[j];
        vector<T> c(n, 0);
        for (int j = 0; j < n; j++) {
            for (auto e : A[j]) c[j] += e.second * b[e.first];
        }
        for (int j = 0; j < n; j++) c[j] *= d[j];
        swap(b, c);
    }
    vector<T> y = Berlekamp_Massey(x);
    if (y.back() == T(0)) return 0;
    if ((int)y.size() == n + 1) return y.back() * (n & 1 ? 1 : -1) / r;
    return determinant(A);
}
