
//重み付きUnion-Find木(等式差分制約を扱える)
//計算量 構築 : O(N)、併合・結合判定・サイズ・ポテンシャル取得 : (ならし)O(α(N))

//概要
//各頂点の(自分の重み)-(親の重み)を記録することによって、(自分の重み)-(根の重み)を簡単に計算できる。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja
//https://atcoder.jp/contests/arc090/tasks/arc090_b

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Weighted_Union_Find_Tree{
    vector<int> data;
    vector<T> ws; //(自分の重み)-(親の重み)を記録
    const int n;

    Weighted_Union_Find_Tree(int n) : data(n, -1), ws(n, 0), n(n) {}

    int root(int x){
        if(data[x] < 0) return x;
        int par = root(data[x]);
        ws[x] += ws[data[x]];
        return data[x] = par;
    }

    int operator [] (int i) {return root(i);}

    T weight(int x){
        root(x);
        return ws[x];
    }

    bool unite(int x, int y, T w){ //weight(y)-weight(x) = w
        w += weight(x), w -= weight(y);
        x = root(x), y = root(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y), w *= -1;
        data[x] += data[y], data[y] = x;
        ws[y] = w;
        return true;
    }

    T diff(int x, int y) {return weight(y)-weight(x);}

    int size(int x) {return -data[root(x)];}
    
    bool same(int x, int y) {return root(x) == root(y);}
    
    void clear(){
        fill(begin(data), end(data), -1), fill(begin(ws), end(ws), 0);
    }
};
