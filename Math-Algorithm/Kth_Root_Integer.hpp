
// K乗根(整数)
// 計算量 O(K*log(A))

// 概要
// 整数A,KがA>=0,K>0を満たすとき、floor(A^(1/K))を二分探索で求める。

// verified with
// https://judge.yosupo.jp/problem/kth_root_integer

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T kth_root_integer(T a, int k) {
    if (k == 1) return a;
    auto check = [&](T x) {
        T mul = 1;
        for (int j = 0; j < k; j++) {
            if (__builtin_mul_overflow(mul, x, &mul)) return false;
        }
        return mul <= a;
    };
    int n = 4 * sizeof(T);
    T ret = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (check(ret | (T(1) << i))) ret |= T(1) << i;
    }
    return ret;
}
