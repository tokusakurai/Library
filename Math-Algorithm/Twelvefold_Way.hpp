
//写像12相
//計算量 前計算 : (N+log(M))、二項係数 : O(1)、第2種スターリング数 : O(K*log(N))、ベル数 : O(min(N,K)*log(N))

//第2種スターリング数 : n個の区別できる玉を、k個の区別しない箱に、各箱に1個以上玉が入るように入れる場合の数
//ベル数 : n個の区別できる玉を、k個の区別しない箱に入れる場合の数

//概要
//前計算 : i = 0,1,...,Nについてi!とその逆元を求める。
//二項係数 : nCk = n!/((n-k)!*k!)、nPk = n!/(n-k)!
//第2種スターリング数 : 包除原理
//ベル数 : 第2種スターリング数の和

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_B&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_E&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Mod_Int.hpp"

template<int mod>
struct Combination{
    using T = Mod_Int<mod>;
    vector<T> _fac, _ifac;

    Combination(int n){
        _fac.resize(n+1), _ifac.resize(n+1);
        _fac[0] = 1;
        for(int i = 1; i <= n; i++) _fac[i] = _fac[i-1]*i;
        _ifac[n] = _fac[n].inverse();
        for(int i = n; i >= 1; i--) _ifac[i-1] = _ifac[i]*i;
    }

    T fac(int k) const {return _fac[k];}

    T ifac(int k) const {return _ifac[k];}

    T comb(int n, int k) const{
        if(k < 0 || n < k) return 0;
        return fac(n)*ifac(n-k)*ifac(k);
    }

    T comb2(int x, int y) const {return comb(x+y, x);}

    T perm(int n, int k) const{
        if(k < 0 || n < k) return 0;
        return fac(n)*ifac(n-k);
    }

    T second_stirling_number(int n, int k) const{ //n個の区別できる玉を、k個の区別しない箱に、各箱に1個以上玉が入るように入れる場合の数
        T ret = 0;
        for(int i = 0; i <= k; i++){
            T tmp = comb(k, i)*T(i).pow(n);
            ret += ((k-i)&1)? -tmp : tmp;
        }
        return ret*ifac(k);
    }

    T bell_number(int n, int k) const{ //n個の区別できる玉を、k個の区別しない箱に入れる場合の数
        if(n == 0) return 1;
        k = min(k, n);
        vector<T> pref(k+1);
        pref[0] = 1;
        for(int i = 1; i <= k; i++){
            if(i&1) pref[i] = pref[i-1]-ifac(i);
            else pref[i] = pref[i-1]+ifac(i);   
        }
        T ret = 0;
        for(int i = 1; i <= k; i++){
            ret += T(i).pow(n)*ifac(i)*pref[k-i];
        }
        return ret;
    }
};
