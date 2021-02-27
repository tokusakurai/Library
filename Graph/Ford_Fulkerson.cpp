
//Ford-Fulkerson法(最大流)
//計算量 O(F*E)

//残余グラフにおいて容量が正の辺のみからなるパス(増加パス)をDFSで探索し、流せるだけ流す。
//ステップ回数は最大でF回
//逆辺の初期容量は、有向グラフの場合：0、無向グラフの場合：正辺の容量と同じ

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = true>
struct Max_Flow{
    struct edge{
        int to; T cap; int rev;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> es;
    vector<bool> used;
    const T INF_T;
    const int n;

    Max_Flow(int n) : es(n), used(n), INF_T(numeric_limits<T>::max()), n(n) {}

    void add_edge(int from, int to, T cap){
        es[from].emplace_back(to, cap, (int)es[to].size());
        es[to].emplace_back(from, directed? 0 : cap, (int)es[from].size()-1);
    }

    T dfs(int now, int t, T flow){
        if(now == t) return flow;
        used[now] = true;
        for(auto &e: es[now]){
            if(!used[e.to] && e.cap > 0){
                T f = dfs(e.to, t, min(flow, e.cap));
                if(f > 0){
                    e.cap -= f, es[e.to][e.rev].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }

    T max_flow(int s, int t){
        T flow = 0;
        for(;;){
            fill(begin(used), end(used), false);
            T f = dfs(s, t, INF_T);
            if(f == 0) return flow;
            flow += f;
        }
    }
};

int main(){
    int V, E; cin >> V >> E;

    Max_Flow<int> G(V);
    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    cout << G.max_flow(0, V-1) << '\n';
}
