
//木の重心分解(雛形)
//計算量 O(V)

//概要
//DFSを用いて、各頂点についてその点を除いたときの残る部分木のサイズの最大値を列挙することで重心を求める。

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> si;
    vector<bool> used;
    const int n;
    int m;

    Graph(int n) : es(n), si(n), used(n, false), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int calc_size(int now, int pre = -1){
        si[now] = 1;
        for(auto &e: es[now]){
            if(e.to == pre || used[e.to]) continue;
            si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    pair<int, int> search_centroid(int now, int sz, int pre = -1){ //(残りの最大部分木の頂点数、重心)
        pair<int, int> ret = make_pair(INT_MAX, -1);
        int M = 0, S = 1;
        for(auto &e: es[now]){
            if(e.to == pre || used[e.to]) continue;
            ret = min(ret, search_centroid(e.to, sz, now));
            M = max(M, si[e.to]);
            S += si[e.to];
        }
        M = max(M, sz-S);
        ret = min(ret, make_pair(M, now));
        return ret;
    }

    int centroid(int s){ //頂点sを含む連結成分の重心を返す
        calc_size(s);
        return search_centroid(s, si[s]).second;
    }

    void decompose(int root = 0){
        int c = centroid(root);
        used[c] = true;
        for(auto &e: es[c]){
            if(!used[e.to]) decompose(e.to);
        }
    }
};

int main(){
    int V; cin >> V;

    Graph G(V);
    for(int i = 0; i < V-1; i++){
        int u, v; cin >> u >> v;
        G.add_edge(u, v);
    }

    G.decompose(0);
}
