
//Heavy-Light分解
//計算量 HL分解 : O(V)、パス検出・パスが通る区間の個数 : O(log(V))

//概要
//根付き木の各頂点の重みを、その頂点を根とする部分木の頂点数とする。
//各頂点について、子のうち重みが最大のものとの間の辺のみを残す。
//結果として木はいくつかの列に分割され、任意の2頂点間の単純パスについて通る列の個数は最大でO(log(V))個となる。

//verified with
//https://judge.yosupo.jp/problem/vertex_add_path_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> par, si, depth;
    vector<int> root, comp, cnt, ls; //属する連結成分の根、連結成分内の深さの順位、連結成分のサイズ、連結成分を列にしたときの開始位置
    const int n;
    int m;

    Graph(int n) : es(n), par(n), si(n), depth(n), root(n), comp(n), cnt(n, 0), ls(n, 0), n(n) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int _dfs1(int now, int pre = -1){
        par[now] = pre;
        if(pre == -1) depth[now] = 0;
        si[now] = 1;
        for(auto &e: es[now]){
            if(e.to != pre){
                depth[e.to] = depth[now]+1;
                si[now] += _dfs1(e.to, now);
            }
        }
        return si[now];
    }

    void _dfs2(int now, bool st, int pre = -1){
        if(st) root[now] = now, comp[now] = 0;
        else root[now] = root[pre], comp[now] = comp[pre]+1;
        cnt[root[now]]++;
        int c = -1, M = 0;
        for(auto &e: es[now]){
            if(e.to == pre) continue;
            if(M < si[e.to]) M = si[e.to], c = e.to;
        }
        for(auto &e: es[now]){
            if(e.to != pre) _dfs2(e.to, c != e.to, now);
        }
    }

    void decompose(int root = 0){
        _dfs1(root);
        _dfs2(root, true);
        for(int i = 1; i < n; i++) ls[i] = cnt[i-1]+ls[i-1];
    }

    vector<pair<int, int>> get_path(int u, int v, bool use_edge = false){ //パスに対応する区間たちを列挙
        vector<pair<int, int>> ret;
        while(root[u] != root[v]){
            if(depth[root[u]] > depth[root[v]]) swap(u, v);
            int l = ls[root[v]];
            ret.emplace_back(l, l+comp[v]+1);
            v = par[root[v]];
        }
        if(depth[u] > depth[v]) swap(u, v);
        int l = ls[root[u]];
        ret.emplace_back(l+comp[u]+use_edge, l+comp[v]+1);
        return ret;
    }
};
