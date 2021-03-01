
//Heavy-Light分解
//計算量 HL分解：O(V)、パスが通る区間の個数：O(log(V))

//概要
//根付き木の各頂点の重みを、その頂点を根とする部分木の頂点数とする。
//各頂点について、子のうち重みが最大のものとの間の辺のみを残す。
//結果として木はいくつかの列に分割され、任意の2頂点間の単純パスについて通る列の個数は最大でO(log(V))個となる。

//verified with
//https://judge.yosupo.jp/problem/vertex_add_path_sum

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> par, si, depth;
    vector<int> root, comp; //属する連結成分の根、連結成分内の深さの順位
    vector<vector<int>> ids;
    const int n;
    int m;

    Graph(int n) : es(n), par(n), si(n), depth(n), root(n), comp(n), ids(n), n(n) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int dfs1(int now, int pre = -1){
        par[now] = pre;
        if(pre == -1) depth[now] = 0;
        si[now] = 1;
        for(auto &e: es[now]){
            if(e.to != pre){
                depth[e.to] = depth[now]+1;
                si[now] += dfs1(e.to, now);
            }
        }
        return si[now];
    }

    void dfs2(int now, bool st, int pre = -1){
        if(st) root[now] = now, comp[now] = 0;
        else root[now] = root[pre], comp[now] = comp[pre]+1;
        ids[root[now]].push_back(now);
        int c = -1, M = 0;
        for(auto &e: es[now]){
            if(e.to == pre) continue;
            if(M < si[e.to]) M = si[e.to], c = e.to;
        }
        for(auto &e: es[now]){
            if(e.to != pre) dfs2(e.to, c != e.to, now);
        }
    }

    void decompose(int root = 0){
        dfs1(root);
        dfs2(root, true);
    }

    vector<tuple<int, int, int>> find_path(int u, int v){ //通ったパスの(親、左端、右端)の組を返す
        vector<tuple<int, int, int>> ret;
        while(root[u] != root[v]){
            if(depth[root[u]] > depth[root[v]]) swap(u, v);
            ret.emplace_back(root[v], 0, comp[v]+1);
            v = par[root[v]];
        }
        if(depth[u] > depth[v]) swap(u, v);
        ret.emplace_back(root[u], comp[u], comp[v]+1);
        return ret;
    }
};

template<typename T>
struct Binary_Indexed_Tree{
    vector<T> bit;
    const int n;
    
    Binary_Indexed_Tree(const vector<T> &v) : n((int)v.size()){
        bit.resize(n+1);
        copy(begin(v), end(v), begin(bit)+1);
        for(int a = 2; a <= n; a <<= 1){
            for(int b = a; b <= n; b += a){
                bit[b] += bit[b-a/2];
            }
        }
    }
    
    void add(int i, const T &x){
        for(i++; i <= n; i += (i & -i)) bit[i] += x;
    }

    void change(int i, const T&x){
        add(i, x-query(i, i+1));
    }
    
    T sum(int i) const{
        T ret = 0;
        for(; i > 0; i -= (i & -i)) ret += bit[i];
        return ret;
    }
    
    T query(int l, int r) const{
        return sum(r) - sum(l);
    }

    T operator [] (int i) const {return query(i, i+1);}

    int lower_bound(T x) const{
        int ret = 0;
        for(int k = 31-__builtin_clz(n); k >= 0; k--){
            if(ret+(1<<k) <= n && bit[ret+(1<<k)] < x) x -= bit[ret += (1<<k)]; 
        }
        return ret;
    }

    int upper_bound(T x) const {return lower_bound(x+1);}
};

int main(){
    int V, Q; cin >> V >> Q;

    vector<long long> a(V);
    for(int i = 0; i < V; i++) cin >> a[i];

    Graph G(V);

    for(int i = 0; i < V-1; i++){
        int u, v; cin >> u >> v;
        G.add_edge(u, v);
    }

    G.decompose();

    vector<Binary_Indexed_Tree<long long>> bits;

    for(int i = 0; i < V; i++){
        vector<long long> v;
        for(auto &e: G.ids[i]) v.push_back(a[e]);
        bits.emplace_back(v);
    }

    while(Q--){
        int q; cin >> q;

        if(q == 0){
            int p; long long x; cin >> p >> x;
            bits[G.root[p]].add(G.comp[p], x);
        }
        else{
            int u, v; cin >> u >> v;
            long long ret = 0;
            for(auto &e: G.find_path(u, v)){
                ret += bits[get<0>(e)].query(get<1>(e), get<2>(e));
            }
            cout << ret << '\n';
        }
    }
}
