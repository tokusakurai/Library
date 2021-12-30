
// 添字 GCD・LCM 畳み込み
// 計算量 O(n log(log(n)))

// 概要
// GCD 畳み込み：a,b を約数系の上位集合でゼータ変換 -> 両者の各項の積を取る -> 約数系の上位集合でメビウス変換
// LCM 畳み込み：a,b を約数系の下位集合でゼータ変換 -> 両者の各項の積を取る -> 約数系の下位集合でメビウス変換

// verified with
// https://atcoder.jp/contests/agc038/tasks/agc038_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Divisors_Zeta_Mobius.hpp"

template <typename T>
vector<T> gcd_convolve(vector<T> a, vector<T> b) {
    int n = a.size();
    assert((int)b.size() == n);
    divisors_zeta_transform(a, true), divisors_zeta_transform(b, true);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    divisors_mobius_transform(a, true);
    return a;
}

template <typename T>
vector<T> lcm_convolve(vector<T> a, vector<T> b) { // lcm(i, j) >= n の場合は a[i]*b[j] は c[0] に足される
    int n = a.size();
    assert((int)b.size() == n);
    divisors_zeta_transform(a, false), divisors_zeta_transform(b, false);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    divisors_mobius_transform(a, false);
    return a;
}
