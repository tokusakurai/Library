
//無向グラフでの基本的なDFS
//計算量 パス検出・閉路検出:O(E+V)

//verified with
//https://yukicoder.me/problems/no/1254

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> used;
    vector<int> keep;
    const int n;
    int m;

    Graph(int n) : es(n), used(n), n(n), m(0) {}

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
        for(auto &e : es[now]){
            if(used[e.to]) continue;
            if(trace(e.to, t)){
                //keep.emplace_back(now);
                keep.emplace_back(e.id);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t){ //sからtへのパスを検出
        keep.clear(), fill(begin(used), end(used), 0);
        trace(s, t), reverse(begin(keep), end(keep));
        return keep;
    }

    int detect(int now, int pre = -1){
        if(used[now]++) return 1;
        for(auto &e: es[now]){
            if(e.id == pre) continue;
            int k = detect(e.to, e.id);
            if(k == 2) return 2;
            if(k == 1){
                //keep.emplace_back(now);
                keep.emplace_back(e.id);
                return used[now];
            }
        }
        return 0;
    }

    vector<int> find_loop(){ //閉路を検出
        keep.clear(), fill(begin(used), end(used), 0);
        for(int i = 0; i < n; i++){
            if(used[i]) continue;
            detect(i);
            if(!keep.empty()){
                reverse(begin(keep), end(keep));
                return keep;
            }
        }
        return {};
    }
};

int main(){
    int V; cin >> V;

    Graph G(V);

    for(int i = 0; i < V; i++){
        int u, v; cin >> u >> v; u--, v--;
        G.add_edge(u, v);
    }
    
    vector<int> loop = G.find_loop();

    cout << loop.size() << '\n';
    for(auto &e: loop) cout << e+1 << ' ';
    cout << '\n';
}
