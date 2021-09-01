
// 最長増加部分列(LIS)
// 計算量 O(N*log(N))

// 概要
// dp[i][j] := 前からi個の要素までみたとき、長さj+1の増加部分列での最終要素の最小値
// 配列dp[i]と配列dp[i+1]で値が異なる箇所は高々1個であるため、配列を使い回すことで計算量が落ちる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
int longest_increasing_subsequence(const vector<T> &a, bool strict) { // strict : 狭義単調増加か広義単調増加か
    vector<T> dp;
    for (auto &e : a) {
        typename vector<T>::iterator it;
        if (strict)
            it = lower_bound(begin(dp), end(dp), e);
        else
            it = upper_bound(begin(dp), end(dp), e);
        if (it == end(dp))
            dp.push_back(e);
        else
            *it = e;
    }
    return dp.size();
}
