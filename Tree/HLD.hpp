
//Heavy-Light分解
//計算量 HL分解 : O(V)、パスが通る区間の個数 : O(log(V))

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
    const int n;
    int m;

    vector<int> par, si, depth;
    vector<int> root, comp; //属する連結成分の根、連結成分内の深さの順位
    vector<vector<int>> ids;

    Graph(int n) : es(n), n(n), m(0), par(n), si(n), depth(n), root(n), comp(n), ids(n) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int dfs1(int now, int pre = -1){
        par[now] = pre;
        if(pre == -1) depth[now] = 0;
        si[now] = 1;
        for(auto &e: es[now]){
            if(e.to != pre){
                depth[e.to] = depth[now]+1;
                si[now] += dfs1(e.to, now);
            }
        }
        return si[now];
    }

    void dfs2(int now, bool st, int pre = -1){
        if(st) root[now] = now, comp[now] = 0;
        else root[now] = root[pre], comp[now] = comp[pre]+1;
        ids[root[now]].push_back(now);
        int c = -1, M = 0;
        for(auto &e: es[now]){
            if(e.to == pre) continue;
            if(M < si[e.to]) M = si[e.to], c = e.to;
        }
        for(auto &e: es[now]){
            if(e.to != pre) dfs2(e.to, c != e.to, now);
        }
    }

    void decompose(int root = 0){
        dfs1(root);
        dfs2(root, true);
    }

    vector<tuple<int, int, int>> find_path(int u, int v){ //通ったパスの(親、左端、右端)の組を返す
        vector<tuple<int, int, int>> ret;
        while(root[u] != root[v]){
            if(depth[root[u]] > depth[root[v]]) swap(u, v);
            ret.emplace_back(root[v], 0, comp[v]+1);
            v = par[root[v]];
        }
        if(depth[u] > depth[v]) swap(u, v);
        ret.emplace_back(root[u], comp[u], comp[v]+1);
        return ret;
    }
};
