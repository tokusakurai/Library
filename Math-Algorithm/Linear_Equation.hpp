
// 線形方程式の求解
// 計算量 : O(nm^2)

// 概要
// Gauss の消去法を用いる。

// verified with
// https://judge.yosupo.jp/problem/system_of_linear_equations

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Matrix.hpp"

// Ax = b の解の 1 つと解空間の基底の組を返す
template <typename T>
vector<vector<T>> linear_equation(Matrix<T> A, vector<T> b) {
    int n = A.n, m = A.m;
    A.row_reduction(b);
    vector<vector<T>> ret;
    vector<int> p(n, m);
    vector<bool> is_zero(m, true);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!Matrix<T>::eq(A[i][j], T(0))) {
                p[i] = j;
                break;
            }
        }
        if (p[i] < m) {
            is_zero[p[i]] = false;
        } else if (!Matrix<T>::eq(b[i], T(0))) {
            return {};
        }
    }
    vector<T> x(m, T(0));
    for (int i = 0; i < n; i++) {
        if (p[i] < m) x[p[i]] = b[i];
    }
    ret.push_back(x);
    for (int j = 0; j < m; j++) {
        if (!is_zero[j]) continue;
        x[j] = T(1);
        for (int i = 0; i < n; i++) {
            if (p[i] < m) x[p[i]] = -A[i][j];
        }
        ret.push_back(x);
        x[j] = T(0);
    }
    return ret;
}
