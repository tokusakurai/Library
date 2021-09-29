
// 線形回帰数列の各項列挙
// 計算量 O((D+N)*log(D+N))

// 概要
// F(x) := x^d-c[1]x^(d-1)-c[2]x^(d-2)-...-c[d]
// とすると、x^(n+d)をF(x)で割った商はa[n]+a[n-1]x+a[n-2]x^2+...+a[0]x^nとなる。

// verified with
// https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Formal_Power_Series.hpp"

template <typename T>
vector<T> linear_recursive_sequence_enumeration(const vector<T> &c, int n) {
    using FPS = Formal_Power_Series<T>;
    // d項間線形漸化式 a[n] = c[1]*a[n-1]+c[2]*a[n-2]+...+c[d]*a[n-d]
    // a[0] = 1のとき、a[0],a[1],...,a[n]を求める
    int d = c.size();
    FPS f(d, 1), g(n + d, 0);
    for (int i = 1; i < d; i++) f[d - 1 - i] = -c[i];
    g[n + d - 1] = 1;
    g /= f;
    reverse(begin(g), end(g));
    return g;
}
