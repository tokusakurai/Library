
//二重辺連結成分分解(分解後は森になる)
//計算量 O(E+V)

//概要
//Low-Linkを用いる。
//辺(u,v)が橋であればuとvは別の連結成分、そうでなければuとvは同じ連結成分に含まれる。

//verified with
//https://atcoder.jp/contests/arc039/tasks/arc039_d
//https://judge.yosupo.jp/problem/two_edge_connected_components

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
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

template<bool directed = false>
struct Low_Link{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> ord, low;
    vector<bool> used;
    vector<int> articulation, bridge;
    const int n;
    int m;

    Low_Link(int n) : es(n), ord(n), low(n), used(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int dfs(int now, int pre, int k){
        used[now] = true;
        ord[now] = low[now] = k++;
        bool is_articulation = false;
        int cnt = 0;
        for(auto &e: es[now]){
            if(e.id == pre) continue;
            if(!used[e.to]){
                cnt++;
                k = dfs(e.to, e.id, k);
                low[now] = min(low[now], low[e.to]);
                if(pre != -1 && low[e.to] >= ord[now]) is_articulation = true;
                if(ord[now] < low[e.to]) bridge.push_back(e.id);
            }
            else{
                low[now] = min(low[now], ord[e.to]);
            }
        }
        if(pre == -1 && cnt >= 2) is_articulation = true;
        if(is_articulation) articulation.push_back(now);
        return k;
    }

    void build(){
        fill(begin(used), end(used), false);
        int k = 0;
        for(int i = 0; i < n; i++){
            if(!used[i]) k = dfs(i, -1, k);
        }
    }
};

template<bool directed = false>
struct Two_Edge_Connected_Components : Low_Link<directed>{
    using L = Low_Link<directed>;
    vector<int> comp;
    const int n;

    Two_Edge_Connected_Components(int n) : L(n), comp(n), n(n) {}

    int dfs(int now, int pre, int k){
        if(pre != -1 && this->ord[pre] >= this->low[now]) comp[now] = comp[pre];
        else comp[now] = k++;
        for(auto &e: this->es[now]){
            if(comp[e.to] == -1) k = dfs(e.to, now, k);
        }
        return k;
    }

    Graph<directed> decompose(){ //分解後のグラフを返す
        this->build();
        fill(begin(comp), end(comp), -1);
        int k = 0;
        for(int i = 0; i < n; i++){
            if(comp[i] == -1) k = dfs(i, -1, k);
        }
        Graph<directed> ret(k);
        vector<int> is_bridge(this->m, 0);
        for(auto &e: this->bridge) is_bridge[e]++;
        for(int i = 0; i < n; i++){
            for(auto &e: this->es[i]){
                if(is_bridge[e.id]-- > 0){
                    ret.add_edge(comp[i], comp[e.to]);
                }
            }
        }
        return ret;
    }

    int operator [] (int i) const {return comp[i];}
};

int main(){
    int V, E; cin >> V >> E;

    Two_Edge_Connected_Components G(V);
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
