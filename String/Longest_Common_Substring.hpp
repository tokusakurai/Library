
// 最長共通 (連続) 部分文字列
// 計算量 O(|S|+|T|)

// 概要
// 文字列 S+'$'+T の接尾辞配列 sa と高さ配列 lcp を構築する。
// sa[i], sa[i+1] の片方が S 由来でもう片方が T 由来であるような i の中で、lcp[i] の最大値が最長共通部分文字列の長さに相当する。

// verified with
// https://atcoder.jp/contests/arc151/tasks/arc151_e

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../String/Suffix_Array.hpp"

// s,t の最長共通 (連続) 部分列が s[i:i+l), t[j:j+l) となるような (l,i,j) の組を返す
template <typename T = string>
tuple<int, int, int> longest_common_substring(const T &s, const T &t) {
    int n = s.size(), m = t.size();
    if (n == 0 || m == 0) return make_tuple(0, 0, 0);
    T v(n + m + 1, 0);
    for (int i = 0; i < n; i++) v[i] = s[i];
    v[n] = min(*min_element(begin(s), end(s)), *min_element(begin(t), end(t))) - 1;
    for (int i = 0; i < m; i++) v[n + 1 + i] = t[i];
    Suffix_Array<T> sa(v);
    Longest_Common_Prefix_Array<T> lcp(sa);
    int len = 0;
    for (int i = 0; i < n + m; i++) {
        int x = sa[i], y = sa[i + 1];
        if (x > y) swap(x, y);
        if (x < n && n < y) len = max(len, lcp[i]);
    }
    int ls = -1, lt = -1;
    for (int i = 0; i < n + m - 1; i++) {
        int x = sa[i], y = sa[i + 1];
        if (x > y) swap(x, y);
        if (x < n && n < y && len == lcp[i]) {
            ls = x, lt = y - n - 1;
            break;
        }
    }
    return make_tuple(len, ls, lt);
}
