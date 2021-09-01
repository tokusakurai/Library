
// ラグランジュ補間(多項式)
// 計算量 O(N*log(N)^2)
// 空間計算量 O(N*log(N))

// 概要
// f(x_1) = y_1, f(x_2) = y_2,..., f(x_N) = y_Nが与えられているときに、(N-1)次多項式f(x)を求める。
// h(x) = (x-x_1)(x-x_2)...(x_x_N)とすると、h'(x) = Σ{Π(x-x_j)(j≠i)}であるから、
// 因数定理よりh'(x)を(x-x_i)で割った余りはΠ(x_i-x_j)(j≠i)となる。
// この余りはMultipoint Evaluationの要領で求められ、さらにSubtree Productを使うことで答えを求めることができる。

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
