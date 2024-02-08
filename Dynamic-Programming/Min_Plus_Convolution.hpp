
// 任意数列と凸数列の (min,+) 畳み込み
// 計算量 O(n+m)

// 概要
// f(i,j) := a_j + b_{i-j} (index 外のときは infty) は monge なので、SMAWK アルゴリズムで各行最小値を計算できる。

// verified with
// https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Dynamic-Programming/SMAWK.hpp"

// b: 凸 (最大化の場合は凹)
template <typename T>
vector<T> min_plus_convolution(const vector<T> &a, const vector<T> &b, bool is_min = true) {
    int n = (int)a.size(), m = (int)b.size();

    for (int i = 1; i < m - 1; i++) {
        if (is_min) {
            assert(b[i] - b[i - 1] <= b[i + 1] - b[i]);
        } else {
            assert(b[i] - b[i - 1] >= b[i + 1] - b[i]);
        }
    }

    auto select = [&](int i, int j, int k) -> bool {
        if (i - j >= m) return true;
        if (i - k < 0) return false;
        return (a[j] + b[i - j] < a[k] + b[i - k]) xor is_min;
    };

    vector<int> c = SMAWK(n + m - 1, n, select);
    vector<T> ret(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) ret[i] = a[c[i]] + b[i - c[i]];
    return ret;
}
