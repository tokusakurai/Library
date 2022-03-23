
// 行列式（任意 mod）
// 計算量 O(n^2(n+log(m)))

// 概要
// 掃き出し法を互除法を用いながら行う。各列について O(log(m)) 回行の加減を行う必要がある。

// verified with
// https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

int determinant(vector<vector<int>> A, const int &m) {
    int n = A.size();
    long long det = 1;
    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            if (A[j][j] == 0) {
                swap(A[j], A[i]);
                if (det > 0) det = m - det;
            }
            while (A[i][j] > 0) {
                if (A[j][j] > A[i][j]) {
                    swap(A[j], A[i]);
                    if (det > 0) det = m - det;
                }
                long long c = A[i][j] / A[j][j];
                for (int k = j; k < n; k++) {
                    long long x = c * A[j][k] % m;
                    A[i][k] -= x;
                    if (A[i][k] < 0) A[i][k] += m;
                }
            }
        }
        det *= A[j][j], det %= m;
    }
    return det;
}
