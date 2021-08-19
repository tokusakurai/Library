
//最近共通祖先(LCA)
//計算量 構築 : O(V*log(V))、2頂点のLCA・距離 : O(log(V))
//空間計算量 O(V*log(V))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
//https://judge.yosupo.jp/problem/lca
//https://atcoder.jp/contests/abc014/tasks/abc014_4

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Weighted_Graph{
    struct edge{
        int to; T cost; int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    const T INF_T;
    const int n;
    int m;

    const int height;
    vector<vector<int>> par; //par[i][j] := 頂点jの2^i個前の祖先
    vector<int> depth;
    vector<T> d;

    Weighted_Graph(int n) : es(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0), height(32-__builtin_clz(n)), depth(n), d(n){
        par.assign(height, vector<int>(n));
    }

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    void prepare(int now, int pre = -1){
        if(pre == -1) depth[now] = 0, d[now] = 0;
        par[0][now] = pre;
        for(auto &e: es[now]){
            if(e.to != pre){
                depth[e.to] = depth[now]+1;
                d[e.to] = d[now]+e.cost;
                prepare(e.to, now);
            }
        }
    }

    void build(int root = 0){
        prepare(root);
        for(int j = 0; j < height-1; j++){
            for(int i = 0; i < n; i++){
                if(par[j][i] == -1) par[j+1][i] = -1;
                else par[j+1][i] = par[j][par[j][i]];
            }
        }
    }

    int lca(int u, int v){
        if(depth[u] < depth[v]) swap(u, v);
        int D = depth[u]-depth[v];
        for(int i = 0; i < height; i++){
            if((D>>i)&1) u = par[i][u];
        }
        if(u == v) return u;
        for(int i = height-1; i >= 0; i--){
            if(par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
        }
        return par[0][u];
    }

    T dist(int u, int v){
        return d[u]+d[v]-2*d[lca(u, v)];
    }
};
