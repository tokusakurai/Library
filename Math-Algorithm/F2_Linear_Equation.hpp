#pragma once

// https://yukicoder.me/problems/no/1421
// https://atcoder.jp/contests/abc276/tasks/abc276_h

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/F2_Matrix.hpp"

// Ax = b の解の 1 つと解空間の基底の組を返す
template <typename T>
vector<vector<int>> F2_linear_equation(F2_Matrix<T> A, vector<int> b) {
    int n = A.n, m = A.m;
    A.row_reduction(b);
    vector<vector<int>> ret;
    vector<int> p(n, m);
    vector<bool> is_zero(m, true);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 1) {
                p[i] = j;
                break;
            }
        }
        if (p[i] < m) {
            is_zero[p[i]] = false;
        } else if (b[i] == 1) {
            return {};
        }
    }
    vector<int> x(m, 0);
    for (int i = 0; i < n; i++) {
        if (p[i] < m) x[p[i]] = b[i];
    }
    ret.push_back(x);
    for (int j = 0; j < m; j++) {
        if (!is_zero[j]) continue;
        x[j] = 1;
        for (int i = 0; i < n; i++) {
            if (p[i] < n) x[p[i]] ^= A[i][j];
        }
        ret.push_back(x);
        x[j] = 0;
    }
    return ret;
}
