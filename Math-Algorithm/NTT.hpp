
//数論変換(高速剰余変換)(modはx*(2^y)+1で表されるもの(N+M<=2^y))
//計算量 O((N+M)*log(N+M))

//概要
//modをPとして、P=x*2^y+1と表したとき、2^y>=N+M-1が成立すればFFTが行える。
//rをPの原子根とすれば、剰余環での1の2^k乗根はr^(x*2^(y-k))として得られる。
//代表的な(P,r)の組として(998244353,3)がある。

//verified with
//https://atcoder.jp/contests/practice2/tasks/practice2_f
//https://judge.yosupo.jp/problem/convolution_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Mod_Int.hpp"

template<int mod, int primitive_root>
struct Number_Theorem_Transform{
    using T = Mod_Int<mod>;
    vector<T> r, ir;

    Number_Theorem_Transform(){
        r.resize(30), ir.resize(30);
        for(int i = 0; i < 30; i++){
            r[i] = -T(primitive_root).pow((mod-1)>>(i+2)); //r[i]:=1の2^(i+2)乗根
            ir[i] = r[i].inverse(); //ir[i]:=1/r[i]
        }
    }

    void ntt(vector<T> &a, int n) const{
        assert((n&(n-1)) == 0);
        a.resize(n);
        for(int k = n; k >>= 1;){
            T w = 1;
            for(int s = 0, t = 0; s < n; s += 2*k){
                for(int i = s, j = s+k; i < s+k; i++, j++){
                    T x = a[i], y = w*a[j];
                    a[i] = x+y, a[j] = x-y;
                }
                w *= r[__builtin_ctz(++t)];
            }
        }
    }

    void intt(vector<T> &a, int n) const{
        assert((n&(n-1)) == 0);
        a.resize(n);
        for(int k = 1; k < n; k <<= 1){
            T w = 1;
            for(int s = 0, t = 0; s < n; s += 2*k){
                for(int i = s, j = s+k; i < s+k; i++, j++){
                    T x = a[i], y = a[j];
                    a[i] = x+y, a[j] = w*(x-y);
                }
                w *= ir[__builtin_ctz(++t)];
            }
        }
        T inv = T(n).inverse();
        for(auto &e: a) e *= inv;
    }

    vector<T> convolve(vector<T> a, vector<T> b) const{
        int k = (int)a.size()+(int)b.size()-1, n = 1;
        while(n < k) n <<= 1;
        ntt(a, n), ntt(b, n);
        for(int i = 0; i < n; i++) a[i] *= b[i];
        intt(a, n), a.resize(k);
        return a;
    }
};
