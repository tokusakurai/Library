#pragma once

// Subproduct Tree
// 計算量 O(n log(n)^2)
// 空間計算量 O(n log(n))

// 概要
// 数列 (x_1,x_2,...,x_n) が与えられたときに、x-x_i を最下段に並べて、多項式の積でセグメント木を作る。
// 各ノードに対応する多項式の次数の総和は O(n log(n)) なので、FFT を用いて O(n log(n)^2) で構築できる。

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Formal_Power_Series.hpp"

template <typename T>
vector<Formal_Power_Series<T>> subproduct_tree(const vector<T> &xs) {
    int n = xs.size();
    int k = 1;
    while (k < n) k <<= 1;
    vector<Formal_Power_Series<T>> g(2 * k, {1});
    for (int i = 0; i < n; i++) g[k + i] = {-xs[i], 1};
    for (int i = k - 1; i > 0; i--) g[i] = g[2 * i] * g[2 * i + 1];
    return g;
}
