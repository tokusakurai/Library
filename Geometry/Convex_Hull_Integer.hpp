#pragma once

// 凸包 (整数)
// 計算量 O(n log(n))

// 概要
// 全ての頂点の座標が整数の場合の凸包。

// verified with
// https://judge.yosupo.jp/problem/static_convex_hull
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=ja
// https://atcoder.jp/contests/ttpc2022/tasks/ttpc2022_f

#include <bits/stdc++.h>
using namespace std;

template <typename S, typename T>
pair<S, T> operator-(const pair<S, T> &p, const pair<S, T> &q) {
    return make_pair(p.first - q.first, p.second - q.second);
}

template <typename T>
int det_sgn(const pair<T, T> &p, const pair<T, T> &q) {
    // T x = p.first * q.second - p.second * q.first;
    __int128_t x = __int128_t(p.first) * q.second - __int128_t(p.second) * q.first;
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

// 下側凸包 (左から)
template <typename T>
vector<pair<T, T>> lower_convex_hull(vector<pair<T, T>> p) {
    sort(begin(p), end(p));
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n <= 1) return p;
    vector<pair<T, T>> ch(n);
    for (int i = 0; i < n; i++) {
        if (k == 1 && ch[0].first == p[i].first) {
            if (ch[0].second > p[i].second) ch[0] = p[i];
            continue;
        }
        while (k >= 2 && det_sgn(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) <= 0) k--;
        ch[k++] = p[i];
    }
    if (k >= 2 && ch[k - 1].first == ch[k - 2].first) k--;
    ch.resize(k);
    return ch;
}

// 上側凸包 (左から)
template <typename T>
vector<pair<T, T>> upper_convex_hull(vector<pair<T, T>> p) {
    sort(begin(p), end(p));
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n <= 1) return p;
    vector<pair<T, T>> ch(n);
    for (int i = 0; i < n; i++) {
        if (k == 1 && ch[0].first == p[i].first) {
            if (ch[0].second < p[i].second) ch[0] = p[i];
            continue;
        }
        while (k >= 2 && det_sgn(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) >= 0) k--;
        ch[k++] = p[i];
    }
    if (k >= 2 && ch[k - 1].first == ch[k - 2].first) k--;
    ch.resize(k);
    return ch;
}

template <typename T>
vector<pair<T, T>> convex_hull(vector<pair<T, T>> p) {
    sort(begin(p), end(p));
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n <= 1) return p;
    vector<pair<T, T>> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && det_sgn(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) <= 0) k--;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && det_sgn(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) <= 0) k--;
    }
    ch.resize(k - 1);
    return ch;
}
