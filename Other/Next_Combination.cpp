
//サイズNの集合からからサイズKの部分集合を全列挙する
//計算量 O(C(N,K))

//概要
//サイズKの部分集合を辞書順で小さいものから1個ずつ順に列挙する。

//verified with
//https://atcoder.jp/contests/cpsco2019-s1/tasks/cpsco2019_s1_c

#include <bits/stdc++.h>
using namespace std;

template<typename T>
T next_combination(T comb){ //combの辞書順で次に大きい部分集合を求める
    assert(comb > 0);
    T x = comb&(-comb), y = comb+x, z = comb&(~y);
    return ((z/x)>>1)|y;
}

int main(){
    int N, K; cin >> N >> K;

    vector<long long> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];

    long long ans = LLONG_MAX;

    for(long long comb = (1LL<<K)-1; comb < (1LL<<N); comb = next_combination(comb)){
        long long S = 0, tmp = 0;
        for(int j = 0; j < N; j++){
            if((comb>>j)&1) S += A[j];
        }
        while(S){
            long long x = S%10;
            tmp += x/5+x%5, S /= 10;
        }
        ans = min(ans, tmp);
    }

    cout << ans << '\n';
}
