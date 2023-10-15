
// 高速 kitamasa 法 (d 階の線形漸化式で与えられる数列の第 n 項を求める)
// 計算量 O(d log(d)log(n))

// 概要
// FPS を用いて kitamasa 法における多項式の積と除算を高速化する。

// verified with
// https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Formal_Power_Series.hpp"

template <typename T>
struct Kitamasa {
    using FPS = Formal_Power_Series<T>;
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

    // p(x)*q(x) を f(x) で割った余り
    vector<T> mul(const vector<T> &p, const vector<T> &q) const {
        FPS ret = FPS(p) * FPS(q);
        ret %= FPS(f);
        return ret;
    }

    // p(x)^n を f(x) で割った余り
    vector<T> pow(vector<T> p, long long n) const {
        vector<T> ret(d, 0);
        ret[0] = 1;
        while (n) {
            if (n & 1) ret = mul(ret, p);
            p = mul(p, p), n >>= 1;
        }
        return ret;
    }

    // a[n] (0-indexed)
    T operator[](long long n) const {
        vector<T> x(d + 1, 0);
        x[1] = 1, x = pow(x, n);
        x.resize(d);
        T ret = 0;
        for (int i = 0; i < d; i++) ret += x[i] * a[i];
        return ret;
    }
};
