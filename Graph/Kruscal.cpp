
//クラスカル法(最小全域木)
//計算量 O(E*log(E))

//概要
//辺をコストの昇順にソートする。
//Union-Find木を用いる。
//上から辺を見ていって、両端が別の連結成分に属していればその辺を採用し、そうでなければ棄却する。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp

#include <bits/stdc++.h>
using namespace std;

struct Union_Find_Tree{
    vector<int> data;
    const int n;
    
    Union_Find_Tree(int n) : data(n, -1), n(n) {}
    
    int root(int x){
        if(data[x] < 0) return x;
        return data[x] = root(data[x]);
    }

    int operator [] (int i) {return root(i);}
    
    bool unite(int x, int y){
        x = root(x), y = root(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y], data[y] = x;
        return true;
    }
    
    int size(int x) {return -data[root(x)];}
    
    bool same(int x, int y) {return root(x) == root(y);}
    
    void clear() {fill(begin(data), end(data), -1);}
};

template<typename T, bool directed = false>
struct Edges{
    struct edge{
        int from, to; T cost; int id;
        edge(int from, int to, T cost, int id) : from(from), to(to), cost(cost), id(id) {}
    };

    vector<edge> es;
    const T INF_T;
    const int n;
    int m;

    Edges(int n) : INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es.emplace_back(from, to, cost, m);
        if(!directed) es.emplace_back(to, from, cost, m);
        m++;
    }

    T kruscal(){
        sort(begin(es), end(es), [](const edge &e1, const edge &e2){
            return e1.cost < e2.cost;
        });
        Union_Find_Tree uf(n);
        T ret = 0;
        for(auto &e: es){
            if(uf.unite(e.from, e.to)) ret += e.cost;
        }
        if(uf.size(0) < n) return INF_T;
        return ret;
    }
};

int main(){
    int V, E; cin >> V >> E;

    Edges<int> G(V);
    for(int i = 0; i < E; i++){
        int u, v, c; cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    cout << G.kruscal() << '\n';
}
