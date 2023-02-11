
// 凸包 (整数)
// 計算量 O(n log(n))

// 概要
// 全ての頂点の座標が整数の場合の凸包。

// verified with
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<pair<T, T>> convex_hull_integer(vector<pair<T, T>> p) {
    sort(begin(p), end(p));
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n == 1) return p;
    vector<pair<T, T>> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2) {
            T x1 = ch[k - 1].first - ch[k - 2].first, y1 = ch[k - 1].second - ch[k - 2].second;
            T x2 = p[i].first - ch[k - 1].first, y2 = p[i].second - ch[k - 1].second;
            // if (x1 * y2 - x2 * y1 > 0) break;
            if (__int128_t(x1) * y2 - __int128_t(x2) * y1 > 0) break;
            k--;
        }
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t) {
            T x1 = ch[k - 1].first - ch[k - 2].first, y1 = ch[k - 1].second - ch[k - 2].second;
            T x2 = p[i].first - ch[k - 1].first, y2 = p[i].second - ch[k - 1].second;
            // if (x1 * y2 - x2 * y1 > 0) break;
            if (__int128_t(x1) * y2 - __int128_t(x2) * y1 > 0) break;
            k--;
        }
    }
    ch.resize(k - 1);
    return ch;
}
