
// Range Add Range Sum
// 計算量 構築：O(n)、区間加算・区間和取得：O(log(n))
// 空間計算量 O(n)

// 概要
// 区間加算すると、累積和の変化は部分的な一次関数の形になる。
// 定数項と一次の項をそれぞれ imos 法で管理することで実現できる。

// verified with
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "Binary_Indexed_Tree.hpp"

template <typename T>
struct Range_Add_Range_Sum {
    Binary_Indexed_Tree<T> bit0, bit1;
    const int n;

    Range_Add_Range_Sum(const vector<T> &v) : n(v.size()), bit0(v), bit1(v.size(), 0) {}

    Range_Add_Range_Sum(int n, const T &x) : Range_Add_Range_Sum(vector<T>(n, x)) {}

    void add(int l, int r, const T &x) {
        l = max(l, 0), r = min(r, n);
        if (l >= r) return;
        bit0.add(l, -x * T(l)), bit1.add(l, x);
        if (r < n) bit0.add(r, x * T(r)), bit1.add(r, -x);
    }

    T sum(int i) const {
        i = min(i, n);
        if (i < 0) return 0;
        return bit0.sum(i) + bit1.sum(i) * T(i);
    }

    T query(int l, int r) const {
        l = max(l, 0), r = min(r, n);
        if (l >= r) return 0;
        return sum(r) - sum(l);
    }
};
