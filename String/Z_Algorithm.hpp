#pragma once

// z-algorithm (文字列 S と S の i 文字目 (0-indexed) 以降の最長共通接頭辞の長さを記録した配列を求める)
// 計算量 O(|S|)

// 概要
// 求める配列を A とする。
// j + A[j] < A[i] ならば A[j] = A[j + i] となる。j + A[j] >= A[i] の場合でもはみ出た部分だけまた判定し直せばよい。

// verified with
// https://atcoder.jp/contests/jag2013summer-day3/tasks/icpc2013summer_day3_h
// https://judge.yosupo.jp/problem/zalgorithm

#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<int> z_algorithm(const T &s) {
    int n = s.size();
    vector<int> ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && s[j] == s[i + j]) j++;
        ret[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < n && k + ret[k] < j) ret[i + k] = ret[k], k++;
        i += k, j -= k;
    }
    return ret;
}
