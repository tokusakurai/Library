
// 組み合わせ
// 計算量 前計算 : (N+log(M))、二項係数 : O(1)、逆数 : O(1)、第2種スターリング数 : O(K*log(N))、ベル数 : O(min(N,K)*log(N))

// 第2種スターリング数 : n個の区別できる玉を、k個の区別しない箱に、各箱に1個以上玉が入るように入れる場合の数
// ベル数 : n個の区別できる玉を、k個の区別しない箱に入れる場合の数

// 概要
// 前計算 : i = 0,1,...,Nについてi!とその逆元を求める。
// 二項係数 : nCk = n!/((n-k)!*k!), nPk = n!/(n-k)!, nHk = (n+k-1)Ck
// 逆数 : 1/k = (k-1)!/k!
// 第2種スターリング数 : 包除原理
// ベル数 : 第2種スターリング数の和

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_B&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_D&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_E&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Combination {
    static vector<T> _fac, _ifac;

    Combination() {}

    static void init(int n) {
        _fac.resize(n + 1), _ifac.resize(n + 1);
        _fac[0] = 1;
        for (int i = 1; i <= n; i++) _fac[i] = _fac[i - 1] * i;
        _ifac[n] = _fac[n].inverse();
        for (int i = n; i >= 1; i--) _ifac[i - 1] = _ifac[i] * i;
    }

    static T fac(int k) { return _fac[k]; }

    static T ifac(int k) { return _ifac[k]; }

    static T inv(int k) { return fac(k - 1) * ifac(k); }

    static T P(int n, int k) {
        if (k < 0 || n < k) return 0;
        return fac(n) * ifac(n - k);
    }

    static T C(int n, int k) {
        if (k < 0 || n < k) return 0;
        return fac(n) * ifac(n - k) * ifac(k);
    }

    static T H(int n, int k) { // k個の区別できない玉をn個の区別できる箱に入れる場合の数
        if (n < 0 || k < 0) return 0;
        return k == 0 ? 1 : C(n + k - 1, k);
    }

    static T second_stirling_number(int n, int k) { // n個の区別できる玉を、k個の区別しない箱に、各箱に1個以上玉が入るように入れる場合の数
        T ret = 0;
        for (int i = 0; i <= k; i++) {
            T tmp = C(k, i) * T(i).pow(n);
            ret += ((k - i) & 1) ? -tmp : tmp;
        }
        return ret * ifac(k);
    }

    static T bell_number(int n, int k) { // n個の区別できる玉を、k個の区別しない箱に入れる場合の数
        if (n == 0) return 1;
        k = min(k, n);
        vector<T> pref(k + 1);
        pref[0] = 1;
        for (int i = 1; i <= k; i++) {
            if (i & 1) {
                pref[i] = pref[i - 1] - ifac(i);
            } else {
                pref[i] = pref[i - 1] + ifac(i);
            }
        }
        T ret = 0;
        for (int i = 1; i <= k; i++) ret += T(i).pow(n) * ifac(i) * pref[k - i];
        return ret;
    }
};

template <typename T>
vector<T> Combination<T>::_fac = vector<T>();

template <typename T>
vector<T> Combination<T>::_ifac = vector<T>();
