
//Ford-Fulkerson法(最大流)
//計算量 O(F*E)

//残余グラフにおいて容量が正の辺のみからなるパス(増加パス)をDFSで探索し、流せるだけ流す。
//ステップ回数は最大でF回
//逆辺の初期容量は、有向グラフの場合：0、無向グラフの場合：正辺の容量と同じ

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename F> //流量の型
struct Max_Flow{
    struct edge{
        int to; F cap; int rev;
        edge(int to, F cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> es;
    vector<bool> used;
    const F INF_F;
    const int n;

    Max_Flow(int n) : es(n), used(n), INF_F(numeric_limits<F>::max()), n(n) {}

    void add_edge(int from, int to, F cap, bool directed = true){
        es[from].emplace_back(to, cap, (int)es[to].size());
        es[to].emplace_back(from, directed? 0 : cap, (int)es[from].size()-1);
    }

    F _dfs(int now, int t, F flow){
        if(now == t) return flow;
        used[now] = true;
        for(auto &e: es[now]){
            if(!used[e.to] && e.cap > 0){
                F f = _dfs(e.to, t, min(flow, e.cap));
                if(f > 0){
                    e.cap -= f, es[e.to][e.rev].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }

    F max_flow(int s, int t){ //s-t最大流を求める、操作後のused配列は最小カットの取り方の1つを表している
        F flow = 0;
        for(;;){
            fill(begin(used), end(used), false);
            F f = _dfs(s, t, INF_F);
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
