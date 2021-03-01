
//頂点のオイラーツアー
//計算量 O(V)

//概要
//根付き木の頂点をDFSで訪問した順(初めてその頂点に到達した場合のみ)に並べると、各頂点より下の部分木は区間に相当する。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2871&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> vs; //DFS順
    vector<int> ls, rs; //iの部分木は区間[ls[i],rs[i])に対応し、vs[ls[i]] = i
    const int n;
    int m;

    Graph(int n) : es(n), ls(n), rs(n), n(n), m(0) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    void euler_tour(int now, int pre = -1){
        ls[now] = vs.size(), vs.push_back(now);
        for(auto &e: es[now]){
            if(e.to != pre) euler_tour(e.to, now);
        }
        rs[now] = vs.size();
    }
};

template<typename Monoid, typename Operator_Monoid>
struct Lazy_Segment_Tree{
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid, Operator_Monoid)>;
    using H = function<Operator_Monoid(Operator_Monoid, Operator_Monoid)>;
    int n, height;
    vector<Monoid> seg;
    vector<Operator_Monoid> lazy;
    const F f;
    const G g;
    const H h;
    const Monoid e1;
    const Operator_Monoid e2;
    
    Lazy_Segment_Tree(const vector<Monoid> &v, const F &f, const G &g, const H &h, const Monoid &e1, const Operator_Monoid &e2)
        : f(f), g(g), h(h), e1(e1), e2(e2){
        int m = v.size();
        n = 1, height = 0;
        while(n < m) n <<= 1, height++;
        seg.assign(2*n, e1), lazy.assign(2*n, e2);
        copy(begin(v), end(v), seg.begin()+n);
        for(int i = n-1; i > 0; i--) seg[i] = f(seg[2*i], seg[2*i+1]);
    }

    inline Monoid reflect(int i) const{
        return (lazy[i] == e2? seg[i] : g(seg[i], lazy[i]));
    }

    inline void recalc(int i){
        while(i >>= 1) seg[i] = f(reflect(2*i), reflect(2*i+1));
    }

    inline void eval(int i){
        if(i < n && lazy[i] != e2){
            lazy[2*i] = h(lazy[2*i] ,lazy[i]);
            lazy[2*i+1] = h(lazy[2*i+1], lazy[i]);
            seg[i] = reflect(i), lazy[i] = e2;
        }
    }

    inline void thrust(int i){
        for(int j = height; j > 0; j--) eval(i>>j);
    }
    
    void apply(int l, int r, const Operator_Monoid &x){
        l = max(l, 0), r = min(r, n);
        if(l >= r) return;
        l += n, r += n;
        thrust(l), thrust(r-1);
        int a = l, b = r;
        while(l < r){
            if(l&1) lazy[l] = h(lazy[l], x), l++;
            if(r&1) r--, lazy[r] = h(lazy[r], x); 
            l >>= 1, r >>= 1;
        }
        recalc(a), recalc(b-1);
    }
    
    Monoid query(int l, int r){
        l = max(l, 0), r = min(r, n);
        if(l >= r) return e1;
        l += n, r += n;
        thrust(l), thrust(r-1);
        Monoid L = e1, R = e1;
        while(l < r){
            if(l&1) L = f(L, reflect(l++));
            if(r&1) R = f(reflect(--r), R);
            l >>= 1, r >>= 1;
        }
        return f(L, R);
    }

    Monoid operator [] (int i) {return query(i, i+1);}

    template<typename C>
    int find_subtree(int i, const C &check, const Monoid &x, Monoid &M, bool type){
        while(i < n){
            eval(i);
            Monoid nxt = type? f(reflect(2*i+type), M) : f(M, reflect(2*i+type));
            if(check(nxt, x)) i = 2*i+type;
            else M = nxt, i = 2*i+(type^1);
        }
        return i-n;
    }
 
    template<typename C>
    int find_first(int l, const C &check, const Monoid &x){
        Monoid L = e1;
        int a = l+n, b = n+n;
        thrust(a);
        while(a < b){
            if(a&1){
                Monoid nxt = f(L, reflect(a));
                if(check(nxt, x)) return find_subtree(a, check, x, L, false);
                L = nxt, a++;
            }
            a >>= 1, b >>= 1;
        }
        return n;
    }
 
    template<typename C>
    int find_last(int r, const C &check, const Monoid &x){
        Monoid R = e1;
        int a = n, b = r+n;
        thrust(b-1);
        while(a < b){
            if(b&1 || a == 1){
                Monoid nxt = f(reflect(--b), R);
                if(check(nxt, x)) return find_subtree(b, check, x, R, true);
                R = nxt;
            }
            a >>= 1, b >>= 1;
        }
        return -1;
    }
};

int main(){
    int V, Q; cin >> V >> Q;

    Graph G(V);
    
    for(int i = 1; i < V; i++){
        int p; cin >> p; p--;
        G.add_edge(p, i);
    }
    G.euler_tour(0);

    using P = pair<int, int>;
    auto f = [](P a, P b) {return P(a.first+b.first, a.second+b.second);};
    auto g = [](P a, int b) {return (b == 0? a : P(a.second, a.first));};
    auto h = [](int a, int b) {return a^b;};

    vector<P> v(V);
    for(int i = 0; i < V; i++){
        char c; cin >> c;
        v[G.ls[i]] = (c == 'G'? P(1, 0) : P(0, 1)); 
    }

    Lazy_Segment_Tree<P, int> seg(v, f, g, h, P(0, 0), 0);

    while(Q--){
        int x; cin >> x; x--;
        seg.apply(G.ls[x], G.rs[x], 1);
        P p = seg.query(0, V);
        cout << (p.first > p.second? "broccoli\n" : "cauliflower\n");
    }
}
