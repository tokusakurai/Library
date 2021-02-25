
//スパーステーブル
//計算量 構築:O(N*log(N))、区間取得:(O(1))
//空間計算量 O(N*log(N))

//verified with
//https://judge.yosupo.jp/problem/staticrmq

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Sparse_Table{
    using F = function<T(T, T)>;
    const int n;
    vector<vector<T>> st; //st[j][i] := 区間[i,i+2^j)での演算の結果
    vector<int> lookup;
    const F f; //二項演算
    const T e; //単位元
    
    //f(f(a,b),c) = f(a,f(b,c))、f(e,a) = f(a,e) = a、f(a,a) = a 
    //例えばminやgcdはこれらを満たすが、+や*は満たさない

    Sparse_Table(const vector<T> &table, const F &f, const T &e) : n((int)table.size()), f(f), e(e){ //tableは配列の初期状態
        int log_n = 32-__builtin_popcount(n);
        st.assign(log_n, vector<T>(n));
        for(int i = 0; i < n; i++) st[0][i] = table[i];
        for(int j = 0; j < log_n-1; j++){
            for(int i = 0; i < n; i++){
                if(i+(1<<j) < n) st[j+1][i] = f(st[j][i], st[j][i+(1<<j)]);
                else st[j+1][i] = st[j][i];
            }
        }
        lookup.assign(n+1, -1);
        for(int i = 1; i <= n; i++) lookup[i] = lookup[i/2]+1;
    }

    T query(int l, int r) const{ //区間[l,r)での演算の結果
        if(l >= r) return e;
        int k = lookup[r-l];
        return f(st[k][l], st[k][r-(1<<k)]);
    }

    T operator [] (int i) const {return st[0][i];}
};

int main(){
    int N, Q; cin >> N >> Q;

    vector<int> table(N);
    for(int i = 0; i < N; i++) cin >> table[i];

    auto f = [](int a, int b) {return min(a, b);};
    Sparse_Table<int> st(table, f, (1<<30)-1);

    while(Q--){
        int l, r; cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }
}
