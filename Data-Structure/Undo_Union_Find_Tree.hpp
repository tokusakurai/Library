
// Undo 可能 Union-Find Tree
// 計算量 構築：O(n)、併合・結合判定・サイズ：O(log(n))、undo：O(1)
// 空間計算量 O(n)

// 概要
// まず、縮約は諦める。
// すると、各 union 操作において data 配列が変更されるのは高々 2 箇所だけであるから、変更箇所を記録しておけば O(1) で Undo できる。

// verified with
// https://codeforces.com/contest/1445/problem/E

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Undo_Union_Find_Tree {
    vector<int> data;
    stack<pair<int, int>> history; // data 配列の変更を記録
    const int n;

    Undo_Union_Find_Tree(int n) : data(n, -1), n(n) {}

    int root(int x) const {
        if (data[x] < 0) return x;
        return root(data[x]);
    }

    int operator[](int i) const { return root(i); }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        history.emplace(x, data[x]), history.emplace(y, data[y]);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y], data[y] = x;
        return true;
    }

    int size(int x) const { return -data[root(x)]; }

    bool same(int x, int y) const { return root(x) == root(y); }

    // 直前 k 回分の union 操作をなかったことにする
    void undo(int k) {
        k <<= 1;
        while (k--) {
            data[history.top().first] = history.top().second;
            history.pop();
        }
    }

    void clear() {
        while (!history.empty()) undo(1);
    }
};
