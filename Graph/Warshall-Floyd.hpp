
// Warshall-Floyd 法（負辺があっても動作する全点対最短路）
// 計算量 O(n^3)

// 概要
// dp[k][i][j] := 頂点 0,1,...,k-1 と頂点 i,j のみを使うときの i から j への最短路
// この dp をメモリ省略で行うことができる。
// dp[i][i] < 0 となる i が存在する場合、頂点 i を含む負閉路が存在する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Table {
    vector<vector<T>> es;
    const T INF_T = numeric_limits<T>::max() / 2;
    const int n;

    inline const vector<T> &operator[](int k) const { return es[k]; }

    inline vector<T> &operator[](int k) { return es[k]; }

    Table(int n) : es(n), n(n) {
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
