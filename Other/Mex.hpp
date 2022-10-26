
// mex (数列に現れない最小の非負整数)
// 計算量 O(n)

// 概要
// 数列のサイズを n とすると、mex は n 以下であるため、n 未満の整数が現れるかを持てばよい。

// verified with
// https://atcoder.jp/contests/abc272/tasks/abc272_e

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
int mex(vector<T> &v) {
    int n = v.size();
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++) {
        if (0 <= v[i] && v[i] < n) cnt[v[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) return i;
    }
    return n;
}
