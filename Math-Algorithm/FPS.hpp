
//形式的冪級数
//計算量 加算・減算・微分・積分 : O(N)、積・除算・inv・log・exp・pow : O(N*log(N))

//各種演算はテイラー展開を用いて定義される(詳しくは下のverify url)

//概要
//積 : NTT
//inv・exp : ニュートン法を用いた漸化式を立てて計算する。
//除算 : invを用いて計算する。
//log : invを用いて計算する。
//pow : logとexpを用いて計算する。

//verified with
//https://judge.yosupo.jp/problem/inv_of_formal_power_series
//https://judge.yosupo.jp/problem/log_of_formal_power_series
//https://judge.yosupo.jp/problem/exp_of_formal_power_series
//https://judge.yosupo.jp/problem/pow_of_formal_power_series

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/NTT.hpp"

template<int mod, int primitive_root>
struct Formal_Power_Series : vector<Mod_Int<mod>>{
    using T = Mod_Int<mod>;
    Number_Theorem_Transform<mod, primitive_root> NTT;
    using vector<T> :: vector;

    Formal_Power_Series(const vector<T> &v) : vector<T>(v) {}

    Formal_Power_Series pre(int n) const{
        return Formal_Power_Series(begin(*this), begin(*this)+min((int)this->size(), n));
    }

    Formal_Power_Series rev(int deg = -1) const{
        Formal_Power_Series ret = *this;
        if(deg != -1) ret.resize(deg, T(0));
        reverse(begin(ret), end(ret));
        return ret;
    }

    Formal_Power_Series &normalize(){
        while(!this->empty() && this->back() == 0) this->pop_back();
        return *this;
    }

    Formal_Power_Series operator - () const noexcept{
        Formal_Power_Series ret = *this;
        for(int i = 0; i < (int)ret.size(); i++) ret[i] = -ret[i];
        return ret; 
    }

    Formal_Power_Series &operator += (const T &x){
        if(this->empty()) this->resize(1);
        (*this)[0] += x;
        return *this;
    }

    Formal_Power_Series &operator += (const Formal_Power_Series &v){
        if(v.size() > this->size()) this->resize(v.size());
        for(int i = 0; i < (int)v.size(); i++) (*this)[i] += v[i];
        return this->normalize();
    }

    Formal_Power_Series &operator -= (const T &x){
        if(this->empty()) this->resize(1);
        *this[0] -= x;
        return *this;
    }

    Formal_Power_Series &operator -= (const Formal_Power_Series &v){
        if(v.size() > this->size()) this->resize(v.size());
        for(int i = 0; i < (int)v.size(); i++) (*this)[i] -= v[i];
        return this->normalize();
    }

    Formal_Power_Series &operator *= (const T &x){
        for(int i = 0; i < (int)this->size(); i++) (*this)[i] *= x;
        return *this;
    }

    Formal_Power_Series &operator *= (const Formal_Power_Series &v){
        return *this = NTT.convolve(*this, v);
    }

    Formal_Power_Series &operator /= (const T &x){
        assert(x != 0);
        T inv = x.inverse();
        for(int i = 0; i < (int)this->size(); i++) (*this)[i] *= inv;
        return *this;
    }

    Formal_Power_Series &operator /= (const Formal_Power_Series &v){
        if(v.size() > this->size()){
            this->clear();
            return *this;
        }
        int n = this->size()-v.size()+1;
        return *this = (rev().pre(n)*v.rev().inv(n)).pre(n).rev(n);
    }

    Formal_Power_Series &operator %= (const Formal_Power_Series &v){
        return *this -= (*this/v)*v;
    }

    Formal_Power_Series &operator <<= (int x){
        Formal_Power_Series ret(x, 0);
        ret.insert(end(ret), begin(*this), end(*this));
        return *this = ret;
    }

    Formal_Power_Series &operator >>= (int x){
        Formal_Power_Series ret;
        ret.insert(end(ret), begin(*this)+x, end(*this));
        return *this = ret;
    }

    Formal_Power_Series operator + (const T &x) const {return Formal_Power_Series(*this) += x;}

    Formal_Power_Series operator + (const Formal_Power_Series &v) const {return Formal_Power_Series(*this) += v;}

    Formal_Power_Series operator - (const T &x) const {return Formal_Power_Series(*this) -= x;}

    Formal_Power_Series operator - (const Formal_Power_Series &v) const {return Formal_Power_Series(*this) -= v;}

    Formal_Power_Series operator * (const T &x) const {return Formal_Power_Series(*this) *= x;}

    Formal_Power_Series operator * (const Formal_Power_Series &v) const {return Formal_Power_Series(*this) *= v;}

    Formal_Power_Series operator / (const T &x) const {return Formal_Power_Series(*this) /= x;}

    Formal_Power_Series operator / (const Formal_Power_Series &v) const {return Formal_Power_Series(*this) /= v;}

    Formal_Power_Series operator % (const Formal_Power_Series &v) const {return Formal_Power_Series(*this) %= v;}

    Formal_Power_Series operator << (int x) const {return Formal_Power_Series(*this) <<= x;}

    Formal_Power_Series operator >> (int x) const {return Formal_Power_Series(*this) >>= x;}

    T val(const T &x) const{
        T ret = 0;
        for(int i = (int)this->size()-1; i >= 0; i--) ret *= x, ret += (*this)[i];
        return ret;
    }

    Formal_Power_Series diff() const{ // df/dx
        int n = this->size();
        Formal_Power_Series ret(n-1);
        for(int i = 1; i < n; i++) ret[i-1] = (*this)[i]*i;
        return ret;
    }

    Formal_Power_Series integral() const{ // ∫fdx
        int n = this->size();
        Formal_Power_Series ret(n+1);
        for(int i = 0; i < n; i++) ret[i+1] = (*this)[i]/(i+1);
        return ret;
    }

    Formal_Power_Series inv(int deg) const{ // 1/f (f[0] != 0)
        assert((*this)[0] != T(0));
        Formal_Power_Series ret(1, (*this)[0].inverse());
        for(int i = 1; i < deg; i <<= 1){
            Formal_Power_Series f = pre(2*i), g = ret;
            NTT.ntt(f, 2*i), NTT.ntt(g, 2*i);
            Formal_Power_Series h(2*i);
            for(int j = 0; j < 2*i; j++) h[j] = f[j]*g[j];
            NTT.intt(h, 2*i);
            for(int j = 0; j < i; j++) h[j] = 0;
            NTT.ntt(h, 2*i);
            for(int j = 0; j < 2*i; j++) h[j] *= g[j];
            NTT.intt(h, 2*i);
            for(int j = 0; j < i; j++) h[j] = 0;
            ret -= h;
            //ret = (ret+ret-ret*ret*pre(i<<1)).pre(i<<1);
        }
        ret.resize(deg);
        return ret;
    }

    Formal_Power_Series inv() const {return inv(this->size());}

    Formal_Power_Series log(int deg) const{ // log(f) (f[0] = 1)
        assert((*this)[0] == 1);
        Formal_Power_Series ret = (diff()*inv(deg)).pre(deg-1).integral();
        ret.resize(deg);
        return ret;
    }

    Formal_Power_Series log() const {return log(this->size());}

    Formal_Power_Series exp(int deg) const{ // exp(f) (f[0] = 0)
        assert((*this)[0] == 0);
        Formal_Power_Series ret(1, 1);
        for(int i = 1; i < deg; i <<= 1){
            ret = (ret*(pre(i<<1)+1-ret.log(i<<1))).pre(i<<1);
        }
        ret.resize(deg);
        return ret;
    }

    Formal_Power_Series exp() const {return exp(this->size());}

    Formal_Power_Series pow(long long k, int deg) const{ // f^k
        int n = this->size();
        for(int i = 0; i < n; i++){
            if((*this)[i] == 0) continue;
            T rev = (*this)[i].inverse();
            Formal_Power_Series C(*this*rev), D(n-i, 0);
            for(int j = i; j < n; j++) D[j-i] = C[j];
            D = (D.log()*k).exp()*((*this)[i].pow(k));
            Formal_Power_Series E(deg, 0);
            if(i > 0 && k > deg/i) return E;
            long long S = i*k;
            for(int j = 0; j+S < deg && j < D.size(); j++) E[j+S] = D[j];
            E.resize(deg);
            return E;
        }
        return Formal_Power_Series(deg, 0);
    }

    Formal_Power_Series pow(long long k) const {return pow(k, this->size());}
};
