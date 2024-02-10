#pragma once

// 多角形 (面積、内外判定)
// 計算量 面積、多角形の内外判定：O(n)、凸多角形の内外判定：O(log(n))

// 概要
// 面積：多角形を複数の三角形に分割し、符号付き面積を計算する。
// 内外判定：半直線を引いて多角形の辺との交差回数の偶奇を調べる。
// 凸多角形の内外判定：多角形を n-2 個の三角形に分割し、そのどれに含まれるかを二分探索する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A&lang=ja
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C&lang=ja
// https://atcoder.jp/contests/abc296/tasks/abc296_g

#include <bits/stdc++.h>
using namespace std;

template <typename S, typename T>
pair<S, T> operator-(const pair<S, T> &p, const pair<S, T> &q) {
    return make_pair(p.first - q.first, p.second - q.second);
}

template <typename T>
T det(const pair<T, T> &p, const pair<T, T> &q) {
    T x = p.first * q.second - p.second * q.first;
    return x;
}

template <typename T>
int det_sgn(const pair<T, T> &p, const pair<T, T> &q) {
    T x = p.first * q.second - p.second * q.first;
    //__int128_t x = __int128_t(p.first) * q.second - __int128_t(p.second) * q.first;
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

template <typename T>
int dot_sgn(const pair<T, T> &p, const pair<T, T> &q) {
    T x = p.first * q.first + p.second * q.second;
    //__int128_t x = __int128_t(p.first) * q.first + __int128_t(p.second) * q.second;
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

// 面積の 2 倍
template <typename T>
T area(const vector<pair<T, T>> &p) {
    T ret = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) ret += det(p[i], p[(i + 1) % n]);
    return abs(ret);
}

// IN:2, ON:1, OUT:0
// 反時計回り、O(n)
template <typename T>
int in_polygon(const vector<pair<T, T>> &p, const pair<T, T> &q) {
    int n = p.size();
    int ret = 0;
    for (int i = 0; i < n; i++) {
        pair<T, T> a = p[i] - q, b = p[(i + 1) % n] - q;
        if (det_sgn(a, b) == 0 && dot_sgn(a, b) <= 0) return 1;
        if (a.second > b.second) swap(a, b);
        if (a.second <= 0 && b.second > 0 && det_sgn(a, b) == 1) ret ^= 2;
    }
    return ret;
}

// IN:2, ON:1, OUT:0
// 反時計回り、凸多角形、O(log n)
template <typename T>
int in_convex_polygon(const vector<pair<T, T>> &p, pair<T, T> q) {
    int n = p.size();
    assert(n >= 3);
    int b1 = det_sgn(p[1] - p[0], q - p[0]);
    int b2 = det_sgn(p[n - 1] - p[0], q - p[0]);
    if (b1 < 0 || b2 > 0) return 0;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        (det_sgn(p[m] - p[0], q - p[0]) >= 0 ? l : r) = m;
    }
    int v = det_sgn(p[l] - q, p[r] - q);
    return v == 0 ? 1 : v > 0 ? (b1 == 0 || b2 == 0 ? 1 : 2) : 0;
}
