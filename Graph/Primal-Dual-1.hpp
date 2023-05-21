
// Primal-Dual 法 (最小費用流)
// 計算量 O(fnm)

// 概要
// 残余グラフにおいて Bellman-Ford 法で最短路を求め、流せるだけ流す。
// ステップ回数は最大で f 回。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

// F : 流量の型、T : 費用の型
template <typename F, typename T = F>
struct Primal_Dual {
    struct edge {
        int to;
        F cap;
        T cost;
        int rev;
        edge(int to, F cap, T cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
    };

    vector<vector<edge>> es;
    vector<T> d;
    vector<int> pre_v, pre_e;
    const F zero_F, INF_F;
    const T zero_T, INF_T;
    const int n;

    Primal_Dual(int n, F zero_F = 0, F INF_F = numeric_limits<F>::max() / 2, T zero_T = 0, T INF_T = numeric_limits<T>::max() / 2)
        : es(n), d(n), pre_v(n), pre_e(n), zero_F(zero_F), INF_F(INF_F), zero_T(zero_T), INF_T(INF_T), n(n) {}

    void add_edge(int from, int to, F cap, T cost) {
        es[from].emplace_back(to, cap, cost, (int)es[to].size());
        es[to].emplace_back(from, zero_F, -cost, (int)es[from].size() - 1);
    }

    void bellman_ford(int s) {
        fill(begin(d), end(d), INF_T);
        d[s] = zero_T;
        while (true) {
            bool update = false;
            for (int i = 0; i < n; i++) {
                if (d[i] == INF_T) continue;
                for (int j = 0; j < (int)es[i].size(); j++) {
                    edge &e = es[i][j];
                    if (e.cap > zero_F && d[i] + e.cost < d[e.to]) {
                        d[e.to] = d[i] + e.cost;
                        pre_v[e.to] = i, pre_e[e.to] = j;
                        update = true;
                    }
                }
            }
            if (!update) break;
        }
    }

    T min_cost_flow(int s, int t, F flow) {
        T ret = zero_T;
        while (flow > zero_F) {
            bellman_ford(s);
            if (d[t] == INF_T) return INF_T;
            F f = flow;
            for (int now = t; now != s; now = pre_v[now]) f = min(f, es[pre_v[now]][pre_e[now]].cap);
            ret += f * d[t], flow -= f;
            for (int now = t; now != s; now = pre_v[now]) {
                edge &e = es[pre_v[now]][pre_e[now]];
                e.cap -= f, es[now][e.rev].cap += f;
            }
        }
        return ret;
    }
};
