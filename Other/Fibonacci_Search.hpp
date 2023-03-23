
// フィボナッチ探索
// 計算量 O(log(R-L))

// verified with
// https://atcoder.jp/contests/tupc2022/tasks/tupc2022_k

// 概要
// f : Z -> Z について、[L,R] における極小 (極大) 点を 1 つ求める。
// アルゴリズムの任意のステップで、[a,b] における f の最小値を y とすると、
// 1. ある a < x < b について、f(x) = y
// 2. f(a) = y かつ a = L
// 3. f(b) = y かつ b = R
// のいずれかが成立する。

#pragma once
#include <bits/stdc++.h>
using namespace std;

// C は座標の型
// [L, R] での f の極小値を 1 つ見つける
template <typename T, typename C, typename F>
pair<C, T> Fibonacci_search(const F &f, C L, C R, bool is_min = true) {
    assert(L <= R);
    C a = L, b = L + 1, c = L + 2, d = L + 3;
    while (d < R) b = c, c = d, d = c + (b - a);

    auto get = [&](C x) {
        if (x > R) return numeric_limits<T>::max() / 2;
        return is_min ? f(x) : -f(x);
    };

    T ya = get(a), yb = get(b), yc = get(c), yd = get(d);
    while (d - a > 3) {
        if (yb < yc) {
            d = c, c = b, b = a + (d - c);
            yd = yc, yc = yb, yb = get(b);
        } else {
            a = b, b = c, c = d - (b - a);
            ya = yb, yb = yc, yc = get(c);
        }
    }
    C x = b;
    T y = yb;
    if (yc < y) x = c, y = yc;
    if (ya < y) x = a, y = ya;
    if (yd < y) x = d, y = yd;
    return make_pair(x, is_min ? y : -y);
};
