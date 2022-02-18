
// kitamasa 法（d 階の線形漸化式で与えられる数列の第 n 項を求める）
// 計算量 O(d^2 log(n))

// 概要
// a[n] を a[n] = Σ[0 <= i < d] b[i]*a[i] の形で表したい。
// f(x) := x^d-c[1]*x^(d-1)-...-c[d-1]*x-c[d] とすると、
// x^n を f(x) で割った余りの x^i の項の係数が b[i] に対応する。

// verified with
// https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Kitamasa {
    // d 項間線形漸化式 a[n] = c[1]*a[n-1]+c[2]*a[n-2]+...+c[d]*a[n-d]
    const vector<T> a, c;
    const int d;
    // f(x) := x^d-c[1]*x^(d-1)-...-c[d-1]*x-c[d]
    vector<T> f;

    Kitamasa(const vector<T> &a, const vector<T> &c) : a(a), c(c), d(a.size()) {
        f.resize(d + 1);
        f[d] = 1;
        for (int i = 1; i <= d; i++) f[d - i] = -c[i];
    }

    vector<T> mul(const vector<T> &p, const vector<T> &q) const { // p(x)*q(x) を f(x) で割った余り
        int n = p.size(), m = q.size();
        vector<T> ret(n + m - 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ret[i + j] += p[i] * q[j];
        }
        for (int i = n + m - 2; i >= d; i--) {
            for (int j = 1; j <= d; j++) ret[i - j] -= ret[i] * f[d - j];
        }
        ret.resize(d);
        return ret;
    }

    vector<T> pow(vector<T> p, long long n) const { // p(x)^n を f(x) で割った余り
        vector<T> ret(1, 0);
        ret[0] = 1;
        while (n) {
            if (n & 1) ret = mul(ret, p);
            p = mul(p, p), n >>= 1;
        }
        return ret;
    }

    T operator[](long long n) const { // a[n] (0-indexed)
        if (n < d) return a[n];
        vector<T> x(d + 1, 0);
        x[1] = 1, x = pow(x, n);
        T ret = 0;
        for (int i = 0; i < d; i++) ret += x[i] * a[i];
        return ret;
    }
};
