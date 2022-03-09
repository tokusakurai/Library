
// 永続 Union-Find Tree
// 計算量 （任意時刻 t における）併合・結合判定・サイズ：O(log^2(n))
// 空間計算量 O(n+q log(n))（q はクエリの回数）

// 概要
// まず、縮約はあきらめる。
// すると、各 Union クエリで書き換えられる配列の要素は高々 2 つなので、永続配列で保持することができる。

// verified with
// https://judge.yosupo.jp/problem/persistent_unionfind

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Persistent_Array.hpp"

template <typename S = int>
struct Persistent_Union_Find_Tree {
    Persistent_Array<int, S> pa;
    const int n;

    Persistent_Union_Find_Tree(int n, S t = -1) : n(n), pa(n, -1, 2 * t) {}

    int root(const S &t, int x) const { // 時刻 t での根
        int y = pa.query(2 * t, x);
        if (y < 0) return x;
        return root(t, y);
    }

    bool unite(const S &s, const S &t, int x, int y) { // 時刻 s でのグラフの頂点 x,y を結んだものを時刻 t でのグラフとする
        x = root(s, x), y = root(s, y);
        if (x == y) {
            pa.change(2 * s, 2 * t, -1, 0);
            return false;
        }
        int a = pa.query(2 * s, x), b = pa.query(2 * s, y);
        if (a > b) swap(x, y), swap(a, b);
        pa.change(2 * s, 2 * t - 1, x, a + b);
        pa.change(2 * t - 1, 2 * t, y, x);
        return true;
    }

    int size(const S &t, int x) const { return -pa.query(2 * t, root(t, x)); }

    bool same(const S &t, int x, int y) const { return root(t, x) == root(t, y); }
};