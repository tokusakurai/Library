#pragma once

// s から t への流量 f の最小費用流を求める (最初のグラフに負の閉路が存在しない場合)
// 計算量 O(nm+fn^2)、初期状態でコストが負の辺が存在しないまたはグラフが DAG である場合：O(fn^2)

// 概要
// O(n^2) の Dijkstra 法を用いることで、頂点が少なく辺が多い場合に高速に動作する。

// verified with
// https://judge.yosupo.jp/problem/assignment

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
    vector<T> d, h;
    vector<int> pre_v, pre_e;
    bool negative = false;
    const F zero_F, INF_F;
    const T zero_T, INF_T;
    const int n;

    Primal_Dual(int n, F zero_F = 0, F INF_F = numeric_limits<F>::max() / 2, T zero_T = 0, T INF_T = numeric_limits<T>::max() / 2)
        : es(n), d(n), h(n), pre_v(n), pre_e(n), zero_F(zero_F), INF_F(INF_F), zero_T(zero_T), INF_T(INF_T), n(n) {}

    void add_edge(int from, int to, F cap, T cost) {
        es[from].emplace_back(to, cap, cost, (int)es[to].size());
        es[to].emplace_back(from, 0, -cost, (int)es[from].size() - 1);
        if (cost < 0) negative = true;
    }

    void bellman_ford(int s) {
        fill(begin(h), end(h), INF_T);
        h[s] = zero_T;
        while (true) {
            bool update = false;
            for (int i = 0; i < n; i++) {
                if (h[i] == INF_T) continue;
                for (auto &e : es[i]) {
                    if (e.cap > zero_F && h[i] + e.cost < h[e.to]) {
                        h[e.to] = h[i] + e.cost;
                        update = true;
                    }
                }
            }
            if (!update) break;
        }
    }

    void dag_shortest_path(int s) {
        vector<int> deg(n, 0);
        for (int i = 0; i < n; i++) {
            for (auto &e : es[i]) {
                if (e.cap > zero_F) deg[e.to]++;
            }
        }
        fill(begin(h), end(h), INF_T);
        h[s] = zero_T;
        queue<int> que;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) que.push(i);
        }
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                if (e.cap == zero_F) continue;
                h[e.to] = min(h[e.to], h[i] + e.cost);
                if (--deg[e.to] == 0) que.push(e.to);
            }
        }
    }

    void dijkstra(int s) {
        fill(begin(d), end(d), INF_T);
        vector<bool> used(n, false);
        d[s] = zero_T;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!used[j] && (u == -1 || d[j] < d[u])) u = j;
            }
            used[u] = true;
            if (d[u] == INF_T) break;
            for (int j = 0; j < (int)es[u].size(); j++) {
                edge &e = es[u][j];
                if (e.cap > zero_F && d[u] + e.cost + h[u] - h[e.to] < d[e.to]) {
                    d[e.to] = d[u] + e.cost + h[u] - h[e.to];
                    pre_v[e.to] = u, pre_e[e.to] = j;
                }
            }
        }
    }

    T min_cost_flow(int s, int t, F flow, bool dag = false) {
        T ret = zero_T;
        if (negative) dag ? dag_shortest_path(s) : bellman_ford(s);
        while (flow > zero_F) {
            dijkstra(s);
            if (d[t] == INF_T) return INF_T;
            for (int i = 0; i < n; i++) {
                if (h[i] == INF_T || d[i] == INF_T) {
                    h[i] = INF_T;
                } else {
                    h[i] += d[i];
                }
            }
            F f = flow;
            for (int now = t; now != s; now = pre_v[now]) f = min(f, es[pre_v[now]][pre_e[now]].cap);
            ret += h[t] * f, flow -= f;
            for (int now = t; now != s; now = pre_v[now]) {
                edge &e = es[pre_v[now]][pre_e[now]];
                e.cap -= f, es[now][e.rev].cap += f;
            }
        }
        return ret;
    }

    vector<pair<T, F>> min_cost_flow_slope(int s, int t, bool dag = false) {
        vector<pair<T, F>> ret;
        if (negative) dag ? dag_shortest_path(s) : bellman_ford(s);
        while (true) {
            dijkstra(s);
            if (d[t] == INF_T) break;
            for (int i = 0; i < n; i++) {
                if (h[i] == INF_T || d[i] == INF_T) {
                    h[i] = INF_T;
                } else {
                    h[i] += d[i];
                }
            }
            F f = INF_F;
            for (int now = t; now != s; now = pre_v[now]) f = min(f, es[pre_v[now]][pre_e[now]].cap);
            if (!ret.empty() && ret.back().first == h[t]) {
                ret.back().second += f;
            } else {
                ret.emplace_back(h[t], f);
            }
            for (int now = t; now != s; now = pre_v[now]) {
                edge &e = es[pre_v[now]][pre_e[now]];
                e.cap -= f, es[now][e.rev].cap += f;
            }
        }
        return ret;
    }
};
