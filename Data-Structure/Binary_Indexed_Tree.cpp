
//Binary-Indexed木
//計算量 構築：O(N)、1点加算・区間和取得・二分探索：O(log(N))
//空間計算量 O(N)

//概要
//ノードを区間に対応させることで、任意のiについて区間[0,i)がO(log(N))個のノードが表す区間のdisjointな和集合として表現される。
//各頂点を被覆するノードはO(log(N))個。
//1点加算：その点を含むノードの値を全て加算する。
//区間和取得：[l,r)の和を求めるとき、[0,r)の和から[0,l)の和を引く。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja
//https://atcoder.jp/contests/practice2/tasks/practice2_b
//https://judge.yosupo.jp/problem/point_add_range_sum

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Binary_Indexed_Tree{
    vector<T> bit;
    const int n;
    
    Binary_Indexed_Tree(const vector<T> &v) : n((int)v.size()){ //vは配列の初期状態
        bit.resize(n+1);
        copy(begin(v), end(v), bit.begin()+1);
        for(int a = 2; a <= n; a <<= 1){
            for(int b = a; b <= n; b += a){
                bit[b] += bit[b-a/2];
            }
        }
    }
    
    void add(int i, const T &x){ //i番目の要素にxを加算する
        for(i++; i <= n; i += (i & -i)) bit[i] += x;
    }

    void change(int i, const T&x){ //i番目の要素をxに変更する
        add(i, x-query(i, i+1));
    }
    
    T sum(int i) const{ //区間[0,i)に含まれる要素の総和
        T ret = 0;
        for(; i > 0; i -= (i & -i)) ret += bit[i];
        return ret;
    }
    
    T query(int l, int r) const{  //区間[l,r)に含まれる要素の総和
        return sum(r) - sum(l);
    }

    T operator [] (int i) const {return query(i, i+1);}

    int lower_bound(T x) const{ //区間[0,a)に含まれる要素の総和がx以上となる最小のa
        int ret = 0;
        for(int k = 31-__builtin_clz(n); k >= 0; k--){
            if(ret+(1<<k) <= n && bit[ret+(1<<k)] < x) x -= bit[ret += (1<<k)]; 
        }
        return ret;
    }

    int upper_bound(T x) const {return lower_bound(x+1);} //区間[0,a)に含まれる要素の総和がx+1以上となる最小のa
};

int main(){
    int N, Q; cin >> N >> Q;

    vector<long long> v(N);
    for(int i = 0; i < N; i++) cin >> v[i];

    Binary_Indexed_Tree<long long> bit(v);
    
    while(Q--){
        int q, x, y; cin >> q >> x >> y;
        if(q == 0) bit.add(x, y);
        else cout << bit.query(x, y) << '\n';
    }
}
