
//Bellman-Ford法(負辺があっても動作する単一始点最短路)
//計算量 O(E*V)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Weighted_Graph{
    struct edge{
        int to; T cost; int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<T> d;
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), d(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    bool bellman_ford(int s){ //sから到達可能な負閉路を検出
        fill(begin(d), end(d), INF_T);
        d[s] = 0;
        bool ret = false;
        for(int i = 0; i < 2*n; i++){
            for(int j = 0; j < n; j++){
                for(auto &e: es[j]){
                    if(d[j] == INF_T) continue;
                    if(d[j]+e.cost < d[e.to]){
                        d[e.to] = d[j]+e.cost;
                        if(i >= n-1) d[e.to] = -INF_T, ret = true;
                    }
                }
            }
        }
        return ret;
    }

    bool negative_loop(){ //全ての負閉路を検出
        fill(begin(d), end(d), 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(auto &e: es[j]){
                    if(d[j]+e.cost < d[e.to]){
                        d[e.to] = d[j]+e.cost;
                        if(i == n-1) return true;
                    }
                }
            }
        }
    }
};

int main(){
    int V, E, s; cin >> V >> E >> s;

    Weighted_Graph<int, true> G(V);

    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    if(G.bellman_ford(s)) {cout << "NEGATIVE CYCLE\n"; return 0;}

    for(int i = 0; i < V; i++){
        if(G.d[i] == INT_MAX/2) cout << "INF" << '\n';
        else cout << G.d[i] << '\n';
    }
}
