
// オンライン畳み込み
// 計算量 O(n log^2(n))

// 概要
// 多項式 a(x) と b(x) の i 次の係数が与えられて、c(x) = a(x)b(x) の i 次の係数を答えるクエリを 0<=i<n について扱える。
// ここでは、a_0,..,a_i,b_0,..,b_i が与えられたときに、∑[1<=j<=i] a_j * b_{i+1-j} が c[i+1] に格納されるようにしている。

// 参考文献
// https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c

// verified with
// https://atcoder.jp/contests/abc230/tasks/abc230_h
// https://atcoder.jp/contests/abc315/tasks/abc315_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

template <typename T>
struct Relaxed_Convolution {
    using NTT_ = Number_Theoretic_Transform<T>;
    int n;
    vector<T> a, b, c;

    Relaxed_Convolution(int max_n = -1) : n(0) {
        if (max_n != -1) a.reserve(max_n + 1), b.reserve(max_n + 1), c.reserve(2 * max_n + 1);
    }

    void calc_contribution(int la, int ra, int lb, int rb) {
        vector<T> f(begin(a) + la, begin(a) + ra);
        vector<T> g(begin(b) + lb, begin(b) + rb);
        auto h = NTT_::convolve(f, g);
        for (int k = 0; k < (int)h.size(); k++) c[la + lb + k] += h[k];
    }

    T insert(T x, T y) {
        a.push_back(x), b.push_back(y), c.push_back(0);
        if (n > 0) c.push_back(0);
        if (n == 0) {
            c[0] += a[0] * b[0];
        } else if (n == 1) {
            c[1] += a[0] * b[1] + a[1] * b[0];
            c[2] += a[1] * b[1];
        } else {
            c[n] += a[0] * b[n] + a[n] * b[0];
            c[n + 1] += a[1] * b[n] + a[n] * b[1];
            int t = __builtin_ctz(n + 1);
            if (n + 1 == (1 << t)) {
                for (int k = 1; k < t - 1; k++) {
                    calc_contribution(1 << k, 1 << (k + 1), n + 1 - (1 << k), n + 1);
                    calc_contribution(n + 1 - (1 << k), n + 1, 1 << k, 1 << (k + 1));
                }
                calc_contribution(1 << (t - 1), 1 << t, 1 << (t - 1), 1 << t);
            } else {
                for (int k = 1; k <= t; k++) {
                    calc_contribution(1 << k, 1 << (k + 1), n + 1 - (1 << k), n + 1);
                    calc_contribution(n + 1 - (1 << k), n + 1, 1 << k, 1 << (k + 1));
                }
            }
        }
        return c[n++];
    }

    T get(int k) const { return k < (int)c.size() ? c[k] : 0; }

    T operator[](int k) const { return get(k); }
};
