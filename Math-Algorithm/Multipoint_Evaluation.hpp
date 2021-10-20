
// 多点評価
// 計算量 O(n log(n)^2)
// 空間計算量 O(n log(n))

// 概要
// n次多項式f(x)が与えられたとき、与えられたn点(x_1,x_2,..,x_n)についてf(x_i)を求める。
// 因数定理より、fを(x-x_i)で割った余りを求めれば良い。
// xsでSubproduct Treeを構築し、上から順に余りを求めれば全ての答えを割り出せる。

// verified with
// https://judge.yosupo.jp/problem/multipoint_evaluation

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Subproduct_Tree.hpp"

template <typename T>
vector<T> multipoint_evaluation(const Formal_Power_Series<T> &f, const vector<T> &xs) {
    vector<Formal_Power_Series<T>> g = subproduct_tree(xs);
    int n = xs.size(), k = g.size() / 2;
    g[1] = f % g[1];
    for (int i = 2; i < k + n; i++) g[i] = g[i / 2] % g[i];
    vector<T> ys(n);
    for (int i = 0; i < n; i++) ys[i] = g[k + i].empty() ? 0 : g[k + i][0];
    return ys;
}
