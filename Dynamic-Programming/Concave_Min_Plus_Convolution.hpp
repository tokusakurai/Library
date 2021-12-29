
// 凸数列の (min,+) 畳み込み
// 計算量 O(n+m)

// 概要
// 数列 a[0],a[1],...,a[n-1] と数列 b[0],b[1],...,b[m-1] が（下に）凸であるとき、
// 各 k に対して c[k] := min{a[i]+b[j]|i+j = k} を求める。
// c[k] = a[i]+b[j], i+j = k となるような (i,j) が取れるとき、c[k+1] = min(a[i+1]+b[j],a[i]+b[j+1]) となる。

// verified with
// https://atcoder.jp/contests/abc218/tasks/abc218_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> concave_min_plus_convolve(const vector<T> &a, const vector<T> &b, const T &e, bool is_min = true) {
    int n = a.size(), m = b.size();
    vector<T> c(n + m - 1, e);
    int la = n, ra = -1, lb = m, rb = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != e) la = min(la, i), ra = max(ra, i);
    }
    for (int i = 0; i < m; i++) {
        if (b[i] != e) lb = min(lb, i), rb = max(rb, i);
    }
    if (la == n || lb == m) return c;
    int pi = la, pj = lb;
    for (int i = la + lb; i <= ra + rb; i++) {
        c[i] = (a[pi] == e || b[pj] == e ? e : a[pi] + b[pj]);
        if (pi == ra) {
            pj++;
        } else if (pj == rb) {
            pi++;
        } else {
            (is_min ^ (a[pi + 1] + b[pj] > a[pi] + b[pj + 1]) ? pi : pj)++;
        }
    }
    return c;
}
