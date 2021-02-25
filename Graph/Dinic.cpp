
//Dinic法(最大流)
//計算量 O(E*V^2)

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
    vector<int> d, pos;
    const T INF_T;
    const int n;

    Max_Flow(int n) : es(n), d(n), pos(n), INF_T(numeric_limits<T>::max()), n(n) {}

    void add_edge(int from, int to, T cap){
        es[from].emplace_back(to, cap, (int)es[to].size());
        es[to].emplace_back(from, directed? 0 : cap, (int)es[from].size()-1);
    }

    bool bfs(int s, int t){
        fill(begin(d), end(d), -1);
        queue<int> que;
        d[s] = 0, que.push(s);
        while(!que.empty()){
            int i = que.front(); que.pop();
            for(auto &e: es[i]){
                if(e.cap > 0 && d[e.to] == -1){
                    d[e.to] = d[i]+1, que.push(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    T dfs(int now, int t, T flow){
        if(now == t) return flow;
        for(int &i = pos[now]; i < (int)es[now].size(); i++){
            edge &e = es[now][i];
            if(e.cap > 0 && d[e.to] > d[now]){
                T f = dfs(e.to, t, min(flow, e.cap));
                if(f > 0){
                    e.cap -= f;
                    es[e.to][e.rev].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }

    T max_flow(int s, int t){
        T flow = 0;
        while(bfs(s, t)){
            fill(begin(pos), end(pos), 0);
            T f = 0;
            while((f = dfs(s, t, INF_T)) > 0) flow += f;
        }
        return flow;
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
