
//Dijkstra法(負辺がないグラフにおける単一始点最短路)
//計算量 O(V^2)

//概要
//始点から近い順に最短路を確定させる。
//ステップでまだ使われてない頂点で始点から最も近いものを調べる。

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Table{
    vector<vector<T>> es;
    vector<T> d;
    vector<bool> used;
    const T INF_T;
    const int n;

    inline const vector<T> &operator [] (int k) const{
        return es[k];
    }

    inline vector<T> &operator [] (int k){
        return es[k];
    }

    Table(int n) : es(n), d(n), used(n), INF_T(numeric_limits<T>::max()/2), n(n){
        for(int i = 0; i < n; i++) es[i].assign(n, INF_T);
        for(int i = 0; i < n; i++) es[i][i] = 0;
    }

    void add_edge(int from, int to, T cost = 1){
        es[from][to] = min(es[from][to], cost);
        if(!directed) es[to][from] = min(es[to][from], cost);
    }

    T dijkstra(int s, int t = 0){
        fill(begin(used), end(used), false), fill(begin(d), end(d), INF_T);
        d[s] = 0;
        for(int i = 0; i < n; i++){
            int u = -1;
            for(int j = 0; j < n; j++){
                if(!used[j] && (u == -1 || d[j] < d[u])) u = j;
            }
            used[u] = true;
            if(d[u] == INF_T) break;
            for(int j = 0; j < n; j++){
                if(es[u][j] != INF_T) d[j] = min(d[j], d[u]+es[u][j]);
            }
        }
        return d[t];
    }
};

int main(){
    int V, E, s; cin >> V >> E >> s;

    Table<int, true> G(V);

    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    G.dijkstra(s);

    for(int i = 0; i < V; i++){
        if(G.d[i] == INT_MAX/2) cout << "INF" << '\n';
        else cout << G.d[i] << '\n';
    }
}
