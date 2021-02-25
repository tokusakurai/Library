
//最長増加部分列(LIS)
//計算量 O(N*log(N))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T>
int longest_increasing_subsequence(const vector<T> &a, bool strict){ //strict:狭義単調増加か広義単調増加か
    vector<T> dp;
    for(auto &e: a){
        typename vector<T>::iterator it;
        if(strict) it = lower_bound(begin(dp), end(dp), e);
        else it = upper_bound(begin(dp), end(dp), e);
        if(it == end(dp)) dp.push_back(e);
        else *it = e;
    }
    return dp.size();
}

int main(){
    int N; cin >> N;

    vector<int> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];
    
    cout << longest_increasing_subsequence(a, true) << '\n';
}
