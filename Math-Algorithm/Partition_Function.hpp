
// 分割数のテーブル
// 計算量 O(n log(n))

// 定義
// 非負整数 n について、分割数 p(n) := n を順番の違いを除いて自然数の和で表す方法の総数

// 概要
// 分割数の母関数を P(x) := p(0)+p(1)x+... とすると、
// P(x) = Π[1<=n](1+x^n+x^(2n)+...) = Π[1<=n](1/(1-x^n))
// となる。これにオイラーの五角数定理を適用することで、
// 1/P(x) = Σ[-∞<n<∞]((-1)^n x^(n(3n-1)/2)) となるので、FPS の inv を用いて P(x) の先頭 n+1 項を高速に計算できる。

// verified with
// https://judge.yosupo.jp/problem/partition_function

#include "../Math-Algorithm/Formal_Power_Series.hpp"

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> partition_function(int n) {
    using FPS = Formal_Power_Series<T>;
    FPS f(n + 1, 0);
    for (int i = 0;; i++) {
        int j = i * (3 * i - 1) / 2;
        if (j > n) break;
        f[j] += (i & 1 ? -1 : 1);
    }
    for (int i = -1;; i--) {
        int j = i * (3 * i - 1) / 2;
        if (j > n) break;
        f[j] += (i & 1 ? -1 : 1);
    }
    return f.inv();
}
