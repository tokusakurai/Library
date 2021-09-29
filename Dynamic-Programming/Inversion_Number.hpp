
// 転倒数
// 計算量 O(N*log(N))

// 概要
// 配列を左端から右端の順または小さい要素から大きい要素の順に見ていき、各値やidの出現回数をBITで記録する。

// verified with
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D&lang=jp

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Binary_Indexed_Tree.hpp"

template <typename T>
long long inversion_number(const vector<T> &a) {
    int n = a.size();
    vector<int> v(n);
    iota(begin(v), end(v), 0);
    sort(begin(v), end(v), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    Binary_Indexed_Tree<int> bit(n, 0);
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        ret += bit.query(v[i] + 1, n);
        bit.add(v[i], 1);
    }
    return ret;
}

template <typename T>
long long inversion_number(const vector<T> &a, const vector<T> &b) { // aをbに変換するのに必要な最小バブルソート回数
    int n = a.size();
    assert(b.size() == n);
    vector<int> u(n), v(n);
    iota(begin(u), end(u), 0);
    sort(begin(u), end(u), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    iota(begin(v), end(v), 0);
    sort(begin(v), end(v), [&](int i, int j) {
        if (b[i] != b[j]) return b[i] < b[j];
        return i < j;
    });
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        if (a[u[i]] != b[v[i]]) return -1;
        w[v[i]] = u[i];
    }
    Binary_Indexed_Tree<int> bit(n, 0);
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        ret += bit.query(w[i] + 1, n);
        bit.add(w[i], 1);
    }
    return ret;
}
