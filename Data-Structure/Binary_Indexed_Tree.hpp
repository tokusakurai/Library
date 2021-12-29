
// Binary Indexed Tree
// 計算量 構築：O(n)、1 点加算・区間和取得・二分探索：O(log(n))
// 空間計算量 O(n)

// 概要
// ノードを区間に対応させることで、任意の i について区間 [0,i) が O(log(n)) 個のノードが表す区間の disjoint な和集合として表現される。
// 各頂点を被覆するノードは O(log(n)) 個。
// 1 点加算 : その点を含むノードの値を全て加算する。
// 区間和取得 : [l,r) の和を求めるとき、[0,r) の和から [0,l) の和を引く。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja
// https://atcoder.jp/contests/practice2/tasks/practice2_b
// https://judge.yosupo.jp/problem/point_add_range_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Binary_Indexed_Tree {
    vector<T> bit;
    const int n;

    Binary_Indexed_Tree(const vector<T> &v) : n((int)v.size()) { // v は配列の初期状態
        bit.resize(n + 1);
        copy(begin(v), end(v), bit.begin() + 1);
        for (int a = 2; a <= n; a <<= 1) {
            for (int b = a; b <= n; b += a) { bit[b] += bit[b - a / 2]; }
        }
    }

    Binary_Indexed_Tree(int n, const T &x) : n(n) {
        bit.resize(n + 1);
        vector<T> v(n, x);
        copy(begin(v), end(v), begin(bit) + 1);
        for (int a = 2; a <= n; a <<= 1) {
            for (int b = a; b <= n; b += a) { bit[b] += bit[b - a / 2]; }
        }
    }

    void add(int i, const T &x) {
        for (i++; i <= n; i += (i & -i)) bit[i] += x;
    }

    void change(int i, const T &x) { add(i, x - query(i, i + 1)); }

    T sum(int i) const {
        T ret = 0;
        for (; i > 0; i -= (i & -i)) ret += bit[i];
        return ret;
    }

    T query(int l, int r) const { return sum(r) - sum(l); }

    T operator[](int i) const { return query(i, i + 1); }

    int lower_bound(T x) const { // 区間 [0,a] の総和が x 以上となる最小の a
        int ret = 0;
        for (int k = 31 - __builtin_clz(n); k >= 0; k--) {
            if (ret + (1 << k) <= n && bit[ret + (1 << k)] < x) x -= bit[ret += (1 << k)];
        }
        return ret;
    }

    int upper_bound(T x) const { // 区間 [0,a] の総和が x より大きくなる最小の a
        int ret = 0;
        for (int k = 31 - __builtin_clz(n); k >= 0; k--) {
            if (ret + (1 << k) <= n && bit[ret + (1 << k)] <= x) x -= bit[ret += (1 << k)];
        }
        return ret;
    }
};
