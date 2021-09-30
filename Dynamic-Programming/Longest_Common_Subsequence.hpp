
// 最長共通部分列(LCS)
// 計算量 O(N*M)

// 概要
// dp[i][j] := aの前からi文字とbの前からj文字の最長共通部分列の長さ

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
int longest_common_subsequence(T a, T b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}
