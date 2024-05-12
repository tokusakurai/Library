#pragma once

// F2 ベクトル空間 (整数で表現) における基底、2 つの空間の共通部分の基底計算
// 計算量 基底：O(nd)、共通空間の基底：O((n+m)d) (d はベクトル空間の次元)

// 概要
// 基底 (列ベクトル) を横に並べた行列 U,V で張られる空間の共通部分に z が含まれる条件は以下のように書ける：
// ある x,y が存在して、Ux = Vy = z
// 従って、行列 [U -V] の右カーネルの基底 (x_i,y_i) を求めると、共通空間の基底は Ux_i となる。

// verified with
// https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces

#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> F2_basis(const vector<T> &a) {
    vector<T> basis;
    for (auto e : a) {
        for (auto b : basis) e = min(e, e ^ b);
        if (e > 0) basis.push_back(e);
    }
    return basis;
}

template <typename T>
vector<T> F2_vector_space_intersection(vector<T> a, vector<T> b) {
    a = F2_basis(a), b = F2_basis(b);
    int n = a.size(), m = b.size();
    vector<T> c(m);
    vector<T> basis;
    for (int k = 0; k < m; k++) {
        T e = b[k], f = 0;
        for (int i = 0; i < n; i++) {
            if (e > (e ^ a[i])) {
                e = e ^ a[i];
                f ^= a[i];
            }
        }
        for (int j = 0; j < k; j++) {
            if (e > (e ^ b[j])) {
                e = e ^ b[j];
                f ^= c[j];
            }
        }
        b[k] = e, c[k] = f;
        if (e == 0) basis.push_back(f);
    }
    return basis;
}
