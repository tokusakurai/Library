
// 偏角ソート
// 計算量 O(n log(n))

// 概要
// 点を arctan で偏角（∈(-π,π]）ソートする。
// ただし、(0,0) の偏角は 0 とする。

// verified with
// https://judge.yosupo.jp/problem/sort_points_by_argument

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
int type(pair<T, T> p) {
    if (p.first == 0 && p.second == 0) return 0;
    if (p.second < 0 || (p.second == 0 && p.first > 0)) return -1;
    return 1;
}

template <typename T>
bool compare_arg(pair<T, T> p, pair<T, T> q) {
    int a = type(p), b = type(q);
    if (a != b) return a < b;
    return p.first * q.second > q.first * p.second;
}

template <typename T>
void sort_arg(vector<pair<T, T>> &p) {
    sort(begin(p), end(p), compare_arg<T>);
}
