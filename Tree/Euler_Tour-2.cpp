
//辺のオイラーツアー
//計算量 O(V)

//概要
//根付き木の頂点と辺をDFSで訪問した順(戻るときに使った辺や頂点もカウントする)に並べる。
//辺(u,v)と辺(v,u)が互いに打ち消し合うようにできればパスを区間としてみなすことができる。

//verified with
//https://atcoder.jp/contests/abc014/tasks/abc014_4

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Weighted_Graph{
    struct edge{
        int to; T cost; int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> vs, edges; //辺を親方向にたどるときは-mして記録
    vector<int> ls, rs, depth; //vsの中でiのもののindexの最小値がls[i]、最大値がrs[i]
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), ls(n), rs(n), depth(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    void euler_tour(int now, int pre = -1){
        if(pre == -1) depth[now] = 0;
        vs.push_back(now);
        ls[now] = edges.size();
        for(auto &e: es[now]){
            if(e.to == pre) continue;
            edges.push_back(e.id);
            depth[e.to] = depth[now]+1, euler_tour(e.to, now);
            vs.push_back(now), edges.push_back(e.id-m);
        }
        rs[now] = edges.size();
    }
};

template<typename Monoid>
struct Segment_Tree{
    using F = function<Monoid(Monoid, Monoid)>;
    int n;
    vector<Monoid> seg;
    const F f;
    const Monoid e1;
    
    Segment_Tree(const vector<Monoid> &v, const F &f, const Monoid &e1) : f(f), e1(e1){
        int m = v.size();
        n = 1;
        while(n < m) n <<= 1;
        seg.assign(2*n, e1);
        copy(begin(v), end(v), begin(seg)+n);
        for(int i = n-1; i > 0; i--) seg[i] = f(seg[2*i], seg[2*i+1]);
    }
    
    void change(int i, const Monoid &x){
        seg[i += n] = x;
        while(i >>= 1){
            seg[i] = f(seg[2*i], seg[2*i+1]);
        }
    }

    Monoid query(int l, int r) const{
        Monoid L = e1, R = e1;
        l += n, r += n;
        while(l < r){
            if(l&1) L = f(L, seg[l++]);
            if(r&1) R = f(seg[--r], R);
            l >>= 1, r >>= 1;
        }
        return f(L, R);
    }
 
    Monoid operator [] (int i) const {return seg[n+i];}
 
    template<typename C>
    int find_subtree(int i, const C &check, const Monoid &x, Monoid &M, bool type) const{
        while(i < n){
            Monoid nxt = type? f(seg[2*i+type], M) : f(M, seg[2*i+type]);
            if(check(nxt, x)) i = 2*i+type;
            else M = nxt, i = 2*i+(type^1);
        }
        return i-n;
    }
 
    template<typename C>
    int find_first(int l, const C &check, const Monoid &x) const{
        Monoid L = e1;
        int a = l+n, b = n+n;
        while(a < b){
            if(a&1){
                Monoid nxt = f(L, seg[a]);
                if(check(nxt, x)) return find_subtree(a, check, x, L, false);
                L = nxt, a++;
            }
            a >>= 1, b >>= 1;
        }
        return n;
    }
 
    template<typename C>
    int find_last(int r, const C &check, const Monoid &x) const{
        Monoid R = e1;
        int a = n, b = r+n;
        while(a < b){
            if(b&1 || a == 1){
                Monoid nxt = f(seg[--b], R);
                if(check(nxt, x)) return find_subtree(b, check, x, R, true);
                R = nxt;
            }
            a >>= 1, b >>= 1;
        }
        return -1;
    }
};

int main(){
    int V; cin >> V;

    Weighted_Graph<int> G(V);

    for(int i = 0; i < V-1; i++){
        int u, v; cin >> u >> v; u--, v--;
        G.add_edge(u, v, 1);
    }

    G.euler_tour(0);
    
    using P = pair<int, int>;
    auto f1 = [](P a, P b) {return min(a, b);};
    auto f2 = [](int a, int b) {return a+b;};

    vector<P> v1(2*V-1);
    for(int i = 0; i < 2*V-1; i++){
        int j = G.vs[i];
        v1[i] = P(G.depth[j], j);
    }

    vector<int> v2(2*V-2);
    for(int i = 0; i < 2*V-2; i++){
        v2[i] = (G.edges[i] >= 0? 1 : -1);
    }

    Segment_Tree<P> seg1(v1, f1, P(INT_MAX, -1));
    Segment_Tree<int> seg2(v2, f2, 0);

    int Q; cin >> Q;

    while(Q--){
        int u, v; cin >> u >> v; u--, v--;
        u = G.ls[u], v = G.ls[v];
        if(u > v) swap(u, v);
        int w = seg1.query(u, v).second;
        w = G.ls[w];
        cout << seg2.query(w, u)+seg2.query(w, v)+1 << '\n';
    }
}
