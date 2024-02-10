#pragma once

// スパーステーブル
// 計算量 構築：O(n log(n))、区間取得：O(1)
// 空間計算量 O(n log(n))

// 概要
// ダブリングを用いて、各頂点から右に 2^j 個の区間に対して演算を行った結果を記録する。
// 取得したい区間が [l,r) であるとすると、2^k <= (r-l) < 2^(k+1) を満たす非負整数 k が存在するので、区間 [l,l+2^k) と区間 [r-2^k,r) の演算結果をマージすればよい。
// k は r-l に依存する整数であるから、前計算が可能。
// 区間は overlap するので、monoid であれば適用できるというわけではない。

// verified with
// https://judge.yosupo.jp/problem/staticrmq

#include <bits/stdc++.h>
using namespace std;

template <typename Idempotent_Monoid>
struct Sparse_Table {
    using M = typename Idempotent_Monoid::V;
    const int n;
    int height;
    vector<vector<M>> st; // st[i][j] := 区間 [j,j+2^i) での演算の結果
    vector<int> lookup;

    // f(f(a,b),c) = f(a,f(b,c)), f(e,a) = f(a,e) = a, f(a,a) = a
    // 例えば min や gcd はこれらを満たすが、+ や * は満たさない

    Sparse_Table(const vector<M> &table) : n((int)table.size()) {
        height = 0;
        while (n >> height) height++;
        st.assign(height, vector<M>(n));
        for (int i = 0; i < n; i++) st[0][i] = table[i];
        for (int j = 0; j < height - 1; j++) {
            for (int i = 0; i < n; i++) {
                if (i + (1 << j) < n) {
                    st[j + 1][i] = Idempotent_Monoid::merge(st[j][i], st[j][i + (1 << j)]);
                } else {
                    st[j + 1][i] = st[j][i];
                }
            }
        }
        lookup.assign(n + 1, -1);
        for (int i = 1; i <= n; i++) lookup[i] = lookup[i / 2] + 1;
    }

    M query(int l, int r) const {
        if (l >= r) return Idempotent_Monoid::id;
        int k = lookup[r - l];
        return Idempotent_Monoid::merge(st[k][l], st[k][r - (1 << k)]);
    }

    M operator[](int i) const { return st[0][i]; }
};
