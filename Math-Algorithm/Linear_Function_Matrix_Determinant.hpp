#pragma once

// 一次関数行列の行列式
// 計算量 O(n^3)

// 概要
// 一次関数行列 A_0 + A_1 x の行列式を求める。
// A_1 に基本変形を繰り返し、固有多項式の形に帰着する。

// verified with
// https://yukicoder.me/problems/no/1907
// https://atcoder.jp/contests/abc323/tasks/abc323_g

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Characteristic_Polynomial.hpp"
#include "../Math-Algorithm/Matrix.hpp"

template <typename T>
vector<T> linear_funcion_matrix_determinant(Matrix<T> A0, Matrix<T> A1) {
    int n = A0.n;
    assert(A0.m == n && A1.n == n && A1.m == n);
    T prd = 1;
    int deg = 0;
    for (int j = 0; j < n; j++) {
        while (deg <= n) {
            for (int i = j - 1; i >= 0; i--) {
                T y = A1[i][j];
                for (int k = 0; k < n; k++) {
                    A0[k][j] -= A0[k][i] * y;
                    A1[k][j] -= A1[k][i] * y;
                }
            }
            for (int i = j + 1; i < n; i++) {
                if (A1[i][j] != 0) {
                    swap(A0[j], A0[i]);
                    swap(A1[j], A1[i]);
                    prd = -prd;
                    break;
                }
            }
            if (A1[j][j] != 0) break;
            deg++;
            for (int i = 0; i < n; i++) {
                A1[i][j] = A0[i][j];
                A0[i][j] = 0;
            }
        }
        if (deg > n) return vector<T>(n + 1, 0);
        T x = A1[j][j].inverse();
        prd *= A1[j][j];
        for (int k = 0; k < n; k++) {
            A0[j][k] *= x;
            A1[j][k] *= x;
        }
        for (int i = 0; i < n; i++) {
            if (i != j) {
                T y = A1[i][j];
                for (int k = 0; k < n; k++) {
                    A0[i][k] -= A0[j][k] * y;
                    A1[i][k] -= A1[j][k] * y;
                }
            }
        }
    }
    auto f = characteristic_polynomial(-A0);
    vector<T> p(n + 1, 0);
    for (int i = deg; i <= n; i++) p[i - deg] += f[i] * prd;
    return p;
}
