
//列の平方分割(例)
//計算量 各種クエリ：O(√(N*log(N)))

//概要
//バケットサイズをKとする。クエリの計算量は、
//クエリがバケットの一部の箇所にしかかからない所：O(K+log(K)) = O(K)
//クエリがバケットの全体にかかる箇所：O(log(K))
//トータルで見ると：O((N/K)*log(K)+K)
//K = √NとするよりK = √(N*log(N))としたほうが計算量は良くなる。
//ただし、定数倍の重さは考慮しなければならない。

//verified with
//https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Sqrt_Decomposition{
    struct Node{
        const int l, r;
        vector<T> v, sorted, s;
        T u, d, base;
        const T INF_T;

        Node(const vector<T> &a, int l, int r) : l(l), r(r), INF_T(numeric_limits<T>::max()/2){
            v.resize(r-l);
            copy(begin(a)+l, begin(a)+r, begin(v));
            sorted.resize(r-l), s.assign(r-l+1, 0);
            u = INF_T, d = -INF_T, base = 0;
            build();
        }

        void build(){
            copy(begin(v), end(v), begin(sorted));
            sort(begin(sorted), end(sorted));
            for(int i = 0; i < r-l; i++) s[i+1] = s[i]+sorted[i];
        }

        T eval(const T &x) const {return min(u, max(d, x+base));}

        void eval_all(){
            for(auto &e : v) e = eval(e);
            u = INF_T, d = -INF_T, base = 0;
        }

        void query_chmin(int a, int b, const T &x){
            a = max(a, l), b = min(b, r);
            if(a >= b) return;
            if(a == l && b == r) {query_chmin_all(x); return;}
            eval_all();
            for(int i = a-l; i < b-l; i++) v[i] = min(v[i], x);
            build();
        }

        void query_chmin_all(const T &x) {u = min(u, x), d = min(d, u);}

        void query_chmax(int a, int b, const T &x){
            a = max(a, l), b = min(b, r);
            if(a >= b) return;
            if(a == l && b == r) {query_chmax_all(x); return;}
            eval_all();
            for(int i = a-l; i < b-l; i++) v[i] = max(v[i], x);
            build();
        }

        void query_chmax_all(const T &x) {d = max(d, x), u = max(u, d);}

        void query_add(int a, int b, const T &x){
            a = max(a, l), b = min(b, r);
            if(a >= b) return;
            if(a == l && b == r) {query_add_all(x); return;}
            eval_all();
            for(int i = a-l; i < b-l; i++) v[i] += x;
            build();
        }

        void query_add_all(const T &x) {u += x, d += x, base += x;}

        T query_sum(int a, int b){
            a = max(a, l), b = min(b, r);
            if(a >= b) return 0;
            if(a == l && b == r) return query_sum_all();
            eval_all(), build();
            T ret = 0;
            for(int i = a-l; i < b-l; i++) ret += v[i];
            return ret;
        }

        T query_sum_all(){
            int L = lower_bound(begin(sorted), end(sorted), d-base)-begin(sorted);
            int R = lower_bound(begin(sorted), end(sorted), u-base)-begin(sorted);
            return s[R]-s[L]+base*(R-L)+d*L+u*(r-l-R);
        }
    };

    vector<Node> nodes;

    Sqrt_Decomposition(const vector<T> &a, int bucket_size){
        for(int i = 0; i < (int)a.size(); i += bucket_size){
            nodes.emplace_back(a, i, min(i+bucket_size, (int)a.size()));
        }
    }

    void query_chmin(int a, int b, const T &x) {for(auto &e : nodes) e.query_chmin(a, b, x);}

    void query_chmax(int a, int b, const T &x) {for(auto &e : nodes) e.query_chmax(a, b, x);}

    void query_add(int a, int b, const T &x) {for(auto &e : nodes) e.query_add(a, b, x);}

    T query_sum(int a, int b){
        T ret = 0;
        for(auto &e : nodes) ret += e.query_sum(a, b);
        return ret;
    }
};

int main(){
    int N, Q; cin >> N >> Q;

    vector<long long> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];

    Sqrt_Decomposition<long long> sq(a, 200);

    while(Q--){
        int q, l, r; cin >> q >> l >> r;
        if(q == 3) cout << sq.query_sum(l, r) << '\n';
        else{
            long long x; cin >> x;
            if(q == 0) sq.query_chmin(l, r, x);
            if(q == 1) sq.query_chmax(l, r, x);
            if(q == 2) sq.query_add(l, r, x);
        }
    }
}
