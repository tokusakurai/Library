
//Moのアルゴリズム(雛形)
//計算量 O(α*(N+Q)*√N) (αは区間を伸縮させるのに必要な計算量)

#include <bits/stdc++.h>
using namespace std;

struct query{
    int l, r, id;
    query(int l, int r, int id) : l(l), r(r), id(id) {}
};
 
template<typename T, typename Q> //Tは配列の要素の型、Qはクエリに対する答えの型
struct Mo{
    vector<T> a;
    const int n;
    int l, r;
    Q ans;
 
    Mo(vector<T> a) : a(a), n(a.size()), l(0), r(0), ans(0) {}
 
    void add(T x){ //区間の拡大(左右で操作が異なる場合は分ける)
        
    }
 
    void erase(T x){ //区間の縮小(左右で操作が異なる場合は分ける)
        
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
            while(e.l < l) add(a[--l]);
            while(r < e.r) add(a[r++]);
            while(l < e.l) erase(a[l++]);
            while(e.r < r) erase(a[--r]);
            ret[e.id] = ans;
        }
        return ret;
    }
};

int main(){
    
}
