
//重みなし木の基本的なDFS
//計算量 根からの距離・部分木のサイズ・直径・パス検出：O(V)

//直径：最短距離が最大になるような2点間の単純パス

//概要
//根からの距離・部分木のサイズ：木上でDPを行っているとみることができる。
//直径：適当に頂点を決めて、その頂点から最も遠い点をsとし、sから最も遠い点をtとすると、パスs-tは直径となる。

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> d, si;
    vector<int> keep;
    const int n;
    int m;

    Graph(int n) : es(n), d(n), si(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    void calc_depth(int now, int pre = -1){ //calc_depth(root)でrootからの距離を配列dに記録する
        if(pre == -1) d[now] = 0;
        for(auto &e: es[now]){
            if(e.to != pre){
                d[e.to] = d[now]+1, calc_depth(e.to, now);
            }
        }
    }

    int calc_size(int now, int pre = -1){ //calc_size(root)でrootを根として見たときの各頂点の部分木のサイズを配列siに記録する
        si[now] = 1;
        for(auto &e: es[now]){
            if(e != pre) si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    int farthest_point(int s){ //sから最も遠い点
        calc_depth(s);
        int max_d = -1, t = -1;
        for(int i = 0; i < n; i++){
            if(d[i] > max_d) max_d = d[i], t = i;
        }
        return t;
    }

    pair<int, pair<int, int>> diameter(){ //直径の長さ、直径の両端の点を返す
        int a = farthest_point(0), b = farthest_point(a);
        return make_pair(d[b], make_pair(a, b));
    }

    bool trace(int now, int t, int pre = -1){
        if(now == t){
            keep.push_back(now);
            return true;
        }
        for(auto &e: es[now]){
            if(e.to == pre) continue;
            if(trace(e.to, t, now)){
                keep.push_back(now);
                //keep.push_back(e.id);
                return true;
            }
        }
        return false;
    }

    vector<int> find_path(int s, int t){ //s-tパスを検出
        keep.clear();
        trace(s, t);
        reverse(begin(keep), end(keep));
        return keep;
    }
};

int main(){
    int V; cin >> V;

    Graph G(V);
    for(int i = 0; i < V-1; i++){
        int u, v; cin >> u >> v;
        G.add_edge(u, v);
    }

    pair<int, pair<int, int>> p = G.diameter();

    auto [s, t] = p.second;
    vector<int> path = G.find_path(s, t);

    cout << p.first << ' ' << path.size() << '\n';
    for(auto &e: path) cout << e << ' ';
    cout << '\n';
}
