#pragma once

// Warshall-Floyd (負辺があっても動作する全点対最短路)
// 計算量 O(n^3)

// 概要
// dp[k][i][j] := 頂点 0,1,...,k-1 と頂点 i,j のみを使うときの i から j への最短路
// この dp をメモリ省略で行うことができる。
// dp[i][i] < 0 となる i が存在する場合、頂点 i を含む負閉路が存在する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename T, bool directed = false>
struct Warshall_Floyd {
    vector<vector<T>> es;
    const T zero_T, INF_T;
    const int n;

    inline const vector<T> &operator[](int k) const { return es[k]; }

    inline vector<T> &operator[](int k) { return es[k]; }

    Warshall_Floyd(int n, T zero_T = 0, T INF_T = numeric_limits<T>::max() / 2) : es(n, vector<T>(n)), zero_T(zero_T), INF_T(INF_T), n(n) {
        for (int i = 0; i < n; i++) fill(begin(es[i]), end(es[i]), INF_T);
        for (int i = 0; i < n; i++) es[i][i] = zero_T;
    }

    void add_edge(int from, int to, T cost = 1) {
        es[from][to] = min(es[from][to], cost);
        if (!directed) es[to][from] = min(es[to][from], cost);
    }

    vector<vector<T>> shortest_path() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (es[i][k] == INF_T || es[k][j] == INF_T) continue;
                    es[i][j] = min(es[i][j], es[i][k] + es[k][j]);
                }
            }
        }
        return es;
    }
};
