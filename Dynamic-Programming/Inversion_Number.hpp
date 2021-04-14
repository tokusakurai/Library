
//転倒数
//計算量 O(N*log(N))

//概要
//配列を左端から右端の順または小さい要素から大きい要素の順に見ていき、各値やidの出現回数をBITで記録する。

//verified with
//https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D&lang=jp

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Binary_Indexed_Tree.hpp"

template<typename T>
long long inversion_number(vector<T> a){
    int n = a.size();
    vector<int> v(n);
    iota(begin(v), end(v), 0);
    sort(begin(v), end(v), [&](int i, int j){
        if(a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    Binary_Indexed_Tree<int> bit(vector<int>(n, 0));
    long long ret = 0;
    for(int i = 0; i < n; i++){
        ret += bit.query(v[i]+1, n);
        bit.add(v[i], 1);
    }
    return ret;
}

long long inversion_number(vector<int> a, int m){ //配列の全ての要素が[0,m)に含まれる場合
    int n = a.size();
    Binary_Indexed_Tree<int> bit(vector<int>(m, 0));
    long long ret = 0;
    for(int i = 0; i < n; i++){
        ret += bit.query(a[i]+1, m);
        bit.add(a[i], 1);
    }
    return ret;
}