
//セグメント木
//計算量 構築:O(N)、1点更新・区間取得・二分探索:O(log(N))
//空間計算量 O(N)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
//https://atcoder.jp/contests/practice2/tasks/practice2_j
//https://codeforces.com/contest/1407/problem/D

#include <bits/stdc++.h>
using namespace std;

template<typename Monoid>
struct Segment_Tree{
    using F = function<Monoid(Monoid, Monoid)>;
    int n;
    vector<Monoid> seg;
    const F f; //要素と要素をマージする二項演算
    const Monoid e1; //単位元
    
    //f(f(a,b),c) = f(a,f(b,c))、 f(e1,a) = f(a,e1) = a
    
    Segment_Tree(const vector<Monoid> &v, const F &f, const Monoid &e1) : f(f), e1(e1){ //vは配列の初期状態
        int m = v.size();
        n = 1;
        while(n < m) n <<= 1;
        seg.assign(2*n, e1);
        copy(begin(v), end(v), seg.begin()+n);
        for(int i = n-1; i > 0; i--) seg[i] = f(seg[2*i], seg[2*i+1]);
    }
    
    void change(int i, const Monoid &x){ //i番目の要素をxに変更
        seg[i += n] = x;
        while(i >>= 1){
            seg[i] = f(seg[2*i], seg[2*i+1]);
        }
    }

    Monoid query(int l, int r) const{ //区間[l,r)での演算の結果
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
    int find_first(int l, const C &check, const Monoid &x) const{ //区間[l,r)での演算の結果がxとcで与えられる条件を満たす最小のr
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
    int find_last(int r, const C &check, const Monoid &x) const{ //区間[l,r)での演算の結果がxとcで与えられる条件を満たす最大のl
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
    int N, Q; cin >> N >> Q;
    
    vector<int> v(N);
    for(int i = 0; i < N; i++) cin >> v[i];

    auto f = [](int a, int b) {return max(a, b);};
    auto c = [](int a, int b) {return a >= b;};
    Segment_Tree<int> seg(v, f, 1-(1<<30));

    while(Q--){
        int q, x, y; cin >> q >> x >> y; x--;
        if(q == 1) seg.change(x, y);
        if(q == 2) cout << seg.query(x, y) << '\n';
        if(q == 3){
            int ans = seg.find_first(x, c, y);
            cout << (ans >= N? N+1 : ans+1) << '\n';
        }
    }
}
