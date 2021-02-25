
//重み付き木の基本的なDFS
//計算量 根からの距離・部分木のサイズ・直径・パス検出:O(V)

//直径 : 最短距離が最大になるような2点間のパス

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=ja
//https://judge.yosupo.jp/problem/tree_diameter

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
    vector<int> si;
    vector<int> keep;
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : d(n), si(n), es(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    void calc_depth(int now, int pre = -1){
        if(pre == -1) d[now] = 0;
        for(auto &e: es[now]){
            if(e.to != pre){
                d[e.to] = d[now]+e.cost, calc_depth(e.to, now);
            }
        }
    }

    int calc_size(int now, int pre = -1){
        si[now] = 1;
        for(auto &e: es[now]){
            if(e != pre) si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    int farthest_point(int s){
        calc_depth(s);
        T max_d = -1;
        int t = -1;
        for(int i = 0; i < n; i++){
            if(d[i] > max_d) max_d = d[i], t = i;
        }
        return t;
    }

    pair<T, pair<int, int>> diameter(){
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

    vector<int> find_path(int s, int t){
        keep.clear();
        trace(s, t);
        reverse(begin(keep), end(keep));
        return keep;
    }
};

int main(){
    int V; cin >> V;

    Weighted_Graph<long long> G(V);
    for(int i = 0; i < V-1; i++){
        int u, v; long long c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    pair<long long, pair<int, int>> p = G.diameter();

    auto [s, t] = p.second;
    vector<int> path = G.find_path(s, t);

    cout << p.first << ' ' << path.size() << '\n';

    for(int i = 0; i < (int)path.size(); i++){
        cout << path[i] << (i == (int)path.size()-1? '\n' : ' ');
    }
}
