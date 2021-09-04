
// Subproduct Tree
// 計算量 O(N*log(N)^2)
// 空間計算量 O(N*log(N))

// 概要
// 配列{x_1,x_2,...,x_N}が与えられたときに、(x-x_i)を最下段に並べて、多項式の積でセグメント木を作る。
// 各ノードに対応する多項式の次数の総和はO(N*log(N))なので、FFTを用いてO(N*log(N)^2)で構築できる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/FPS.hpp";

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