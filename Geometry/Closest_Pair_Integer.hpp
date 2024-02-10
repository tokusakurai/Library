#pragma once

// 最近点対 (整数)
// 計算量 O(n log(n))

// 概要
// 全ての頂点の座標が整数の場合の最近点対 (距離の 2 乗を求める)。

// verified with
// https://codeforces.com/contest/429/problem/D

#include <bits/stdc++.h>
using namespace std;

template <typename T>
T closest_pair_integer(vector<pair<T, T>> p) {
    const T INF_T = numeric_limits<T>::max() / 2;
    int n = p.size();
    if (n == 0) return INF_T;
    sort(begin(p), end(p));
    vector<pair<T, T>> memo(n);

    function<T(int, int)> rec = [&](int l, int r) {
        if (r - l == 1) return INF_T;
        int m = (l + r) / 2;
        T x = p[m].first;
        T ret = min(rec(l, m), rec(m, r));
        inplace_merge(begin(p) + l, begin(p) + m, begin(p) + r, [](pair<T, T> p1, pair<T, T> p2) {
            if (p1.second != p2.second) return p1.second < p2.second;
            return p1.first < p2.first;
        });
        int cnt = 0;
        for (int i = l; i < r; i++) {
            T d = p[i].first - x;
            if (d * d >= ret) continue;
            for (int j = 0; j < cnt; j++) {
                T dx = p[i].first - memo[cnt - j - 1].first;
                T dy = p[i].second - memo[cnt - j - 1].second;
                if (dy * dy >= ret) break;
                ret = min(ret, dx * dx + dy * dy);
            }
            memo[cnt++] = p[i];
        }
        return ret;
    };

    return rec(0, n);
}
