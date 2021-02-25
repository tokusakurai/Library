
//Dijkstra法(負辺がないグラフにおける単一始点最短路)
//計算量 O(E*log(V))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
//https://judge.yosupo.jp/problem/shortest_path

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
    vector<int> pre_v;
    vector<int> keep;
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), d(n), pre_v(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T dijkstra(int s, int t = 0){
        fill(begin(d), end(d), INF_T);
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P> > que;
        que.emplace(d[s] = 0, s);
        while(!que.empty()){
            auto [p, i] = que.top(); que.pop();
            if(p > d[i]) continue;
            for(auto &e: es[i]){
                if(d[i]+e.cost < d[e.to]){
                    pre_v[e.to] = i, que.emplace(d[e.to] = d[i]+e.cost, e.to);
                }
            }
        }
        return d[t];
    }

    vector<int> shortest_path(int s, int t){ //経路復元
        keep.clear();
        if(dijkstra(s, t) == INF_T) return keep;
        for(int now = t; now != s; now = pre_v[now]) keep.push_back(now);
        keep.push_back(s), reverse(begin(keep), end(keep));
        return keep;
    }
};

int main(){
    int V, E, s, t; cin >> V >> E >> s >> t;

    Weighted_Graph<long long, true> G(V);

    for(int i = 0; i < E; i++){
        int u, v; long long c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    vector<int> path = G.shortest_path(s, t);

    if(path.empty()) cout << "-1\n";
    else{
        cout << G.d[t] << ' ' << (int)path.size()-1 << '\n';
        for(int i = 0; i < (int)path.size()-1; i++){
            cout << path[i] << ' ' << path[i+1] << '\n';
        }
    }
}
