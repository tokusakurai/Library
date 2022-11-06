
// 行列計算
// 計算量 積：O(nmk)、k 乗：O(n^3 log(k))、簡約化・ガウスの消去法：O(nm^2)、逆行列：O(n^3)

// 累乗：ダブリング
// ガウスの消去法：行基本変形を繰り返すことで連立一次方程式の解を求める。

// verified with
// https://judge.yosupo.jp/problem/matrix_product
// https://judge.yosupo.jp/problem/matrix_det
// https://judge.yosupo.jp/problem/inverse_matrix
// https://judge.yosupo.jp/problem/system_of_linear_equations

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Matrix {
    vector<vector<T>> A;
    int n, m;

    Matrix(int n, int m) : A(n, vector<T>(m, 0)), n(n), m(m) {}

    inline const vector<T> &operator[](int k) const { return A[k]; }

    inline vector<T> &operator[](int k) { return A[k]; }

    static Matrix I(int l) {
        Matrix ret(l, l);
        for (int i = 0; i < l; i++) ret[i][i] = 1;
        return ret;
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

    Matrix operator*(const Matrix &B) const { return Matrix(*this) *= B; }

    Matrix pow(long long k) const {
        assert(n == m);
        Matrix now = *this, ret = I(n);
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    bool eq(const T &a, const T &b) const {
        return a == b;
        // return abs(a-b) <= EPS;
    }

    // 行基本変形を用いて簡約化を行い、(rank, det) の組を返す
    pair<int, T> row_reduction(vector<T> &b) {
        assert((int)b.size() == n);
        if (n == 0) return make_pair(0, m > 0 ? 0 : 1);
        int check = 0, rank = 0;
        T det = (n == m ? 1 : 0);
        assert(b.size() == n);
        for (int j = 0; j < m; j++) {
            int pivot = check;
            for (int i = check; i < n; i++) {
                if (A[i][j] != 0) pivot = i;
                // if(abs(A[i][j]) > abs(A[pivot][j])) pivot = i; // T が小数の場合はこちら
            }
            if (check != pivot) det *= T(-1);
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

    // 行基本変形を行い、逆行列を求める
    pair<bool, Matrix> inverse() {
        if (n != m) return make_pair(false, Matrix(0, 0));
        if (n == 0) return make_pair(true, Matrix(0, 0));
        Matrix ret = I(n);
        for (int j = 0; j < n; j++) {
            int pivot = j;
            for (int i = j; i < n; i++) {
                if (A[i][j] != 0) pivot = i;
                // if(abs(A[i][j]) > abs(A[pivot][j])) pivot = i; // T が小数の場合はこちら
            }
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
        return make_pair(true, ret);
    }

    // Ax = b の解の 1 つと解空間の基底の組を返す
    vector<vector<T>> Gaussian_elimination(vector<T> b) {
        row_reduction(b);
        vector<vector<T>> ret;
        vector<int> p(n, m);
        vector<bool> is_zero(m, true);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!eq(A[i][j], T(0))) {
                    p[i] = j;
                    break;
                }
            }
            if (p[i] < m) {
                is_zero[p[i]] = false;
            } else if (!eq(b[i], T(0))) {
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
};
