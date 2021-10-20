
// 二元体での行列
// 計算量 簡約化・ガウスの消去法 : O(mn^2/64)

// 概要
// 行iに行jを足す操作は行iに行jをXORする操作と同値なので、bitsetで高速化できる。

// verified with
// https://yukicoder.me/problems/no/1421

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct F2_Matrix {
    vector<T> A;

    F2_Matrix(int m) : A(m) {}

    int height() const { return A.size(); }

    int width() const { return A.front().size(); }

    inline const T &operator[](int k) const { return A[k]; }

    inline T &operator[](int k) { return A[k]; }

    int row_reduction(vector<int> &b) { // 行基本変形を用いて簡約化を行い、rankを返す。
        int m = height(), n = width(), check = 0, rank = 0;
        assert(b.size() == m);
        for (int j = 0; j < n; j++) {
            int pivot = check;
            for (int i = check; i < m; i++) {
                if (A[i][j]) pivot = i;
            }
            swap(A[check], A[pivot]), swap(b[check], b[pivot]);
            if (!A[check][j]) continue;
            rank++;
            for (int i = 0; i < m; i++) {
                if (i == check || !A[i][j]) continue;
                A[i] ^= A[check], b[i] ^= b[check];
            }
            if (++check == m) break;
        }
        return rank;
    }

    int row_reduction() {
        vector<int> b(height(), 0);
        return row_reduction(b);
    }

    vector<vector<int>> Gausiann_elimination(vector<int> b) { // Ax = bの解の1つと解空間の基底の組を返す
        int m = height(), n = width();
        row_reduction(b);
        vector<vector<int>> ret;
        vector<int> p(m, n);
        vector<bool> is_zero(n, true);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j] == 1) {
                    p[i] = j;
                    break;
                }
            }
            if (p[i] < n) {
                is_zero[p[i]] = false;
            } else if (b[i] == 1) {
                return {};
            }
        }
        vector<int> x(n, 0);
        for (int i = 0; i < m; i++) {
            if (p[i] < n) x[p[i]] = b[i];
        }
        ret.push_back(x);
        for (int j = 0; j < n; j++) {
            if (!is_zero[j]) continue;
            x[j] = 1;
            for (int i = 0; i < m; i++) {
                if (p[i] < n) x[p[i]] ^= A[i][j];
            }
            ret.push_back(x), x[j] = 0;
        }
        return ret;
    }
};
