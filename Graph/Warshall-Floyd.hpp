
// Warshall_Floyed法(負辺があっても動作する全点対最短路)
// 計算量 O(V^3)

// 概要
// dp[k][i][j] := 頂点0~k-1と頂点i,jのみを使うときのiからjへの最短路
// このdpをメモリ省略で行うことができる。
// dp[i][i]<0となるiが存在する場合、頂点iを含む負閉路が存在する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Table {
    vector<vector<T>> es;
    const T INF_T;
    const int n;

    inline const vector<T> &operator[](int k) const { return es[k]; }

    inline vector<T> &operator[](int k) { return es[k]; }

    Table(int n) : es(n), INF_T(numeric_limits<T>::max() / 2), n(n) {
        for (int i = 0; i < n; i++) es[i].assign(n, INF_T);
        for (int i = 0; i < n; i++) es[i][i] = 0;
    }

    void add_edge(int from, int to, T cost = 1) {
        es[from][to] = min(es[from][to], cost);
        if (!directed) es[to][from] = min(es[to][from], cost);
    }

    void warshall_floyd() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (es[i][k] == INF_T || es[k][j] == INF_T) continue;
                    es[i][j] = min(es[i][j], es[i][k] + es[k][j]);
                }
            }
        }
    }
};
