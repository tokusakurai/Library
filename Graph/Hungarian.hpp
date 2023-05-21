
// Hungarian 法 (割り当て問題)
// 計算量 O(n^2m)

// 概要
// n×m 行列 a が与えられたときに、Σ[i=0,...,n-1] a[i][p[i]] を最小化するような配列 p を求める。(p の要素は相異なる)
// 上の行から 1 行ずつ追加していって、追加するごとに p を更新していく。
// 割り当て問題は重み付きマトロイド交差問題の一種であるので、補助グラフにおける最短路を O(nm) の dijkstra 法で求められる。
// 求めた最短路 (交互路) を使ってマッチングを更新する。

// verified with
// https://judge.yosupo.jp/problem/assignment

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
pair<T, vector<int>> hungarian(const vector<vector<T>> &a) {
    const T INF_T = numeric_limits<T>::max() / 2;
    if (a.empty()) return {0, {}};
    int n = a.size(), m = a[0].size();
    assert(n <= m);
    vector<T> u(n, 0), v(m + 1, 0);
    vector<int> p(m + 1, -1);
    for (int t = 0; t < n; t++) {
        p[m] = t;
        int j0 = m;
        vector<T> d(m + 1, INF_T);
        vector<int> pre(m + 1, -1);
        vector<bool> used(m + 1, false);
        while (j0 != -1 && p[j0] != -1) {
            used[j0] = true;
            int i0 = p[j0], j1 = -1;
            T delta = INF_T;
            for (int j = 0; j < m; j++) {
                if (used[j]) continue;
                T tmp = a[i0][j] - u[i0] - v[j];
                if (tmp < d[j]) d[j] = tmp, pre[j] = j0;
                if (d[j] < delta) delta = d[j], j1 = j;
            }
            for (int j = 0; j <= m; j++) {
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                d[j] -= delta;
            }
            j0 = j1;
        }
        while (j0 != m) {
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    vector<int> match(n, -1);
    for (int i = 0; i < m; i++) {
        if (p[i] != -1) match[p[i]] = i;
    }
    return {-v[m], match};
}
