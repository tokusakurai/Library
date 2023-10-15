
// 行列計算
// 計算量 積：O(nmk)、k 乗：O(n^3 log(k))、行簡約化：O(nm^2)、逆行列：O(n^3)

// 累乗：ダブリング

// verified with
// https://judge.yosupo.jp/problem/matrix_product
// https://judge.yosupo.jp/problem/matrix_det
// https://judge.yosupo.jp/problem/inverse_matrix

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool is_float = false>
struct Matrix {
    vector<vector<T>> A;
    int n, m;

    Matrix() = default;

    Matrix(int n) : A(n, vector<T>(n, 0)), n(n), m(n) {}

    Matrix(int n, int m) : A(n, vector<T>(m, 0)), n(n), m(m) {}

    Matrix(const vector<vector<T>> &A) : A(A), n((int)A.size()), m(A.empty() ? 0 : (int)A[0].size()) {}

    inline const vector<T> &operator[](int k) const { return A[k]; }

    inline vector<T> &operator[](int k) { return A[k]; }

    static Matrix I(int l) {
        Matrix ret(l, l);
        for (int i = 0; i < l; i++) ret[i][i] = 1;
        return ret;
    }

    Matrix &operator+=(const Matrix &B) {
        assert(n == B.n && m == B.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) A[i][j] += B[i][j];
        }
        return *this;
    }

    Matrix &operator-=(const Matrix &B) {
        assert(n == B.n && m == B.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) A[i][j] -= B[i][j];
        }
        return *this;
    }

    Matrix &operator*=(const Matrix &B) {
        assert(m == B.n);
        Matrix ret(n, B.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < B.m; j++) ret[i][j] += A[i][k] * B[k][j];
            }
        }
        swap(A, ret.A);
        m = B.m;
        return *this;
    }

    Matrix &operator/=(const Matrix &B) {
        *this *= B.inverse();
        return *this;
    }

    Matrix operator-() const {
        Matrix ret(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ret[i][j] = -A[i][j];
        }
        return ret;
    }

    Matrix operator+(const Matrix &B) const { return Matrix(*this) += B; }

    Matrix operator-(const Matrix &B) const { return Matrix(*this) -= B; }

    Matrix operator*(const Matrix &B) const { return Matrix(*this) *= B; }

    Matrix operator/(const Matrix &B) const { return Matrix(*this) /= B; }

    bool operator==(const Matrix &B) const { return A == B.A; }

    bool operator!=(const Matrix &B) const { return A != B.A; }

    Matrix pow(long long k) const {
        assert(n == m);
        Matrix now = *this, ret = I(n);
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    Matrix transpose() const {
        Matrix ret(m, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ret[j][i] = A[i][j];
        }
        return ret;
    }

    Matrix submatrix(vector<int> rs, vector<int> cs) {
        int sub_n = rs.size(), sub_m = cs.size();
        Matrix ret(sub_n, sub_m);
        for (int i = 0; i < sub_n; i++) {
            for (int j = 0; j < sub_m; j++) ret[i][j] = A[rs[i]][cs[j]];
        }
        return ret;
    }

    Matrix submatrix(int lr, int rr, int lc, int rc) {
        assert(0 <= lr && lr <= rr && rr <= n);
        assert(0 <= lc && lc <= rc && rc <= m);
        int sub_n = rr - lr, sub_m = rc - lc;
        Matrix ret(sub_n, sub_m);
        for (int i = 0; i < sub_n; i++) {
            for (int j = 0; j < sub_m; j++) ret[i][j] = A[lr + i][lc + j];
        }
        return ret;
    }

    static bool eq(const T &a, const T &b) {
        if constexpr (is_float) return abs(a - b) <= 1e-6;
        return a == b;
    }

    int get_pivot(int j, int i) {
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if constexpr (is_float) {
                if (abs(A[k][j]) > abs(A[pivot][j])) pivot = k;
            } else {
                if (A[k][j] != 0) pivot = k;
            }
        }
        return pivot;
    }

    // 行基本変形を用いて簡約化を行い、(rank, det) の組を返す
    pair<int, T> row_reduction(vector<T> &b) {
        assert((int)b.size() == n);
        if (n == 0) return make_pair(0, m > 0 ? 0 : 1);
        int check = 0, rank = 0;
        T det = (n == m ? 1 : 0);
        for (int j = 0; j < m; j++) {
            int pivot = get_pivot(j, check);
            if (check != pivot) det = -det;
            swap(A[check], A[pivot]), swap(b[check], b[pivot]);
            if (eq(A[check][j], T(0))) {
                det = T(0);
                continue;
            }
            rank++;
            det *= A[check][j];
            T r = T(1) / A[check][j];
            for (int k = j + 1; k < m; k++) A[check][k] *= r;
            b[check] *= r;
            A[check][j] = T(1);
            for (int i = 0; i < n; i++) {
                if (i == check) continue;
                if (!eq(A[i][j], 0)) {
                    for (int k = j + 1; k < m; k++) A[i][k] -= A[i][j] * A[check][k];
                    b[i] -= A[i][j] * b[check];
                }
                A[i][j] = T(0);
            }
            if (++check == n) break;
        }
        return make_pair(rank, det);
    }

    pair<int, T> row_reduction() {
        vector<T> b(n, T(0));
        return row_reduction(b);
    }

    int rank() const { return Matrix(*this).row_reduction().first; }

    T determinant() const {
        assert(n == m);
        return Matrix(*this).row_reduction().second;
    }

    pair<bool, Matrix> inverse() {
        if (n != m) return make_pair(false, Matrix(0, 0));
        if (n == 0) return make_pair(true, Matrix(0, 0));
        vector<vector<T>> A_cpy = A;
        Matrix ret = I(n);
        for (int j = 0; j < n; j++) {
            int pivot = get_pivot(j, j);
            swap(A[j], A[pivot]), swap(ret[j], ret[pivot]);
            if (eq(A[j][j], T(0))) return make_pair(false, Matrix(0, 0));
            T r = T(1) / A[j][j];
            for (int k = j + 1; k < n; k++) A[j][k] *= r;
            for (int k = 0; k < n; k++) ret[j][k] *= r;
            A[j][j] = T(1);
            for (int i = 0; i < n; i++) {
                if (i == j) continue;
                if (!eq(A[i][j], T(0))) {
                    for (int k = j + 1; k < n; k++) A[i][k] -= A[i][j] * A[j][k];
                    for (int k = 0; k < n; k++) ret[i][k] -= A[i][j] * ret[j][k];
                }
                A[i][j] = T(0);
            }
        }
        A = A_cpy;
        return make_pair(true, ret);
    }
};
