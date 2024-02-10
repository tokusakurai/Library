#pragma once

// 二元体での行列
// 計算量 簡約化・ガウスの消去法：O(nm^2/w) (w はワードサイズ)

// 概要
// 行 i に行 j を足す操作は行 i に行 j を XOR する操作と同値なので、bitset で高速化できる。

// verified with
// https://yukicoder.me/problems/no/1421
// https://atcoder.jp/contests/abc276/tasks/abc276_h

#include <bits/stdc++.h>
using namespace std;


template <typename T>
struct F2_Matrix {
    vector<T> A;
    int n, m;

    F2_Matrix() = default;

    F2_Matrix(int n, int m) : A(n), n(n), m(m) {}

    inline const T &operator[](int k) const { return A[k]; }

    inline T &operator[](int k) { return A[k]; }

    // 行基本変形を用いて簡約化を行い、rank を返す。
    int row_reduction(vector<int> &b) {
        assert((int)b.size() == n);
        if (n == 0) return 0;
        int check = 0, rank = 0;
        for (int j = 0; j < m; j++) {
            int pivot = check;
            for (int i = check; i < n; i++) {
                if (A[i][j]) pivot = i;
            }
            swap(A[check], A[pivot]), swap(b[check], b[pivot]);
            if (!A[check][j]) continue;
            rank++;
            for (int i = 0; i < n; i++) {
                if (i == check || !A[i][j]) continue;
                A[i] ^= A[check], b[i] ^= b[check];
            }
            if (++check == n) break;
        }
        return rank;
    }

    int row_reduction() {
        vector<int> b(n, 0);
        return row_reduction(b);
    }

    int rank() const { return Matrix(*this).row_reduction(); }
};

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
