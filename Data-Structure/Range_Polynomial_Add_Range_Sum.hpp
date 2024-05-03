#pragma once

// 区間 k 次多項式加算・区間和
// 計算量 構築：O(nk)、区間加算・区間和取得：O(nk^2 + nk log(n))
// 空間計算量 O(nk)

// 概要
// k 次多項式 f が与えられたとき、i ∈ [l,r) について a[i] に f(i) を加算
// n^k を binom{n,k}, binom{n,k-1}, ..., binom{n,0} の線形和で表す。これは第二種スターリング数を用いることで変換できる。
// ∑[0<=i<n] binom{i,k} = binom{n,k+1} を利用して、k+2 個の bit で総和を管理する。
// k 個目の bit は binom{i,k} の係数に相当している。

// verified with
// https://codeforces.com/contest/1924/problem/B

#include <bits/stdc++.h>
using namespace std;

#include "Binary_Indexed_Tree.hpp"

template <typename T>
struct Range_Polynomial_Add_Range_Sum {
    vector<Binary_Indexed_Tree<T>> bit;
    vector<vector<T>> stirling;
    const int n, k;

    Range_Polynomial_Add_Range_Sum(const vector<T> &v, int k) : n((int)v.size()), k(k) {
        bit.emplace_back(v);
        for (int i = 1; i <= k + 1; i++) bit.emplace_back(n, 0);
        stirling.assign(k + 1, vector<T>(k + 1, 0));
        stirling[0][0] = 1;
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= i; j++) stirling[i][j] = stirling[i - 1][j - 1] + stirling[i - 1][j] * j;
        }
    }

    Range_Polynomial_Add_Range_Sum(int n, T x, int k) : Range_Polynomial_Add_Range_Sum(vector<T>(n, x), k) {}

    Range_Polynomial_Add_Range_Sum(int n, int k) : Range_Polynomial_Add_Range_Sum(vector<T>(n, 0), k) {}

    void set(int i, const T &x) { bit[0].set(i, x); }

    void build() { bit[0].build(); }

    // [l,r) に f(i) を加算 (f は k 次以下の多項式)
    void add(int l, int r, const vector<T> &f) {
        int t = f.size();
        assert(t <= k + 1);
        vector<T> g(t, 0);
        for (int i = 0; i < t; i++) {
            for (int j = 0; j <= i; j++) g[j] += stirling[i][j] * f[i];
        }
        l = max(l, 0), r = min(r, n);
        {
            T cum = 0, p = 1;
            for (int i = 0; i < t; i++) {
                bit[i + 1].add(l, g[i]);
                p *= l - i;
                cum += g[i] * p / (i + 1);
            }
            bit[0].add(l, -cum);
        }
        if (r < n) {
            T cum = 0, p = 1;
            for (int i = 0; i < t; i++) {
                bit[i + 1].add(r, -g[i]);
                p *= r - i;
                cum += g[i] * p / (i + 1);
            }
            bit[0].add(r, cum);
        }
    }

    T sum(int i) const {
        i = min(i, n);
        if (i < 0) return 0;
        T ret = bit[0].sum(i), p = 1;
        for (int j = 0; j <= k; j++) {
            p *= i - j;
            ret += bit[j + 1].sum(i) * p / (j + 1);
        }
        return ret;
    }

    T query(int l, int r) const {
        l = max(l, 0), r = min(r, n);
        if (l >= r) return 0;
        return sum(r) - sum(l);
    }

    T operator[](int i) const { return query(i, i + 1); }
};
