
//実行時入力mod-int構造体(素数)
//計算量 加減乗算 : O(1)、除算 : O(log(MOD))、K乗 : O(log(K))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Runtime_Mod_Int{
    int x;

    Runtime_Mod_Int() : x(0) {}

    Runtime_Mod_Int(long long y){
        x = y % get_mod();
        if(x < 0) x += get_mod();
    }

    static inline int &get_mod(){
        static int mod = 0;
        return mod;
    }

    static void set_mod(int md){
        get_mod() = md;
    }

    Runtime_Mod_Int &operator += (const Runtime_Mod_Int &p){
        if((x += p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    Runtime_Mod_Int &operator -= (const Runtime_Mod_Int &p){
        if((x += get_mod() - p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    Runtime_Mod_Int &operator *= (const Runtime_Mod_Int &p){
        x = (int) (1LL * x * p.x % get_mod());
        return *this;
    }

    Runtime_Mod_Int &operator /= (const Runtime_Mod_Int &p){
        *this *= p.inverse();
        return *this;
    }

    Runtime_Mod_Int &operator ++ () {return *this += Runtime_Mod_Int(1);}

    Runtime_Mod_Int operator ++ (int){
        Runtime_Mod_Int tmp = *this;
        ++*this;
        return tmp;
    }

    Runtime_Mod_Int &operator -- () {return *this -= Runtime_Mod_Int(1);}

    Runtime_Mod_Int operator -- (int){
        Runtime_Mod_Int tmp = *this;
        --*this;
        return tmp;
    }

    Runtime_Mod_Int operator - () const {return Runtime_Mod_Int(-x);}

    Runtime_Mod_Int operator + (const Runtime_Mod_Int &p) const {return Runtime_Mod_Int(*this) += p;}

    Runtime_Mod_Int operator - (const Runtime_Mod_Int &p) const {return Runtime_Mod_Int(*this) -= p;}

    Runtime_Mod_Int operator * (const Runtime_Mod_Int &p) const {return Runtime_Mod_Int(*this) *= p;}

    Runtime_Mod_Int operator / (const Runtime_Mod_Int &p) const {return Runtime_Mod_Int(*this) /= p;}

    bool operator == (const Runtime_Mod_Int &p) const {return x == p.x;}

    bool operator != (const Runtime_Mod_Int &p) const {return x != p.x;}

    Runtime_Mod_Int inverse() const {
        assert(*this != Runtime_Mod_Int(0));
        return pow(get_mod()-2);
    }

    Runtime_Mod_Int pow(long long k) const{
        Runtime_Mod_Int now = *this, ret = 1;
        for(; k > 0; k >>= 1, now *= now){
            if(k&1) ret *= now;
        }
        return ret;
    }

    friend ostream &operator << (ostream &os, const Runtime_Mod_Int &p){
        return os << p.x;
    }

    friend istream &operator >> (istream &is, Runtime_Mod_Int &p){
        long long a;
        is >> a;
        p = Runtime_Mod_Int(a);
        return is;
    }
};
