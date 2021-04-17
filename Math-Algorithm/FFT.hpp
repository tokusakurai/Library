
//高速フーリエ変換を用いた多項式の畳み込み
//計算量 O((N+M)*log(N+M))

//概要
//StockhamのFFTを用いる。
//通常のFFT(Cooley Turkey)ではビットを反転して並べ替えているが、その部分を省略している。
//そのため、DFTした後の配列は順番が入れ替わったもの(ビット反転したときの昇順)となっている。

//verified with
//https://atcoder.jp/contests/atc001/tasks/fft_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

template<typename T>
struct Fast_Foulier_Transform{
    using comp = complex<double>;
    vector<comp> r, ir;

    Fast_Foulier_Transform(){
        r.resize(30), ir.resize(30);
        for(int i = 0; i < 30; i++){
            r[i] = -polar(1.0, pi/(1<<(i+1))); //r[i] := 1の2^(i+2)乗根
            ir[i] = -polar(1.0, -pi/(1<<(i+1))); //ir[i] := 1/r[i]
        }
    };

    vector<comp> to_comp(const vector<T> &a) const{
        vector<comp> ret(a.size());
        for(int i = 0; i < (int)a.size(); i++) ret[i] = comp(a[i], 0.0);
        return ret;
    }

    vector<T> to_T(const vector<comp> &a) const{
        vector<T> ret(a.size(), 0);
        for(int i = 0; i < (int)a.size(); i++) ret[i] = a[i].real()+0.1; //整数の場合、誤差をケア
        //for(int i = 0; i < (int)a.size(); i++) ret[i] = a[i].real(); //小数の場合
        return ret;
    }

    void fft(vector<comp> &a, int n) const{
        assert((n&(n-1)) == 0);
        a.resize(n);
        for(int k = n; k >>= 1;){
            comp w = 1;
            for(int s = 0, t = 0; s < n; s += 2*k){
                for(int i = s, j = s+k; i < s+k; i++, j++){
                    comp x = a[i], y = w*a[j];
                    a[i] = x+y, a[j] = x-y;
                }
                w *= r[__builtin_ctz(++t)];
            }
        }
    }

    void ifft(vector<comp> &a, int n) const{
        assert((n&(n-1)) == 0);
        a.resize(n);
        for(int k = 1; k < n; k <<= 1){
            comp w = 1;
            for(int s = 0, t = 0; s < n; s += 2*k){
                for(int i = s, j = s+k; i < s+k; i++, j++){
                    comp x = a[i], y = a[j];
                    a[i] = x+y, a[j] = w*(x-y);
                }
                w *= ir[__builtin_ctz(++t)];
            }
        }
        for(auto &e: a) e /= n;
    }

    vector<T> convolve(const vector<T> &a, const vector<T> &b) const{
        int k = (int)a.size()+(int)b.size()-1, n = 1;
        while(n < k) n <<= 1;
        vector<comp> A = to_comp(a), B = to_comp(b);
        fft(A, n), fft(B, n);
        for(int i = 0; i < n; i++) A[i] *= B[i];
        ifft(A, n);
        vector<T> c = to_T(A);
        c.resize(k);
        return c;
    }
};
