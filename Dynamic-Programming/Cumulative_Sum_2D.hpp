
// 2 次元累積和
// 計算量 構築：O(nm)、imos 法を用いた加算・長方形和クエリ：O(1)

// 概要
// 各要素について自分より左上の要素の和を累積和 dp で求める。

// verified with
// https://atcoder.jp/contests/typical90/tasks/typical90_ab

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Cumulative_Sum_2D {
    vector<vector<T>> v;
    const int n, m;

    Cumulative_Sum_2D(const vector<vector<T>> &v) : v(v), n((int)v.size()), m((int)v[0].size()) {}

    Cumulative_Sum_2D(int n, int m) : v(n, vector<T>(m, 0)), n(n), m(m) {}

    // 累積和を構築
    void build() {
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) v[i][j] += v[i][j - 1];
        }
        for (int j = 0; j < m; j++) {
            for (int i = 1; i < n; i++) v[i][j] += v[i - 1][j];
        }
    }

    // 区間 [lx,rx) × [ly,ry) に imos 法で加算
    void add(int lx, int ly, int rx, int ry, T x) {
        lx = max(lx, 0), ly = max(ly, 0), rx = min(rx, n), ry = min(ry, m);
        if (rx <= lx || ry <= ly) return;
        v[lx][ly] += x;
        if (rx < n) v[rx][ly] -= x;
        if (ry < m) v[lx][ry] -= x;
        if (rx < n && ry < m) v[rx][ry] += x;
    }

    T fold(int a, int b) { return (a <= 0 || b <= 0 ? 0 : v[min(a, n) - 1][min(b, m) - 1]); }

    // 区間 [lx,rx) × [ly,ry) の総和
    T sum(int lx, int ly, int rx, int ry) {
        lx = max(lx, 0), ly = max(ly, 0), rx = min(rx, n), ry = min(ry, m);
        if (rx <= lx || ry <= ly) return 0;
        return fold(lx, ly) - fold(rx, ly) - fold(lx, ry) + fold(rx, ry);
    }
};
