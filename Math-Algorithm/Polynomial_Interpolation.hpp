
// ラグランジュ補間（多項式）
// 計算量 O(n log(n)^2)
// 空間計算量 O(n log(n))

// 概要
// f(x_1) = y_1, f(x_2) = y_2,..., f(x_n) = y_n が与えられているときに、n-1 次以下の多項式 f(x) を求める。
// h(x) = (x-x_1)(x-x_2)...(x-x_n) とすると、h'(x) = Σ[0<=i<m]Π[j!=i](x-x_j) であるから、
// 因数定理より h'(x) を x-x_i で割った余りは Π[j!=i](x_i-x_j) となる。
// この余りは Multipoint Evaluation の要領で求められ、さらに Subproduct Tree を使うことで答えを求めることができる。

// verified with
// https://judge.yosupo.jp/problem/polynomial_interpolation

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Subproduct_Tree.hpp"

template <typename T>
Formal_Power_Series<T> polynomial_interpolation(const vector<T> &xs, const vector<T> &ys) {
    int n = xs.size();
    assert(ys.size() == n);
    vector<Formal_Power_Series<T>> g = subproduct_tree(xs);
    int k = g.size() / 2;
    vector<Formal_Power_Series<T>> f(2 * k);
    f[1] = g[1].diff();
    for (int i = 2; i < k + n; i++) f[i] = f[i / 2] % g[i];
    for (int i = 0; i < n; i++) f[k + i][0] = ys[i] / f[k + i][0];
    for (int i = k - 1; i > 0; i--) f[i] = f[2 * i] * g[2 * i + 1] + f[2 * i + 1] * g[2 * i];
    f[1].resize(n);
    return f[1];
}
