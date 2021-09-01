
// 分割数テーブル
// 計算量 O(N*K)

// 概要
// dp[i][j] := i個の区別できない玉をj個の区別できない箱に分割する場合の数

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J&lang=jp

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<vector<T>> Partition_Number(int n, int k) { // 分割数P(n,k) := 整数nをちょうどk個の非負整数の和で表す方法(順序は区別しない)
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
