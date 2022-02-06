
// テトレーション（mod）
// 計算量 O(√m)

// 概要
// x^^n := 1 (n = 0), x^(x^^(n-1)) (n >= 1) として再帰的に定義される。
// n >= φ(m) であるとき、x^n ≡ x^(φ(m)+n%φ(m)) が成立する。
// 演算の結果で M 以上になったかのフラグを持っておけば x^n のループに入っているかどうかを確認できる。
// φ(m) >= ceil(log_2(m)) であることから、一度フラグが立ったら常に立っているとしていい。
// ただし、x = 0,1 は場合分けする必要がある。
// m <- φ(m) を 2 回行うと m は半分以下になることから計算量は O(√m) と評価できる。

// verified with
// https://judge.yosupo.jp/problem/tetration_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Factor_Ring.hpp"

long long modpow(long long x, long long n, const int &m, int &flag) { // 答えが m 以上になるなら flag を立てる
    long long ret = 1;
    for (; n > 0; n >>= 1, x *= x, x %= m) {
        if (n & 1) {
            ret *= x;
            if (ret >= m) flag = 1, ret %= m;
        }
    }
    return ret;
}

long long modtetration(const long long &x, const long long &n, const int &m, int &flag) { // flag が立っていれば x^n は周期に入っている (n >= φ(m))
    if (m == 1) return flag = 1;
    if (x == 0) return (n & 1 ? 0 : 1);
    if (x == 1 || n == 0) return 1;
    if (n == 1) {
        if (x >= m) flag = 1;
        return x % m + flag * m;
    }
    long long tmp = modtetration(x, n - 1, Euler_totient(m), flag);
    long long ret = modpow(x, tmp, m, flag);
    return ret + flag * m;
}

long long modtetration(const long long &x, const long long &n, const int &m) {
    int flag = 0;
    return modtetration(x, n, m, flag) % m;
}
