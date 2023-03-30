
// 永続 Union-Find Tree
// 計算量 併合・結合判定・サイズ：O(log^2(n))、複製：O(1)
// 空間計算量 O(n+q log(n)) (q はクエリの回数)

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

    Persistent_Union_Find_Tree(int n, int init_id = 0) : data(n, -1, init_id) {}

    void resize(int n) { data.resize(n, -1); }

    void copy(int ref_id, int new_id) { data.copy(ref_id, new_id); }

    int root(int ref_id, int x) {
        int y = data.get(ref_id, x);
        if (y < 0) return x;
        return root(ref_id, y);
    }

    // ref_id に対応するデータから派生して new_id に対応する新しいデータを作る
    bool unite(int ref_id, int new_id, int x, int y) {
        x = root(ref_id, x), y = root(ref_id, y);
        if (x == y) {
            copy(ref_id, new_id);
            return false;
        }
        int a = data.get(ref_id, x), b = data.get(ref_id, y);
        if (a > b) swap(x, y), swap(a, b);
        data.update(ref_id, new_id, x, a + b);
        data.update(new_id, new_id, y, x);
        return true;
    }

    int size(int ref_id, int x) { return -data.get(ref_id, root(ref_id, x)); }

    bool same(int ref_id, int x, int y) { return root(ref_id, x) == root(ref_id, y); }
};
