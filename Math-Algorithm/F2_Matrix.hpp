#pragma once

// 二元体での行列
// 計算量 簡約化・ガウスの消去法：O(nm^2/w) (w はワードサイズ)

// 概要
// 行 i に行 j を足す操作は行 i に行 j を XOR する操作と同値なので、bitset で高速化できる。

// verified with
// https://judge.yosupo.jp/problem/matrix_product_mod_2
// https://judge.yosupo.jp/problem/matrix_det_mod_2
// https://judge.yosupo.jp/problem/inverse_matrix_mod_2

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct F2_Matrix {
    vector<T> A;
    int n, m;

    F2_Matrix() = default;

    F2_Matrix(int n) : A(n), n(n), m(n) {}

    F2_Matrix(int n, int m) : A(n), n(n), m(m) {}

    F2_Matrix(const vector<vector<int>> &a) : n((int)a.size()), m(a.empty() ? 0 : (int)a[0].size()) {
        A.resize(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) A[i][j] = a[i][j];
        }
    }

    F2_Matrix(const vector<string> &s) : n((int)s.size()), m(s.empty() ? 0 : (int)s[0].size()) {
        A.resize(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) A[i][j] = s[i][j] - '0';
        }
    }

    inline const T &operator[](int k) const { return A[k]; }

    inline T &operator[](int k) { return A[k]; }

    static F2_Matrix I(int l) {
        F2_Matrix ret(l, l);
        for (int i = 0; i < l; i++) ret[i][i] = 1;
        return ret;
    }

    F2_Matrix &operator+=(const F2_Matrix &B) {
        assert(n == B.n && m == B.m);
        for (int i = 0; i < n; i++) A[i] ^= B[i];
        return *this;
    }

    F2_Matrix &operator*=(const F2_Matrix &B) {
        assert(m == B.n);
        F2_Matrix ret(n, B.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (A[i][j]) ret[i] ^= B[j];
            }
        }
        swap(A, ret.A);
        m = B.m;
        return *this;
    }

    F2_Matrix operator+(const F2_Matrix &B) const { return F2_Matrix(*this) += B; }

    F2_Matrix operator*(const F2_Matrix &B) const { return F2_Matrix(*this) *= B; }

    bool operator==(const F2_Matrix &B) const { return A == B.A; }

    bool operator!=(const F2_Matrix &B) const { return A != B.A; }

    F2_Matrix pow(long long k) const {
        assert(n == m);
        F2_Matrix now = *this, ret = I(n);
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    F2_Matrix transpose() const {
        F2_Matrix ret(m, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ret[j][i] = A[i][j];
        }
        return ret;
    }

    F2_Matrix submatrix(vector<int> rs, vector<int> cs) {
        int sub_n = rs.size(), sub_m = cs.size();
        F2_Matrix ret(sub_n, sub_m);
        for (int i = 0; i < sub_n; i++) {
            for (int j = 0; j < sub_m; j++) ret[i][j] = A[rs[i]][cs[j]];
        }
        return ret;
    }

    F2_Matrix submatrix(int lr, int rr, int lc, int rc) {
        assert(0 <= lr && lr <= rr && rr <= n);
        assert(0 <= lc && lc <= rc && rc <= m);
        int sub_n = rr - lr, sub_m = rc - lc;
        F2_Matrix ret(sub_n, sub_m);
        for (int i = 0; i < sub_n; i++) {
            for (int j = 0; j < sub_m; j++) ret[i][j] = A[lr + i][lc + j];
        }
        return ret;
    }

    int get_pivot(int j, int i) {
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if (A[k][j]) pivot = k;
        }
        return pivot;
    }

    // 行基本変形を用いて簡約化を行い、rank を返す。
    int row_reduction(vector<int> &b) {
        assert((int)b.size() == n);
        if (n == 0) return 0;
        int check = 0, rank = 0;
        for (int j = 0; j < m; j++) {
            int pivot = get_pivot(j, check);
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

    int rank() const { return F2_Matrix(*this).row_reduction(); }

    int determinant() const {
        assert(n == m);
        int r = F2_Matrix(*this).row_reduction();
        return (r == n ? 1 : 0);
    }

    pair<bool, F2_Matrix> inverse() {
        if (n != m) return make_pair(false, F2_Matrix(0, 0));
        if (n == 0) return make_pair(true, F2_Matrix(0, 0));
        vector<T> A_cpy = A;
        F2_Matrix ret = I(n);
        for (int j = 0; j < n; j++) {
            int pivot = get_pivot(j, j);
            swap(A[j], A[pivot]), swap(ret[j], ret[pivot]);
            if (!A[j][j]) {
                A = A_cpy;
                return make_pair(false, F2_Matrix(0, 0));
            }
            for (int i = 0; i < n; i++) {
                if (i == j) continue;
                if (A[i][j]) {
                    A[i] ^= A[j];
                    ret[i] ^= ret[j];
                }
            }
        }
        A = A_cpy;
        return make_pair(true, ret);
    }
};
