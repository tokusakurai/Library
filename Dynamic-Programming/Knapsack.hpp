
//各種ナップザック問題
//計算量 01ナップザック1・個数制限なしナップザック・個数制限付きナップザック : O(N*W)、01ナップザック2 : O(N*Σv_i)

//概要
//01ナップザック1：dp[i][j] := i個目まで取って重さがj以下になるときの価値の最大値
//01ナップザック2：dp[i][j] := i個目まで取って価値がjになるときの重さの最小値
//個数制限なしナップザック：dp[i] := 重さがi以下になるときの価値の最大値
//個数制限付きナップザック：dp[i][j] := i種類目のものまで取って重さがj以下になるときの価値の最大値(スライド最大値を用いる)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_F&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_G&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T knapsack_01_1(vector<T> v, vector<int> w, int W){
    int n = v.size();
    assert(w.size() == n);
    vector<T> dp(W+1, 0);
    for(int i = 0; i < n; i++){
        for(int j = W; j >= w[i]; j--){
            dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
        }
    }
    return dp[W];
}

template<typename T>
int knapsack_01_2(vector<int> v, vector<T> w, T W){
    int n = v.size();
    assert(w.size() == n);
    int V = accumulate(begin(v), end(v), 0);
    vector<T> dp(V+1, W+1);
    dp[0] = T(0);
    for(int i = 0; i < n; i++){
        for(int j = V; j >= v[i]; j--){
            dp[j] = min(dp[j], dp[j-v[i]]+w[i]);
        }
    }
    int ret = 0;
    for(int i = 0; i <= V; i++) if(dp[i] <= W) ret = i;
    return ret;
}

template<typename T>
T knapsack(vector<T> v, vector<int> w, int W){
    int n = v.size();
    assert(w.size() == n);
    vector<T> dp(W+1, 0);
    for(int i = 0; i <= W; i++){
        for(int j = 0; j < n; j++){
            if(i >= w[j]) dp[i] = max(dp[i], dp[i-w[j]]+v[j]);
        }
    }
    return dp[W];
}

template<typename T>
T knapsack_limitation(vector<T> v, vector<int> w, vector<int> m, int W){
    int n = v.size();
    assert(w.size() == n && m.size() == n);
    vector<T> dp(W+1, 0);
    for(int i = 0; i < n; i++){
        if(m[i] == 0) continue;
        vector<T> tmp(W+1);
        for(int j = 0; j < w[i]; j++){
            deque<int> que;
            for(int k = 0; j+w[i]*k <= W; k++){
                int p = j+w[i]*k;
                dp[p] -= v[i]*k;
                while(!que.empty() && dp[que.back()] <= dp[p]) que.pop_back();
                que.push_back(p);
                tmp[p] = dp[que.front()]+v[i]*k;
                if(que.front() == p-w[i]*m[i]) que.pop_front();
            }
        }
        swap(dp, tmp);
    }
    return dp[W];
}
