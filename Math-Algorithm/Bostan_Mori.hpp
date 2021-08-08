
//Bostan-Moriのアルゴリズム法(D階の線形漸化式で与えられる数列の第N項を求める)
//計算量 O(D*log(D)*log(N))

//概要
//G(x) := a[0]+a[1]x+a[2]x^2+...
//Q(x) := 1-c[1]x-c[2]x^2-...-c[d]x^d
//P(x) := G(x)*Q(x)
//とすると、P(x)はd-1次以下になっているので、a[n] = [x^n](P(x)/Q(x))を求める。

//verified with
//https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/NTT.hpp"

template<int mod, int primitive_root>
struct Bostan_Mori{
    using T = Mod_Int<mod>;
    Number_Theorem_Transform<mod, primitive_root> NTT_;

    //d項間線形漸化式 a[n] = c[1]*a[n-1]+c[2]*a[n-2]+・・・+c[d]*a[n-d]
    const int d;
    //G(x) := a[0]+a[1]x+a[2]x^2+...
    //Q(x) := 1-c[1]x-c[2]x^2-...-c[d]x^d
    //P(x) := G(x)*Q(x) (畳み込み)
    vector<T> P, Q;

    Bostan_Mori(const vector<T> &a, const vector<T> &c) : d(a.size()){
        Q.resize(d+1);
        Q[0] = 1;
        for(int i = 1; i <= d; i++) Q[i] = -c[i];
        P = NTT_.convolve(a, Q);
        P.resize(d);
    }

    T operator [] (long long n) const{ //a[n](0-indexed)
        vector<T> U = P, V = Q;
        for(; n; n >>= 1){
            vector<T> W = V;
            for(int i = 0; i <= d; i++){
                if(i&1) W[i] = -W[i];
            }
            int k = 1;
            while(k < 2*d+1) k <<= 1;
            U.resize(k), NTT_.ntt(U, k);
            V.resize(k), NTT_.ntt(V, k);
            W.resize(k), NTT_.ntt(W, k);
            vector<T> A(k), B(k);
            for(int i = 0; i < k; i++){
                A[i] = U[i]*W[i];
                B[i] = V[i]*W[i];
            }
            NTT_.intt(A, k), NTT_.intt(B, k);
            for(int i = 0; i <= d; i++) V[i] = B[2*i];
            V.resize(d+1);
            if(n&1){
                for(int i = 0; i < d; i++) U[i] = A[2*i+1];
            }
            else{
                for(int i = 0; i < d; i++) U[i] = A[2*i];
            }
            U.resize(d);
        }
        return U[0];
    }
};