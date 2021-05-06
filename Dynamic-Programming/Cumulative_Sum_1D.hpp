
//1次元累積和
//計算量 構築 : O(N)、区間和クエリ : O(1)

//概要
//各要素について自分より前の要素の和を累積和dpで求める。

//verified with
//https://judge.yosupo.jp/problem/static_range_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Cumurative_Sum_1D{
    vector<T> v;
    const int n;

    Cumurative_Sum_1D(const vector<T> &v) : v(v), n((int)v.size()){
        build();
    }

    void build(){
        for(int i = 1; i < n; i++) v[i] += v[i-1];
    }

    T fold(int a){
        return (a <= 0? 0 : v[min(n, a)-1]);
    }

    T sum(int l, int r){
        return fold(r)-fold(l);
    }
};