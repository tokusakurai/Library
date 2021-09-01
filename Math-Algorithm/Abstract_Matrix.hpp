
// 抽象化された行列
// 計算量 積 : O(N*M*P)、K乗 : O(N^3*log(K))

// 概要
// 半環(R,+,*)に対して行列の積演算を行える。
// 単位行列は、対角成分は1元、それ以外は0元。
// 累乗：ダブリング

// verified with
// https://atcoder.jp/contests/abc009/tasks/abc009_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, T (*add)(T, T), T (*mul)(T, T), T e0, T e1>
struct Semi_Ring {
    T x;
    Semi_Ring() {}
    Semi_Ring(T x) : x(x) {}

    Semi_Ring &operator+=(const Semi_Ring &p) {
        if (x == e0) return *this = p.x;
        if (p.x == e0) return *this;
        return *this = add(x, p.x);
    }

    Semi_Ring &operator*=(const Semi_Ring &p) {
        if (x == e1) return *this = p.x;
        if (p.x == e1) return *this;
        return *this = mul(x, p.x);
    }

    // (a+b)+c = a+(b+c), 0+a = a+0 = a, a+b = b+a
    // (a*b)*c = a*(b*c), 1*a = a*1 = a
    // a*(b+c) = a*b+a*c, (a+b)*c = a*c+b*c
    // 0*a = a*0 = 0
    // これらを満たす演算の組として(+,*), (XOR,AND), (min,+), (max,+)などがある

    Semi_Ring operator+(const Semi_Ring &p) const { return Semi_Ring(*this) += p; }

    Semi_Ring operator*(const Semi_Ring &p) const { return Semi_Ring(*this) *= p; }

    friend ostream &operator<<(ostream &os, const Semi_Ring &p) { return os << p.x; }

    friend istream &operator>>(istream &is, Semi_Ring &p) {
        T a;
        is >> a;
        p = Semi_Ring(a);
        return is;
    }
};

template <typename t, t (*add)(t, t), t (*mul)(t, t), t e0, t e1>
struct Abstract_Matrix {
    using T = Semi_Ring<t, add, mul, e0, e1>;
    vector<vector<T>> A;

    Abstract_Matrix(int n, int m) : A(n, vector<T>(m, T(e0))) {}

    int height() const { return A.size(); }

    int width() const { return A.front().size(); }

    inline const vector<T> &operator[](int k) const { return A[k]; }

    inline vector<T> &operator[](int k) { return A[k]; }

    static Abstract_Matrix I(int l) {
        Abstract_Matrix ret(l, l);
        for (int i = 0; i < l; i++) ret[i][i] = T(e1);
        return ret;
    }

    Abstract_Matrix &operator*=(const Abstract_Matrix &B) {
        int n = height(), m = width(), p = B.width();
        assert(m == B.height());
        Abstract_Matrix ret(n, p);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < p; j++) ret[i][j] += A[i][k] * B[k][j];
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
