#pragma once

// 分割数テーブル
// 計算量 O(nk)

// 概要
// dp[i][j] := i 個の区別できない玉を j 個の区別できない箱に分割する場合の数

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J&lang=jp

#include <bits/stdc++.h>
using namespace std;

// 分割数 P(n,k) := 整数 n をちょうど k 個の非負整数の和で表す方法 (順序は区別しない)
template <typename T>
vector<vector<T>> Partition_Number(int n, int k) {
    vector<vector<T>> dp(n + 1, vector<T>(k + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = dp[i][j - 1];
            if (i >= j) dp[i][j] += dp[i - j][j];
        }
    }
    return dp;
}
