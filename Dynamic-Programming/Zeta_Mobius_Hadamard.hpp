
//高速ゼータ変換、高速メビウス変換、高速アダマール変換
//計算量 高速ゼータ変換・高速メビウス変換・高速アダマール変換 : O(N*log(N))

//ゼータ変換 : g(T) = Σf(S) (S⊇T) (上位集合)、 g(T) = Σf(S) (S⊆T) (下位集合)
//メビウス変換 : ゼータ変換の逆変換
//アダマール変換 : アダマール行列を左から作用させる

//概要
//高速ゼータ変換 : 長さnの2進数表記をn次元空間での座標のように見なせば、n次元の累積和であるとみなすことができる。
//高速メビウス変換 : 同様に、n次元の差分であるとみなすことができる。
//高速アダマール変換 : アダマール行列の(i,j)成分=(-1)^(i・j) ((i・j)はn次元ベクトルとみたときのiとjの内積)
//AND畳み込み : a,bを上位集合で高速ゼータ変換⇒両者の各項の積を取る⇒上位集合で高速メビウス変換
//OR畳み込み : a,bを下位集合で高速ゼータ変換⇒両者の各項の積を取る⇒下位集合で高速メビウス変換
//XOR畳み込み : a,bを高速アダマール変換⇒両者の各項の積を取る⇒高速逆アダマール変換

//verified with
//https://judge.yosupo.jp/problem/bitwise_and_convolution
//https://judge.yosupo.jp/problem/bitwise_xor_convolution

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
void Fast_Zeta_Transform(vector<T> &f, bool upper){
    int n = f.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                if(upper) f[j] += f[j|i];
                else f[j|i] += f[j];
            }
        }
    }
}

template<typename T>
void Fast_Mobius_Transform(vector<T> &f, bool upper){
    int n = f.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                if(upper) f[j] -= f[j|i];
                else f[j|i] -= f[j];
            }
        }
    }
}

template<typename T>
void Fast_Hadamard_Transform(vector<T> &f, bool inverse = false){
    int n = f.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                T x = f[j], y = f[j|i];
                f[j] = x+y, f[j|i] = x-y;
            }
        }
    }
    if(inverse) for(auto &e : f) e /= n;
}

template<typename T>
vector<T> bitwise_and_convolution(vector<T> f, vector<T> g){
    int n = f.size();
    assert(g.size() == n && (n&(n-1)) == 0);
    Fast_Zeta_Transform(f, true), Fast_Zeta_Transform(g, true);
    for(int i = 0; i < n; i++) f[i] *= g[i];
    Fast_Mobius_Transform(f, true);
    return f;
}

template<typename T>
vector<T> bitwise_or_convolution(vector<T> f, vector<T> g){
    int n = f.size();
    assert(g.size() == n && (n&(n-1)) == 0);
    Fast_Zeta_Transform(f, false), Fast_Zeta_Transform(g, false);
    for(int i = 0; i < n; i++) f[i] *= g[i];
    Fast_Mobius_Transform(f, false);
    return f;
}

template<typename T>
vector<T> bitwise_xor_convolution(vector<T> f, vector<T> g){
    int n = f.size();
    assert(g.size() == n && (n&(n-1)) == 0);
    Fast_Hadamard_Transform(f), Fast_Hadamard_Transform(g);
    for(int i = 0; i < n; i++) f[i] *= g[i];
    Fast_Hadamard_Transform(f, true);
    return f;
}