
//無向グラフでの基本的なDFS
//計算量 パス検出・閉路検出 : O(E+V)

//概要
//直前に使用した辺を戻らないようにしてDFSをする。
//パス検出 : 目的の点に到達したら探索を打ち切って、来たパスを戻ることで復元する。
//閉路検出 : 同じ点に2回到達したら探索を打ち切って、その頂点に来るまで来たパスを戻ることで復元する。

//verified with
//https://yukicoder.me/problems/no/1254

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

    vector<int> used;

    Graph(int n) : es(n), n(n), m(0), used(n) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    vector<int> ret_path;

    bool detect_path(int now, int t, bool use_id = false){
        used[now] = true;
        if(now == t){
            if(!use_id) ret_path.push_back(now);
            return true;
        }
        for(auto &e : es[now]){
            if(used[e.to]) continue;
            if(detect_path(e.to, t, use_id)){
                ret_path.push_back(use_id? e.id : now);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t, bool use_id = false){ //点素なs-tパスを1つ検出
        ret_path.clear(), fill(begin(used), end(used), 0);
        detect_path(s, t, use_id);
        reverse(begin(ret_path), end(ret_path));
        return ret_path;
    }

    vector<int> ret_cycle;

    int detect_cycle(int now, int pre = -1, bool use_id = false){
        if(used[now]++) return 1;
        for(auto &e: es[now]){
            if(e.id == pre) continue;
            int k = detect_cycle(e.to, e.id, use_id);
            if(k == 2) return 2;
            if(k == 1){
                ret_cycle.push_back(use_id? e.id : now);
                return used[now];
            }
        }
        return 0;
    }

    vector<int> find_cycle(bool use_id = false){ //点素な閉路を1つ検出
        ret_cycle.clear(), fill(begin(used), end(used), 0);
        for(int i = 0; i < n; i++){
            if(used[i]) continue;
            detect_cycle(i, -1, use_id);
            if(!ret_cycle.empty()){
                reverse(begin(ret_cycle), end(ret_cycle));
                return ret_cycle;
            }
        }
        return {};
    }
};

int main(){
    int V; cin >> V;

    Graph G(V);

    for(int i = 0; i < V; i++){
        int u, v; cin >> u >> v; u--, v--;
        G.add_edge(u, v);
    }
    
    vector<int> cycle = G.find_cycle(true);

    cout << cycle.size() << '\n';
    for(auto &e: cycle) cout << e+1 << ' ';
    cout << '\n';
}
