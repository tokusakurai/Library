
//平方分割(雛形)
//計算量 クエリO(√N)やO(√(N*log(N)))になることが多い

//概要
//区間全体にクエリをかける操作が高速にできる場合、バケットサイズO(√N)で区間を分割することでクエリを高速化出来る。

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Sqrt_Decomposition{
    struct Node{
        const int l, r;
        vector<T> v;

        Node(const vector<T> &a, int l, int r) : l(l), r(r){
            v.resize(r-l);
            copy(begin(a)+l, begin(a)+r, begin(v));

        }

        T eval(const T &x) const {return ;} //各要素を遅延評価で更新

        void eval_all(){ //全体を遅延評価で更新
            for(auto &e : v) e = eval(e);
            
        }

        void query1(int a, int b, const T &x){ //区間[a,b)にxを適用
            a = max(a, l), b = min(b, r);
            if(a >= b) return;
            if(a == l && b == r) {query1_all(x); return;}

        }

        void query1_all(const T &x){ //区間全体にxを適用

        }

        T query2(int a, int b){ //区間[a,b)での演算の結果
            a = max(a, l), b = min(b, r);
            if(a >= b) return;
            if(a == l && b == r) {return query2_all();}

        }

        T query2_all(){ //区間全体での演算の結果

        }
    };

    vector<Node> nodes; //配列をbucket_sizeごとに分割する

    Sqrt_Decomposition(const vector<T> &a, int bucket_size){
        for(int i = 0; i < (int)a.size(); i += bucket_size){
            nodes.emplace_back(a, i, min(i+bucket_size, (int)a.size()));
        }
    }

    void query1(int a, int b, const T &x) {for(auto &e : nodes) query1(a, b, x);} //区間[a,b)にxを適用

    T query2(int a, int b){ //区間[a,b)での演算の結果
        T ret = ;
        for(auto &e : nodes) ;
        return ret;
    }
};

int main(){
    
}
