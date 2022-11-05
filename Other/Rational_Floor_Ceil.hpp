
// 有理数の floor・ceil
// 計算量 O(1)

// 概要
// floor(x / y) = x / y (x >= 0), (x - y + 1) / y (x < 0)
// ceil(x / y) = (x + y - 1) / y (x >= 0), x / y (x < 0)

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T floor_rational(T x, T y) {
    assert(y != 0);
    if (y < 0) x = -x, y = -y;
    return (x >= 0 ? x / y : (x - y + 1) / y);
}

template <typename T>
T ceil_rational(T x, T y) {
    assert(y != 0);
    if (y < 0) x = -x, y = -y;
    return (x >= 0 ? (x + y - 1) / y : x / y);
}
