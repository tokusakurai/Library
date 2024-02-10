#pragma once

// monotone minima
// 計算量 O(n + m log(n))

// 概要
// n*m 行列 A が monotone であるとは、
// c_i = argmin{j | a_{ij}} (複数ある場合はその中で最小値) が c_0 <= c_1 <= ... <= c_{n-1} を満たすことである。
// monotone な f に対して、行で分割統治することで各 c_i の計算を高速化できる。

#include <bits/stdc++.h>
using namespace std;

// select(i,j,k) := f(i,j) > f(i,k) or not (j < k)
template <typename F>
vector<int> monotone_minima(int n, int m, const F &select) {
    if (n == 0) return {};
    assert(m >= 1);
    vector<int> row_minima(n);

    auto rec = [&](auto &&rec, int lx, int rx, int ly, int ry) -> void {
        if (lx == rx) return;
        int x = (lx + rx) / 2;
        int y_opt = ly;
        for (int y = ly + 1; y < ry; y++) {
            if (select(x, y_opt, y)) y_opt = y;
        }
        row_minima[x] = y_opt;
        rec(rec, lx, x, ly, y_opt + 1);
        rec(rec, x + 1, rx, y_opt, ry);
    };

    rec(rec, 0, n, 0, m);
    return row_minima;
}
