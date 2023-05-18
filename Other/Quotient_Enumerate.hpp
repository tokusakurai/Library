
// floor(n/i), ceil(n/i) (1<=i<=n) を列挙する
// 計算量 O(√n)

// 概要
// floor(n/i) = x を満たすような 1<=i<=n が存在する x について、x と i の範囲 [l,r) を格納する。
// 実際には ((l,r),x) の組が l の昇順で格納される。
// floor(n/i) = x ⇔ x<= n/i < x+1 ⇔ n/(x+1) < i <= n/x ⇔ floor(n/(x+1)) < i <= floor(n/x)
// ceil(n/i) = x ⇔ x-1 < n/i <= x ⇔ n/x <= i < n/(x-1) ⇔ ceil(n/x) <= i < ceil(n/(x-1))

// verified with
// https://judge.yosupo.jp/problem/enumerate_quotients
// https://atcoder.jp/contests/abc230/tasks/abc230_e
// https://atcoder.jp/contests/arc150/tasks/arc150_b

#pragma once
#include <bits/stdc++.h>
using namespace std;

// (x,l,r)
template <typename T>
vector<tuple<T, T, T>> quotient_floor_enumerate(T n) {
    vector<tuple<T, T, T>> ret;
    for (T l = 1; l <= n;) {
        T x = n / l;
        T r = n / x + 1;
        ret.emplace_back(x, l, r);
        l = r;
    }
    return ret;
}

// (x,l,r)
template <typename T>
vector<tuple<T, T, T>> quotient_ceil_enumerate(T n) {
    vector<tuple<T, T, T>> ret;
    for (T l = 1; l <= n;) {
        T x = (n + l - 1) / l;
        T r = (x == 1 ? n + 1 : (n + x - 2) / (x - 1));
        ret.emplace_back(x, l, r);
        l = r;
    }
    return ret;
}