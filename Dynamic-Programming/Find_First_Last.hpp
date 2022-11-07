
// find first, find last
// 計算量 O(n)

// 概要
// dp[i] := a[j] > a[i] を満たすような最小の j > i とする。
// a[i+1] > a[i] なら dp[i] = i+1 である。そうでなければ、i+1 -> dp[i+1] -> dp[dp[i+1]] -> ... のようにして a[i] より大きい値が出てくるまでたどる。
// このとき、i -> dp[i] に沿って移動するのが全体で高々 1 回となるので、全体の計算量は O(n) となる。

// verified with
// https://codeforces.com/contest/1750/problem/E

#pragma once
#include <bits/stdc++.h>
using namespace std;

// 各 i について j > i かつ a[j] >(=) a[i] (a[j] <(=) a[i]) を満たすような最小の j を求める (存在しなければ n)
template <typename T>
vector<int> find_first(const vector<T> &a, bool greater = true, bool eq = false) {
    int n = a.size();
    vector<int> dp(n);
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = i + 1;
        while (dp[i] < n) {
            int j = dp[i];
            if (greater && a[j] > a[i]) break;
            if (!greater && a[j] < a[i]) break;
            if (eq && a[j] == a[i]) break;
            dp[i] = dp[j];
        }
    }
    return dp;
}

// 各 i について j < i かつ a[j] >(=) a[i] (a[j] <(=) a[i]) を満たすような最大の j を求める (存在しなければ -1)
template <typename T>
vector<int> find_last(const vector<T> &a, bool greater = true, bool eq = false) {
    int n = a.size();
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i] = i - 1;
        while (dp[i] >= 0) {
            int j = dp[i];
            if (greater && a[j] > a[i]) break;
            if (!greater && a[j] < a[i]) break;
            if (eq && a[j] == a[i]) break;
            dp[i] = dp[j];
        }
    }
    return dp;
}
