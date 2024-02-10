#pragma once

// 二部 Union-Find Tree
// 計算量 構築：O(n)、併合・結合判定・サイズ：(ならし) O(α(n))
// 空間計算量 O(n)

// 概要
// 各頂点を 2 色で塗分ける。x,y を同色で塗る、異色で塗るのクエリに対応できる。矛盾が生じれば -1 を返す。
// 2n 頂点の Union-Find を用意し、
// x,y が同色確定 ⇔ x,y が連結
// x,y が異色確定 ⇔ x,n+y が連結
// とすればよい。

// verified with
// https://codeforces.com/contest/461/problem/D

#include <bits/stdc++.h>
using namespace std;

struct Bipartite_Union_Find_Tree {
    vector<int> data, si;
    const int n;
    int cnt;

    Bipartite_Union_Find_Tree(int n) : data(2 * n, -1), si(2 * n, 0), n(n), cnt(n) {
        for (int i = 0; i < n; i++) si[i] = 1;
    }

    int root(int x) {
        if (data[x] < 0) return x;
        return data[x] = root(data[x]);
    }

    int operator[](int i) { return root(i); }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y], data[y] = x;
        si[x] += si[y];
        return true;
    }

    int unite_same(int x, int y) {
        if (col_diff(x, y)) return -1;
        bool flag = unite(x, y);
        unite(n + x, n + y);
        if (flag) cnt--;
        return (flag ? 1 : 0);
    }

    int unite_diff(int x, int y) {
        if (col_same(x, y)) return -1;
        bool flag = unite(x, n + y);
        unite(n + x, y);
        if (flag) cnt--;
        return (flag ? 1 : 0);
    }

    int size(int x) { return -data[root(x)]; }

    int size_same(int x) { return si[root(x)]; }

    int size_diff(int x) {
        x = root(x);
        return -data[x] - si[x];
    }

    int count() { return cnt; };

    bool same(int x, int y) { return root(x) == root(y); }

    bool col_same(int x, int y) { return same(x, y); }

    bool col_diff(int x, int y) { return same(x, n + y); }

    void clear() {
        cnt = n;
        fill(begin(data), end(data), -1);
    }
};
