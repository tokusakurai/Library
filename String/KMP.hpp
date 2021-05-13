
//MP法(文字列Sの先頭i文字について最長の共通する接頭辞と接尾辞を記録した配列を返す)
//KMP法(MP法の条件に加えて、接頭辞と接尾辞の次の文字は相異なる)
//計算量 MP法・KMP法 : O(|S|)

//概要
//MP法で求める配列をA、KMP法で求める配列をBとする。
//S[i] = S[A[i]]ならA[i+1] = A[i]+1
//S[i] = S[A[A[i]]]ならA[i+1] = A[A[i]]+1
//のように再帰できる。
//S[i] = S[A[i]]ならB[i] = B[A[i]]、そうでなければB[i] = A[i]

//verified with
//https://atcoder.jp/contests/xmascontest2015/tasks/xmascontest2015_d

#include <bits/stdc++.h>
using namespace std;

vector<int> MP(string S){
    int n = S.size();
    vector<int> ret(n+1);
    ret[0] = -1;
    int j = -1;
    for(int i = 0; i < n; i++){
        while(j >= 0 && S[i] != S[j]) j = ret[j];
        j++;
        ret[i+1] = j;
    }
    return ret;
}

vector<int> KMP(string S){
    int n = S.size();
    vector<int> ret(n+1);
    ret[0] = -1;
    int j = -1;
    for(int i = 0; i < n; i++){
        while(j >= 0 && S[i] != S[j]) j = ret[j];
        j++;
        if(i+1 < n && S[i+1] == S[j]) ret[i+1] = ret[j];
        else ret[i+1] = j;
    }
    return ret;
}