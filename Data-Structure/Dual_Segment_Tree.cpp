
//双対セグメント木
//計算量 構築：O(N)、区間更新・1点取得：O(log(N))
//空間計算量 O(N)

//概要
//遅延評価を用いることでセグメント木と逆の流れの操作ができる。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T, typename Operator_Monoid> //要素、作用素の型
struct Dual_Segment_Tree{
    using G = function<T(T, Operator_Monoid)>;
    using H = function<Operator_Monoid(Operator_Monoid, Operator_Monoid)>;
    int n, height;
    vector<T> seg;
    vector<Operator_Monoid> lazy;
    const G g; //要素と作用素の二項演算
    const H h; //作用素と作用素の二項演算
    const Operator_Monoid e2; //hの単位元
    
    //h(h(p,q),r) = h(p,h(q,r))、h(e2,p) = h(p,e2) = p
    //g(g(a,p),q) = g(a,h(p,q))

    Dual_Segment_Tree(const vector<T> &v, const G &g, const H &h, const Operator_Monoid &e2) : g(g), h(h), e2(e2){
        int m = v.size();
        n = 1, height = 0;
        while(n < m) n <<= 1, height++;
        lazy.assign(2*n, e2);
        seg = v;
    }

    inline void eval(int i){
        if(i < n && lazy[i] != e2){
            lazy[2*i] = h(lazy[2*i], lazy[i]);
            lazy[2*i+1] = h(lazy[2*i+1], lazy[i]);
            lazy[i] = e2;
        }
    }

    inline void thrust(int i){
        for(int j = height; j > 0; j--) eval(i>>j);
    }

    void apply(int l, int r, const Operator_Monoid &x){ //区間[l,r)に作用素xを適用
        l = max(l, 0), r = min(r, n);
        if(l >= r) return;
        l += n, r += n;
        thrust(l), thrust(r-1);
        while(l < r){
            if(l&1) lazy[l] = h(lazy[l], x), l++;
            if(r&1) r--, lazy[r] = h(lazy[r], x);
            l >>= 1, r >>= 1;
        }
    }

    T get(int i){ //i番目の要素
        thrust(i+n);
        return g(seg[i], lazy[i+n]);
    }

    T operator [] (int i) {return get(i);}
};

int main(){
    int N, Q; cin >> N >> Q;

    auto g = [](int a, int b) {return b == -1? a : b;};
    auto h = [](int a, int b) {return b == -1? a : b;};
    Dual_Segment_Tree<int, int> seg(vector<int>(N, INT_MAX), g, h, -1);

    while(Q--){
        int q, x; cin >> q >> x;
        if(q == 0){
            int y, a; cin >> y >> a; y++;
            seg.apply(x, y, a);
        }
        else cout << seg.get(x) << '\n';
    }
}
