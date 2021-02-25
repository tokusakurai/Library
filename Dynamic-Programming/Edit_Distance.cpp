
//編集距離(挿入、削除、置換ができる)
//計算量 O(N*M)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E&lang=ja

#include <bits/stdc++.h>
using namespace std;

template<typename T>
int edit_distance(T a, T b){
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for(int i = 0; i <= n; i++) dp[i][0] = i;
    for(int j = 0; j <= m; j++) dp[0][j] = j;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]})+1;
        }
    }
    return dp[n][m];
}

int main(){
    string a, b; cin >> a >> b;

    cout << edit_distance(a, b) << '\n';
}
