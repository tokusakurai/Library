
//Moのアルゴリズム(例)
//計算量 O((N+Q)*√N)

//概要
//区間の伸縮をO(1)で行えるため、計算量はO((N+Q)*√N)

//verified with
//https://atcoder.jp/contests/abc174/tasks/abc174_f

#include <bits/stdc++.h>
using namespace std;

struct query{
    int l, r, id;
    query(int l, int r, int id) : l(l), r(r), id(id) {}
};

template<typename T, typename Q>
struct Mo{
    vector<T> a;
    const int n;
    int l, r;
    Q ans;
    vector<int> cnt;

    Mo(vector<T> a) : a(a), n(a.size()), l(0), r(0), ans(0), cnt(a.size(), 0) {}

    void insert(T x){
        if(cnt[x]++ == 0) ans++;
    }

    void erase(T x){
        if(--cnt[x] == 0) ans--;
    }

    vector<Q> solve(int bucket_size, vector<query> qs){
        vector<Q> ret(qs.size());
        sort(begin(qs), end(qs), [&](query a, query b){
            int A = (a.l)/bucket_size, B = (b.l)/bucket_size;
            if(A != B) return A < B;
            if(A%2 == 0) return a.r < b.r;
            return a.r > b.r;
        });
        for(auto &e: qs){
            while(e.l < l) insert(a[--l]);
            while(r < e.r) insert(a[r++]);
            while(l < e.l) erase(a[l++]);
            while(e.r < r) erase(a[--r]);
            ret[e.id] = ans;
        }
        return ret;
    }
};

int main(){
    int N, Q; cin >> N >> Q;

    vector<int> a(N);
    for(int i = 0; i < N; i++) {cin >> a[i]; a[i]--;}

    Mo<int, int> mo(a);

    vector<query> qs;
    for(int i = 0; i < Q; i++){
        int l, r; cin >> l >> r; l--;
        qs.emplace_back(l, r, i);
    }

    for(auto &e: mo.solve(700, qs)) cout << e << '\n';
}
