#pragma once

// 抽象化された行列
// 計算量 積：O(mnp)、k 乗：O(n^3 log(k))

// 概要
// 半環 (R,+,*) に対して行列の積演算を行える。
// 単位行列は、対角成分は 1 元、それ以外は 0 元。
// 累乗：ダブリング

// verified with
// https://atcoder.jp/contests/abc009/tasks/abc009_4
// https://atcoder.jp/contests/abc236/tasks/abc236_g

#include <bits/stdc++.h>
using namespace std;

template <typename Semiring>
struct Abstract_Matrix {
    using S = typename Semiring::V;
    vector<vector<S>> A;

    // (a+b)+c = a+(b+c), 0+a = a+0 = a, a+b = b+a
    // (a*b)*c = a*(b*c), 1*a = a*1 = a
    // a*(b+c) = a*b+a*c, (a+b)*c = a*c+b*c
    // 0*a = a*0 = 0
    // これらを満たす演算の組として (+,*), (XOR,AND), (min,+), (max,+) などがある

    Abstract_Matrix(int n, int m) : A(n, vector<S>(m, Semiring::id_0)) {}

    int height() const { return A.size(); }

    int width() const { return A.front().size(); }

    inline const vector<S> &operator[](int k) const { return A[k]; }

    inline vector<S> &operator[](int k) { return A[k]; }

    static Abstract_Matrix I(int l) {
        Abstract_Matrix ret(l, l);
        for (int i = 0; i < l; i++) ret[i][i] = Semiring::id_1;
        return ret;
    }

    Abstract_Matrix &operator*=(const Abstract_Matrix &B) {
        int n = height(), m = width(), p = B.width();
        assert(m == B.height());
        Abstract_Matrix ret(n, p);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < p; j++) ret[i][j] = Semiring::add(ret[i][j], Semiring::mul(A[i][k], B[k][j]));
            }
        }
        swap(A, ret.A);
        return *this;
    }

    Abstract_Matrix operator*(const Abstract_Matrix &B) const { return Abstract_Matrix(*this) *= B; }

    Abstract_Matrix pow(long long k) {
        int n = height(), m = width();
        assert(n == m);
        Abstract_Matrix now = *this, ret = I(n);
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }
};
