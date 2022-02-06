
// 数論変換（高速剰余変換）（mod は x*(2^y)+1 で表されるもの (n+m<=2^y)）
// 計算量 O((n+m)log(n+m))

// 概要
// mod を pとして、p = x*2^y+1 と表したとき、2^y >= n+m-1 が成立すれば FFT が行える。
// r を P の原子根とすれば、体 Z/pZ での 1 の 2^k 乗根は r^(x*2^(y-k)) として得られる。
// 代表的な (p,r) の組として (998244353,3) がある。

// verified with
// https://atcoder.jp/contests/practice2/tasks/practice2_f
// https://judge.yosupo.jp/problem/convolution_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Mod_Int.hpp"

template <typename T>
struct Number_Theoretic_Transform {
    static int max_base;
    static T root;
    static vector<T> r, ir;

    Number_Theoretic_Transform() {}

    static void init() {
        if (!r.empty()) return;
        int mod = T::get_mod();
        int tmp = mod - 1;
        root = 2;
        while (root.pow(tmp >> 1) == 1) root++;
        max_base = 0;
        while (tmp % 2 == 0) tmp >>= 1, max_base++;
        r.resize(max_base), ir.resize(max_base);
        for (int i = 0; i < max_base; i++) {
            r[i] = -root.pow((mod - 1) >> (i + 2)); // r[i] := 1 の 2^(i+2) 乗根
            ir[i] = r[i].inverse();                 // ir[i] := 1/r[i]
        }
    }

    static void ntt(vector<T> &a) {
        init();
        int n = a.size();
        assert((n & (n - 1)) == 0);
        assert(n <= (1 << max_base));
        for (int k = n; k >>= 1;) {
            T w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    T x = a[i], y = w * a[j];
                    a[i] = x + y, a[j] = x - y;
                }
                w *= r[__builtin_ctz(++t)];
            }
        }
    }

    static void intt(vector<T> &a) {
        init();
        int n = a.size();
        assert((n & (n - 1)) == 0);
        assert(n <= (1 << max_base));
        for (int k = 1; k < n; k <<= 1) {
            T w = 1;
            for (int s = 0, t = 0; s < n; s += 2 * k) {
                for (int i = s, j = s + k; i < s + k; i++, j++) {
                    T x = a[i], y = a[j];
                    a[i] = x + y, a[j] = w * (x - y);
                }
                w *= ir[__builtin_ctz(++t)];
            }
        }
        T inv = T(n).inverse();
        for (auto &e : a) e *= inv;
    }

    static vector<T> convolve(vector<T> a, vector<T> b) {
        int k = (int)a.size() + (int)b.size() - 1, n = 1;
        while (n < k) n <<= 1;
        a.resize(n), b.resize(n);
        ntt(a), ntt(b);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        intt(a), a.resize(k);
        return a;
    }
};

template <typename T>
int Number_Theoretic_Transform<T>::max_base = 0;

template <typename T>
T Number_Theoretic_Transform<T>::root = T();

template <typename T>
vector<T> Number_Theoretic_Transform<T>::r = vector<T>();

template <typename T>
vector<T> Number_Theoretic_Transform<T>::ir = vector<T>();
