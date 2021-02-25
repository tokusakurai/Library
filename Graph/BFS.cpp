
//BFS
//計算量 O(E+V)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> d;
    const int n;
    int m;

    Graph(int n) : es(n), d(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int bfs(int s, int t = 0){
        fill(begin(d), end(d), INT_MAX/2);
        queue<int> que;
        d[s] = 0, que.emplace(s);
        while(!que.empty()){
            int i = que.front(); que.pop();
            for(auto &e: es[i]){
                if(d[i]+1 < d[e.to]){
                    d[e.to] = d[i]+1, que.push(e.to);
                }
            }
        }
        return d[t];
    }
};

int main(){
    int V; cin >> V;

    Graph<true> G(V);

    for(int i = 0; i < V; i++){
        int u, E; cin >> u >> E; u--;

        for(int j = 0; j < E; j++){
            int v; cin >> v; v--;
            G.add_edge(u, v);
        }
    }

    G.bfs(0);

    for(int i = 0; i < V; i++){
        cout << i+1 << ' ' << (G.d[i] >= V? -1 : G.d[i]) << '\n';
    }
}
