
// サイズ n の集合からからサイズ k の部分集合を全列挙する
// 計算量 O(C(n,k))

// 概要
// サイズ k の部分集合を辞書順で小さいものから 1 個ずつ順に列挙する。

// verified with
// https://atcoder.jp/contests/cpsco2019-s1/tasks/cpsco2019_s1_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T next_combination(T comb) { // comb の辞書順で次に大きい部分集合を求める
    assert(comb > 0);
    T x = comb & (-comb), y = comb + x, z = comb & (~y);
    return ((z / x) >> 1) | y;
}
