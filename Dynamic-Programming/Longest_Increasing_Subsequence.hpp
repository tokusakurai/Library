#pragma once

// 最長増加部分列 (LIS)
// 計算量 O(n log(n))

// 概要
// dp[i][j] := 前から i 個の要素までみたとき、長さ j+1 の増加部分列での最終要素の最小値
// 配列 dp[i] と配列 dp[i+1] で値が異なる箇所は高々 1 個であるため、配列を使い回すことで計算量が落ちる。

// verified with
// https://judge.yosupo.jp/problem/longest_increasing_subsequence

#include <bits/stdc++.h>
using namespace std;

// strict：狭義単調増加か広義単調増加か
template <typename T>
vector<int> longest_increasing_subsequence(const vector<T> &a, bool strict) {
    int n = a.size();
    if (n == 0) return {};
    vector<int> dp, pre(n, -1);
    dp.reserve(n);
    auto comp = [&](int x, int y) { return a[x] < a[y]; };
    for (int i = 0; i < n; i++) {
        int t = (strict ? lower_bound(begin(dp), end(dp), i, comp) : upper_bound(begin(dp), end(dp), i, comp)) - begin(dp);
        if (t >= 1) pre[i] = dp[t - 1];
        if (t == (int)dp.size()) {
            dp.push_back(i);
        } else {
            dp[t] = i;
        }
    }
    vector<int> ret;
    ret.reserve(n);
    int i = dp.back();
    while (i != -1) {
        ret.push_back(i);
        i = pre[i];
    }
    reverse(begin(ret), end(ret));
    return ret;
}
