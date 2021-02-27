
//有向グラフでの基本的なDFS
//計算量 パス検出・トポロジカルソート・閉路検出:O(E+V)

//概要
//直前に使用した辺を戻らないようにしてDFSをする。
//パス検出：目的の点に到達したら探索を打ち切って、来たパスを戻ることで復元する。
//閉路検出：トポロジカルソートして、逆方向に戻る辺があれば閉路が存在する。

//verified with
//https://judge.yosupo.jp/problem/cycle_detection

#include <bits/stdc++.h>
using namespace std;

template<bool directed = true>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<bool> used;
    vector<int> vs, topo;
    vector<int> keep;
    const int n;
    int m;

    Graph(int n) : es(n), used(n), topo(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    bool trace(int now, int t){
        used[now] = true;
        if(now == t){
            //keep.emplace_back(now)
            return true;
        }
        for(auto &e: es[now]){
            if(used[e.to]) continue;
            if(trace(e.to, t)){
                //keep.emplace_back(now);
                keep.emplace_back(e.id);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t){
        keep.clear(), fill(begin(used), end(used), 0);
        trace(s, t), reverse(begin(keep), end(keep));
        return keep;
    }

    void topological_sort(int now){
        used[now] = true;
        int s = 0;
        for(auto &e: es[now]){
            if(!used[e.to]) topological_sort(e.to);
        }
        topo[now] = vs.size(), vs.push_back(now);
    }

    vector<int> find_loop(){
        keep.clear(), fill(begin(used), end(used), 0);
        for(int i = 0; i < n; i++){
            if(!used[i]) topological_sort(i);
        }
        for(int i = 0; i < n; i++){
            for(auto &e: es[i]){
                if(topo[i] <= topo[e.to]){
                    vector<int> ret = find_path(e.to, i);
                    ret.push_back(e.id);
                    return ret;
                }
            }
        }
        return {};
    }
};

int main(){
    int V, E; cin >> V >> E;

    Graph G(V);

    for(int i = 0; i < E; i++){
        int u, v; cin >> u >> v;
        G.add_edge(u, v);
    }
    
    vector<int> loop = G.find_loop();

    if(loop.empty()) cout << -1 << endl;
    else{
        cout << loop.size() << '\n';
        for(auto &e: loop) cout << e << '\n';
    }
}
