
//Hopcroft-Karp法(2部グラフの最大マッチング)
//計算量 O(E*√V)

//概要
//左側のマッチングに含まれない点の深さを0としてBFSで各点の深さを決定する。
//このとき左→右の移動では現在マッチングに使われていない辺を、右→左の移動では現在マッチングに使われている辺のみを用いる。
//左側のマッチングに含まれていない点から右側のマッチングに含まれていない点へのパスをDFSで見つけ、パス上の辺の使用不使用を反転させる。
//ステップ回数は最大でO(√V)回。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A&lang=ja
//https://judge.yosupo.jp/problem/bipartitematching

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Bipartite_Matching{
    vector<vector<int>> es;
    vector<int> d, match;
    vector<bool> used, used2;
    const int n, m;

    Bipartite_Matching(int n, int m) : es(n), d(n), match(m), used(n), used2(n), n(n), m(m) {}

    void add_edge(int u, int v){
        es[u].push_back(v);
    }

    void _bfs(){
        fill(begin(d), end(d), -1);
        queue<int> que;
        for(int i = 0; i < n; i++){
            if(!used[i]) que.emplace(i), d[i] = 0;
        }
        while(!que.empty()){
            int i = que.front(); que.pop();
            for(auto &e: es[i]){
                int j = match[e];
                if(j != -1 && d[j] == -1){
                    que.emplace(j), d[j] = d[i]+1;
                }
            }
        }
    }

    bool _dfs(int now){
        used2[now] = true;
        for(auto &e: es[now]){
            int u = match[e];
            if(u == -1 || (!used2[u] && d[u] == d[now]+1 && _dfs(u))){
                match[e] = now, used[now] = true;
                return true;
            }
        }
        return false;
    }

    int bipartite_matching(){ //操作後のmatch配列は最大マッチングの1つにおいて右側の各要素とマッチングする左側の要素を表す
        fill(begin(match), end(match), -1), fill(begin(used), end(used), false);
        int ret = 0;
        while(true){
            _bfs();
            fill(begin(used2), end(used2), false);
            int flow = 0;
            for(int i = 0; i < n; i++){
                if(!used[i] && _dfs(i)) flow++;
            }
            if(flow == 0) break;
            ret += flow;
        }
        return ret;
    }
};
