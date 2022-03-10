
// 永続 Union-Find Tree
// 計算量 併合・結合判定・サイズ：O(log^2(n))、複製：O(1)
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

struct Persistent_Union_Find_Tree {
    Persistent_Array<int> data;

    Persistent_Union_Find_Tree(int n) : data(n, -1) {}

    Persistent_Union_Find_Tree() : data() {}

    void resize(int n) { data.resize(n, -1); }

    void copy(const Persistent_Union_Find_Tree &uf) { data.copy(uf.data); }

    int root(int x) const {
        int y = data.get(x);
        if (y < 0) return x;
        return root(y);
    }

    int operator[](int i) const { return root(i); }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        int a = data.get(x), b = data.get(y);
        if (a > b) swap(x, y), swap(a, b);
        data.change(x, a + b);
        data.change(y, x);
        return true;
    }

    int size(int x) const { return -data.get(root(x)); }

    bool same(int x, int y) const { return root(x) == root(y); }
};
