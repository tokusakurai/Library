
// ラグランジュ補間 (1 点)
// 計算量 O(n)

// 概要
// n-1 次以下の多項式 f(x) について f(0),f(1),...,f(n-1) の値が与えられたときに、与えられた 1 点 c について f(c) を求める。
// ラグランジュ補間をすると、
// f(c) = Σ[0<=i<n] f(i)Π[j!=i](c-j)/(i-j)
// であるから、階乗の逆数と x-i の累積積を左右から求めることで高速化する。

// verified with
// https://atcoder.jp/contests/arc033/tasks/arc033_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Combination.hpp"

// n 次多項式 f の f(0),...,f(n) を与えて f(c) を計算
// comb を n まで初期化する
template <typename T>
T single_point_interpolation(vector<T> ys, T c) {
    using comb_ = Combination<T>;
    int n = ys.size();
    T coef = 1;
    for (int i = 0; i < n; i++) {
        ys[i] *= coef * comb_::ifac(i);
        coef *= c - i;
    }
    coef = 1;
    T ret = 0;
    for (int i = n - 1; i >= 0; i--) {
        ret += ys[i] * coef * comb_::ifac(n - 1 - i) * ((n - 1 - i) & 1 ? -1 : 1);
        coef *= c - i;
    }
    return ret;
}
