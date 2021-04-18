
//manachar(文字列Sの文字iを中心とする奇数長の最長回分の半径を記録した配列を求める)
//計算量 O(|S|)

//概要
//求める配列をRとする。
//j+R[i-j] < R[i]ならばR[i-j] = R[i+j]となる。j+R[i-j] >= R[i+j]の場合でもはみ出た部分だけ判定し直せばよい。
//偶数長の回文は、元の文字列の各文字の間に適当な文字を挟めばよい。

//verified with
//https://judge.yosupo.jp/problem/enumerate_palindromes

#pragma once
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
