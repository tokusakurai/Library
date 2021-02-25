
//manachar(文字列Sの文字iを中心とする奇数長の最長回分の半径を記録した配列を求める)
//計算量 O(N)

//verified with
//https://judge.yosupo.jp/problem/enumerate_palindromes

#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<int> manachar(const T &s){
    int n = s.size();
    vector<int> ret(n);
    int i = 0, j = 0;
    while(i < n){
        while(i-j >= 0 && i+j < n && s[i-j] == s[i+j]) j++;
        ret[i] = j;
        int k = 1;
        while(i-k >= 0 && k+ret[i-k] < j) ret[i+k] = ret[i-k], k++;
        i += k, j -= k;
    }
    return ret;
}

int main(){
    string S; cin >> S;
    int N = S.size();

    string T = ".";
    for(int i = 0; i < N; i++){
        T += S[i], T += '.';
    }

    vector<int> ans = manachar(T);

    for(int i = 1; i < 2*N; i++) cout << ans[i]-1 << ' ';
    cout << '\n';
}
