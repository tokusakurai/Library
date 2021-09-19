
// Union-Find Tree
// 計算量 構築 : O(N)、併合・結合判定・サイズ・ポテンシャル取得 : (ならし)O(α(N))
// 空間計算量 O(N)

// 概要
// サイズが大きい成分にサイズが小さい成分をくっつけるマージテクでクエリ : O(log(N))
// さらに頂点の根を求める際に根に直接つなぎ直す縮約をすることでクエリ : (ならし)O(α(N))

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=ja
// https://atcoder.jp/contests/atc001/tasks/unionfind_a
// https://judge.yosupo.jp/problem/unionfind

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Union_Find_Tree {
    vector<int> data;
    const int n;
    int cnt;

    Union_Find_Tree(int n) : data(n, -1), n(n), cnt(n) {}

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
        cnt--;
        return true;
    }

    int size(int x) { return -data[root(x)]; }

    int count() { return cnt; };

    bool same(int x, int y) { return root(x) == root(y); }

    void clear() {
        cnt = n;
        fill(begin(data), end(data), -1);
    }
};
