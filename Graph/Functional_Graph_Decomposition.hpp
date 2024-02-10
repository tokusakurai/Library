#pragma once

// functional graph のサイクル分解
// 計算量 O(n)

// 概要
// functional graph の全てのサイクルと、サイクルを除いてできる森の隣接リストの組を返す

#include <bits/stdc++.h>
using namespace std;

pair<vector<vector<int>>, vector<vector<int>>> functional_graph_decompose(const vector<int> &a) {
    int n = a.size();
    vector<vector<int>> cycles;
    vector<vector<int>> es(n);
    vector<int> c(n, 0);
    for (int i = 0; i < n; i++) {
        for (int p = i;; p = a[p]) {
            if (c[p] == 1) {
                int q = p;
                vector<int> cycle;
                do {
                    cycle.push_back(q);
                    c[q] = 3;
                    q = a[q];
                } while (q != p);
                cycles.push_back(cycle);
            }
            if (c[p] >= 2) break;
            c[p]++;
        }
        for (int p = i; c[p] == 1; p = a[p]) c[p] = 2;
    }
    for (int i = 0; i < n; i++) {
        if (c[i] != 3) {
            es[i].push_back(a[i]);
            es[a[i]].push_back(i);
        }
    }
    return make_pair(cycles, es);
}
