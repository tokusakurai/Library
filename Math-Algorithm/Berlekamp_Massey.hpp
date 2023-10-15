
// Berlekamp-Massey のアルゴリズム (線形漸化式で得られる数列の先頭 n 項が与えられたとき、それを与える階数最小の線形漸化式を求める)
// 計算量 O(n^2)

// 概要
// 数列を先頭から見ていき、逐次的に線形漸化式を更新していく。
// 更新する際に、より先頭の少ない項で条件をみたす漸化式を使うことができる。
// d 階線形漸化式で得られる数列の先頭 2d 項が与えられた場合、正しく線形漸化式を求めることが出来る。

// verified with
// https://judge.yosupo.jp/problem/find_linear_recurrence

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> Berlekamp_Massey(const vector<T> &a) {
    int n = a.size();
    vector<T> c = {-1}, c_pre = {0};
    int i_pre = -1;
    T x_pre = 1;
    for (int i = 0; i < n; i++) {
        int d = c.size(), d_pre = c_pre.size();
        T x = 0;
        for (int j = 0; j < d; j++) x += a[i - j] * c[j];
        if (x == 0) continue;
        T coef = -x / x_pre;
        if (d >= d_pre + i - i_pre) {
            for (int j = 0; j < d_pre; j++) c[i - i_pre + j] += coef * c_pre[j];
        } else {
            vector<T> memo = c;
            c.resize(d_pre + i - i_pre);
            for (int j = 0; j < d_pre; j++) { c[i - i_pre + j] += coef * c_pre[j]; }
            c_pre = memo, i_pre = i, x_pre = x;
        }
    }
    return c;
}
