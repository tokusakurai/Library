
//遅延評価付きセグメント木
//計算量 構築：O(N)、区間更新・区間取得・二分探索：O(log(N))
//空間計算量 O(N)

//概要
//区間更新：まず更新される各ノードについて遅延評価を解消してから、遅延配列を更新し、最後に本配列を更新する。
//区間取得：取得する区間の遅延評価を解消する。(ここでは本配列は更新しなくてもよい)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H&lang=ja
//https://atcoder.jp/contests/practice2/tasks/practice2_k
//https://codeforces.com/contest/1404/problem/C

#include <bits/stdc++.h>
using namespace std;

template<typename Monoid, typename Operator_Monoid>
struct Lazy_Segment_Tree{
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid, Operator_Monoid)>;
    using H = function<Operator_Monoid(Operator_Monoid, Operator_Monoid)>;
    int n, height;
    vector<Monoid> seg;
    vector<Operator_Monoid> lazy;
    const F f; //要素と要素の二項演算
    const G g; //要素と作用素の二項演算
    const H h; //作用素と作用素の二項演算
    const Monoid e1; //fの単位元
    const Operator_Monoid e2; //hの単位元
    
    //f(f(a,b),c) = f(a,f(b,c))、f(e1,a) = f(a,e1) = a
    //h(h(p,q),r) = h(p,h(q,r))、h(e2,p) = h(p,e2) = p
    //g(f(a,b),p) = f(g(a,p),g(b,p))
    //g(g(a,p),q) = g(a,h(p,q))
    
    Lazy_Segment_Tree(const vector<Monoid> &v, const F &f, const G &g, const H &h, const Monoid &e1, const Operator_Monoid &e2)
        : f(f), g(g), h(h), e1(e1), e2(e2){
        int m = v.size();
        n = 1, height = 0;
        while(n < m) n <<= 1, height++;
        seg.assign(2*n, e1), lazy.assign(2*n, e2);
        copy(begin(v), end(v), seg.begin()+n);
        for(int i = n-1; i > 0; i--) seg[i] = f(seg[2*i], seg[2*i+1]);
    }

    inline Monoid reflect(int i) const{ //ノードiの実際の値
        return (lazy[i] == e2? seg[i] : g(seg[i], lazy[i]));
    }

    inline void recalc(int i){ //本配列の更新
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
    int N, Q; cin >> N >> Q;

    auto f = [](int a, int b) {return min(a, b);};
    auto g = [](int a, int b) {return a+b;};
    auto h = [](int a, int b) {return a+b;};
    Lazy_Segment_Tree<int, int> seg(vector<int>(N, 0), f, g, h, (1<<30)-1, 0);

    while(Q--){
        int q, x, y; cin >> q >> x >> y; y++;
        if(q == 0){
            int a; cin >> a;
            seg.apply(x, y, a);
        }
        else cout << seg.query(x, y) << '\n';
    }
}
