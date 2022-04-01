
// 行列の固有多項式
// 計算量 O(n^3)

// 概要
// P を正則行列とすると、|xI-A| = |xI-P^{-1}AP| となるので、P^{-1} を左から、P を右からかけて A を Hessenberg 行列に変形する。
// これは行基本変形を行うときに対応する列基本変形を行えばよい。
// A が Hessenberg 行列であるとき、A の i 行 i 列目までの固有多項式を p_i(x) とすると、
// p_{i+1}(x) = (x-A[i][i])p_i(x) + Σ[k=1,..,i](-A[i-k][i])*Π[j=1,..,k](-A[i+1-j][i-j])*(-1)^k p_{i-k}(x)
// として計算することができる。

// verified with
// https://judge.yosupo.jp/problem/characteristic_polynomial

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> characteristic_polynomial(vector<vector<T>> A) {
    int n = A.size();
    for (int j = 0; j < n - 2; j++) {
        for (int i = j + 2; i < n; i++) {
            if (A[i][j] != 0) {
                swap(A[j + 1], A[i]);
                for (int k = 0; k < n; k++) swap(A[k][j + 1], A[k][i]);
                break;
            }
        }
        if (A[j + 1][j] != 0) {
            T inv = A[j + 1][j].inverse();
            for (int i = j + 2; i < n; i++) {
                T c = A[i][j] * inv;
                for (int k = j; k < n; k++) A[i][k] -= A[j + 1][k] * c;
                for (int k = 0; k < n; k++) A[k][j + 1] += A[k][i] * c;
            }
        }
    }
    vector<vector<T>> p(n + 1);
    p[0] = {1};
    for (int i = 0; i < n; i++) {
        p[i + 1].assign(i + 2, 0);
        for (int j = 0; j <= i; j++) {
            p[i + 1][j + 1] += p[i][j];
            p[i + 1][j] -= p[i][j] * A[i][i];
        }
        T c = 1;
        for (int k = 1; k <= i; k++) {
            c *= -A[i + 1 - k][i - k];
            T x = c * (k & 1 ? A[i - k][i] : -A[i - k][i]);
            for (int j = 0; j <= i - k; j++) p[i + 1][j] += p[i - k][j] * x;
        }
    }
    return p[n];
}
