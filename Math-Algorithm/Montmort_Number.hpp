
// モンモール数(完全順列の個数)のテーブル
// 計算量 O(N)

// 概要
// 求める数列をa_0,a_1,...とすると、1番目の要素にxを割り当てたとしてx番目の要素が1かどうかで場合分けすると、
// a_n = (n-1)(a_{n-1}+a_{n-2})の漸化式が得られる。

// verified with
// https://judge.yosupo.jp/problem/montmort_number_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> Montmort_Number(int n) {
    vector<T> ret(n + 1);
    ret[0] = T(1), ret[1] = T(0);
    for (int i = 2; i <= n; i++) ret[i] = T(i - 1) * (ret[i - 1] + ret[i - 2]);
    return ret;
}
