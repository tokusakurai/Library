
// スパーステーブル
// 計算量 構築 : O(n log(n))、区間取得 : O(1)
// 空間計算量 O(n log(n))

// 概要
// ダブリングを用いて、各頂点から右に2^j個の区間に対して演算を行った結果を記録する。
// 取得したい区間が[l,r)であるとすると(r>l)、2^k<=(r-l)<2^(k+1)を満たす非負整数kが存在するので、区間[l,l+2^k)と区間[r-2^k,r)の演算結果をマージすればよい。
// kはr-lに依存する整数であるから、前計算が可能。
// 区間はoverlapするので、monoidであれば適用できるというわけではない。

// verified with
// https://judge.yosupo.jp/problem/staticrmq

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Sparse_Table {
    using F = function<T(T, T)>;
    const int n;
    int height;
    vector<vector<T>> st; // st[i][j] := 区間[j,j+2^i)での演算の結果
    vector<int> lookup;
    const F f;
    const T e;

    // f(f(a,b),c) = f(a,f(b,c)), f(e,a) = f(a,e) = a, f(a,a) = a
    // 例えばminやgcdはこれらを満たすが、+や*は満たさない

    Sparse_Table(const vector<T> &table, const F &f, const T &e) : n((int)table.size()), f(f), e(e) {
        height = 32 - __builtin_popcount(n);
        st.assign(height, vector<T>(n));
        for (int i = 0; i < n; i++) st[0][i] = table[i];
        for (int j = 0; j < height - 1; j++) {
            for (int i = 0; i < n; i++) {
                if (i + (1 << j) < n) {
                    st[j + 1][i] = f(st[j][i], st[j][i + (1 << j)]);
                } else {
                    st[j + 1][i] = st[j][i];
                }
            }
        }
        lookup.assign(n + 1, -1);
        for (int i = 1; i <= n; i++) lookup[i] = lookup[i / 2] + 1;
    }

    T query(int l, int r) const {
        if (l >= r) return e;
        int k = lookup[r - l];
        return f(st[k][l], st[k][r - (1 << k)]);
    }

    T operator[](int i) const { return st[0][i]; }
};
