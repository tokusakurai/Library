
//高速ゼータ変換、高速メビウス変換、高速アダマール変換
//計算量 高速ゼータ変換・高速メビウス変換・高速アダマール変換 : O(N*log(N))

//ゼータ変換 : g(T) = Σf(S) (S⊇T) (上位集合)、 g(T) = Σf(S) (S⊆T) (下位集合)
//メビウス変換 : ゼータ変換の逆変換
//アダマール変換 : アダマール行列を左から作用させる

//概要
//高速ゼータ変換 : 長さnの2進数表記をn次元空間での座標のように見なせば、n次元の累積和であるとみなすことができる。
//高速メビウス変換 : 同様に、n次元の差分であるとみなすことができる。
//高速アダマール変換 : アダマール行列の(i,j)成分=(-1)^(i・j) ((i・j)はn次元ベクトルとみたときのiとjの内積)

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
void Fast_Zeta_Transform(vector<T> &a, bool upper){
    int n = a.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                if(upper) a[j] += a[j|i];
                else a[j|i] += a[j];
            }
        }
    }
}

template<typename T>
void Fast_Mobius_Transform(vector<T> &a, bool upper){
    int n = a.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                if(upper) a[j] -= a[j|i];
                else a[j|i] -= a[j];
            }
        }
    }
}

template<typename T>
void Fast_Hadamard_Transform(vector<T> &a, bool inverse = false){
    int n = a.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                T x = a[j], y = a[j|i];
                a[j] = x+y, a[j|i] = x-y;
            }
        }
    }
    if(inverse) for(auto &e : a) e /= n;
}
