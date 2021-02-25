
//木の重心分解(雛形)
//計算量 1回の重心分解:O(V)

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

    void decompose(int root = 0){
        calc_size(root);
        int c = search_centroid(root, si[root]).second;
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
