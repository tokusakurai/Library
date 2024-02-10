#pragma once

// SMAWK アルゴリズム
// 計算量 O(n+m)

// 概要
// n*m 行列 A が totally monotone であるとは、A の任意の部分行列が monotone であることである。
// totally monotone な行に対して、以下の再帰アルゴリズムで各行の最小値を計算できる：
// 1. n < m の場合
//    reduce 操作を行い、行最小値が含まれる可能性がない列を消去する。これによって、列数は n 以下になる。
// 2. n >= m の場合
//    interpolate 操作を行う。すなわち、偶数行目だけ残して得られる行列に対して再帰的に行最小値を求め、
//    奇数行目については、上下の行の答えの間の行を全探索することで計算する。

// f が monge である、すなわち 1 <= i_1 < i_2 <= n, 1 <= j_1 < j_2 <= m ならば
// f(i_1, j_1) + f(i_2, j_2) <= f(i_1, j_2) + f(i_2, j_1) であるとき、(f(i,j))_{i,j} は totally monotone である。

// 参考文献
// http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf

#include <bits/stdc++.h>
using namespace std;

// select(i,j,k) := f(i,j) > f(i,k) or not (j < k)
template <typename F>
vector<int> SMAWK(int n, int m, const F &select) {
    if (n == 0) return {};
    assert(m >= 1);
    vector<int> row_minima(n);

    auto rec = [&](auto &&rec, const vector<int> &rows, const vector<int> &cols) -> void {
        int k = (int)rows.size(), l = (int)cols.size();
        if (k == 0) return;
        vector<int> survive_cols;
        survive_cols.reserve(k);
        for (int j = 0; j < l; j++) {
            while (!survive_cols.empty()) {
                int l = survive_cols.back();
                int i = (int)survive_cols.size() - 1;
                if (select(rows[i], l, cols[j])) {
                    survive_cols.pop_back();
                } else {
                    if (i < k - 1) survive_cols.push_back(cols[j]);
                    break;
                }
            }
            if (survive_cols.empty()) survive_cols.push_back(cols[j]);
        }
        vector<int> odd_rows;
        for (int i = 1; i < k; i += 2) odd_rows.push_back(rows[i]);
        rec(rec, odd_rows, survive_cols);
        int j = 0;
        for (int i = 0; i < k; i += 2) {
            int best_col = survive_cols[j];
            int right_col = (i == k - 1 ? survive_cols.back() : row_minima[rows[i + 1]]);
            while (survive_cols[j] < right_col) {
                j++;
                if (select(rows[i], best_col, survive_cols[j])) best_col = survive_cols[j];
            }
            row_minima[rows[i]] = best_col;
        }
    };

    vector<int> rows(n), cols(m);
    for (int i = 0; i < n; i++) rows[i] = i;
    for (int j = 0; j < m; j++) cols[j] = j;
    rec(rec, rows, cols);
    return row_minima;
}
