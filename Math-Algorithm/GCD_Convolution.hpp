
// 添字GCD畳み込み
// 計算量 O(N*log(N))

// 概要
// a,bを約数系の上位集合でゼータ変換⇒両者の各項の積を取る⇒約数系の上位集合でメビウス変換

// verified with
// https://atcoder.jp/contests/agc038/tasks/agc038_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
void divisors_zeta_transform(vector<T> &a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        a[i] += a[0];
        for (int j = 2 * i; j < n; j += i) a[i] += a[j];
    }
}

template <typename T>
void divisors_moboius_transform(vector<T> &a) {
    int n = a.size();
    for (int i = n - 1; i > 0; i--) {
        a[i] -= a[0];
        for (int j = 2 * i; j < n; j += i) a[i] -= a[j];
    }
}

template <typename T>
vector<T> gcd_convolve(vector<T> a, vector<T> b) {
    int n = a.size();
    assert((int)b.size() == n);
    divisors_zeta_transform(a), divisors_zeta_transform(b);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    divisors_moboius_transform(a);
    return a;
}
