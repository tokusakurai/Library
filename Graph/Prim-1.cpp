
//プリム法(最小全域木)
//計算量 O(V^2)

//概要
//ある頂点から始めて1つずつ辺を加えて木を構成する。
//今木に含まれている頂点と木に含まれていない頂点を結ぶ辺のうち、もっともコストが小さいものを採用する。
//各ステップで、木に含まれていない頂点を全てチェックする。

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Table{
    vector<vector<T>> es;
    const T INF_T;
    const int n;

    inline const vector<T> &operator [] (int k) const{
        return es[k];
    }

    inline vector<T> &operator [] (int k){
        return es[k];
    }

    Table(int n) : es(n), INF_T(numeric_limits<T>::max()/2), n(n){
        for(int i = 0; i < n; i++) es[i].assign(n, INF_T);
        for(int i = 0; i < n; i++) es[i][i] = 0;
    }

    void add_edge(int from, int to, T cost = 1){
        es[from][to] = min(es[from][to], cost);
        if(!directed) es[to][from] = min(es[to][from], cost);
    }

    T prim(){
        vector<T> mincost(n, INF_T); //木に含まれる頂点と自身を結ぶ辺のコストの最小値
        vector<bool> used(n, false);
        mincost[0] = 0;
        T ret = 0;
        for(int i = 0; i < n; i++){
            int u = -1;
            for(int j = 0; j < n; j++){
                if(used[j]) continue;
                if(u == -1 || mincost[j] < mincost[u]) u = j;
            }
            if(mincost[u] == INF_T) continue;
            used[u] = true;
            ret += mincost[u];
            for(int j = 0; j < n; j++){
                mincost[j] = min(mincost[j], es[u][j]);
            }
        }
        for(int i = 0; i < n; i++) if(!used[i]) return INF_T;
        return ret;
    }
};

int main(){
    int V, E; cin >> V >> E;

    Table<int> G(V);

    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    cout << G.prim() << '\n';
}
