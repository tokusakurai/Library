
//強連結成分分解(分解後はDAGになる)
//計算量 O(E+V)

//概要
//1回目のDFSでは適当な頂点から始めて帰りがけの順で頂点を並べる。
//2回目のDFSでは帰りがけの逆順に頂点を見ていき、逆辺を使って到達できる未訪問の頂点があれば、それらは同じ強連結成分となる。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=ja
//https://judge.yosupo.jp/problem/scc

#include <bits/stdc++.h>
using namespace std;

template<bool directed = true>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    Graph(int n) : es(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }
};

template<bool directed = true>
struct Strongly_Connected_Components{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es, rs;
    vector<int> vs, comp;
    vector<bool> used;
    const int n;
    int m;

    Strongly_Connected_Components(int n) : es(n), rs(n), vs(n), comp(n), used(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m), rs[to].emplace_back(from, m);
        if(!directed) es[to].emplace_back(from, m), rs[from].emplace_back(to, m);
        m++;
    }

    void _dfs(int now){
        used[now] = true;
        for(auto &e: es[now]){
            if(!used[e.to]) _dfs(e.to);
        }
        vs.push_back(now);
    }

    void _rdfs(int now, int cnt){
        used[now] = true, comp[now] = cnt;
        for(auto &e: rs[now]){
            if(!used[e.to]) _rdfs(e.to, cnt);
        }
    }

    Graph<true> decompose(){
        fill(begin(used), end(used), false);
        for(int i = 0; i < n; i++){
            if(!used[i]) _dfs(i);
        }
        fill(begin(used), end(used), false), reverse(begin(vs), end(vs));
        int cnt = 0;
        for(auto &e: vs){
            if(!used[e]) _rdfs(e, cnt++);
        }
        Graph<true> G(cnt);
        for(int i = 0; i < n; i++){
            for(auto &e: es[i]){
                int u = comp[i], v = comp[e.to];
                if(u != v) G.add_edge(u, v);
            }
        }
        return G;
    }

    int operator [] (int k) const {return comp[k];}
};

int main(){
    int V, E; cin >> V >> E;

    Strongly_Connected_Components G(V);

    for(int i = 0; i < E; i++){
        int u, v; cin >> u >> v;
        G.add_edge(u, v);
    }

    int n = G.decompose().n;
    cout << n << '\n';

    vector<vector<int>> ans(n);
    for(int i = 0; i < V; i++) ans[G[i]].push_back(i);

    for(int i = 0; i < n; i++){
        cout << ans[i].size() << ' ';
        for(auto &e: ans[i]) cout << e << ' ';
        cout << '\n';
    }
}