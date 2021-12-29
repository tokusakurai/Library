
// 部分永続 Union-Find Tree（任意時刻でのクエリを扱える）
// 計算量 構築：O(n)、（任意時刻tにおける）併合・結合判定・サイズ：O(log(n))
// 空間計算量 O(n)

// 概要
// まず、縮約は諦める。
// すると、各頂点について親が書き換えられるのは高々 1 回だけになるので、その時刻を記録しておけば任意時刻でも親をたどっていくことができる。

// verified with
// https://atcoder.jp/contests/agc002/tasks/agc002_d

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Partitially_Persistent_Union_Find_Tree {
    vector<int> data;
    vector<int> last;                   // 別の頂点にくっつけられた（自分が根でなくなった）時刻
    vector<vector<pair<int, int>>> add; // 併合が起きたときの時刻と連結成分のサイズを記録
    const int n;

    Partitially_Persistent_Union_Find_Tree(int n) : data(n, -1), last(n, INT_MAX), add(n), n(n) {
        for (int i = 0; i < n; i++) add[i].emplace_back(-1, -1);
    }

    int root(int t, int x) const {
        if (t < last[x]) return x;
        return root(t, data[x]);
    }

    bool unite(int t, int x, int y) {
        x = root(t, x), y = root(t, y);
        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);
        add[x].emplace_back(t, data[x] += data[y]);
        data[y] = x, last[y] = t;
        return true;
    }

    int size(int t, int x) const {
        x = root(t, x);
        return -prev(lower_bound(begin(add[x]), end(add[x]), make_pair(t, 0)))->second;
    }

    int same(int t, int x, int y) const { return root(t, x) == root(t, y); }

    void clear() {
        fill(begin(data), end(data), -1), fill(begin(last), end(last), INT_MAX);
        for (int i = 0; i < n; i++) add[i].clear(), add[i].emplace_back(-1, -1);
    }
};
