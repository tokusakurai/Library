
//最大安定集合(どの2点も隣接しない点集合で最大のもの)
//計算量 O(1.381^V*V)

//verified with
//https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_g
//https://judge.yosupo.jp/problem/maximum_independent_set

#include <bits/stdc++.h>
using namespace std;
 
long long maximum_independent_set(vector<long long> G, long long rem = -1){
    int n = G.size();
    if(rem == -1) rem = (1LL<<n)-1;
    long long ret = 0;
    int k = -1, m = -1; //次数最大の頂点
    while(true){
        bool update = false;
        for(int i = 0; i < n; i++){
            if(!((rem>>i)&1)) continue;
            int s = __builtin_popcountll(rem & G[i]); //次数
            if(s > m) k = i, m = s;
            if(s <= 1){
                rem &= ~(G[i] | (1LL<<i));
                ret |= (1LL<<i), update = true;
            }
        }
        if(!update) break;
        k = -1, m = -1;
    }
    if(rem > 0){
        rem &= ~(1LL<<k);
        long long p = maximum_independent_set(G, rem); //kを使わない
        long long q = maximum_independent_set(G, rem & ~G[k]); //kを使う
        if(__builtin_popcountll(p) > __builtin_popcountll(q)) ret |= p;
        else ret |= ((1LL<<k) | q);
    }
    return ret;
}
 
int main(){
    int V, E; cin >> V >> E;

    vector<long long> es(V);

    for(int i = 0; i < E; i++){
        int u, v; cin >> u >> v;
        es[u] |= (1LL<<v), es[v] |= (1LL<<u);
    }

    long long ans = maximum_independent_set(es);
    
    cout << __builtin_popcountll(ans) << '\n';
    for(int i = 0; i < V; i++){
        if((ans>>i)&1) cout << i << ' ';
    }
    cout << '\n';
}
