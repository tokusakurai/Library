
//写像12相
//計算量 前計算：(N+log(M))、二項係数：O(1)、第2種スターリング数：O(K*log(N))、ベル数：O(min(N,K)*log(N))

//第2種スターリング数：n個の区別できる玉を、k個の区別しない箱に、各箱に1個以上玉が入るように入れる場合の数
//ベル数：n個の区別できる玉を、k個の区別しない箱に入れる場合の数

//概要
//前計算：i=0,1,...,Nについてi!とその逆元を求める。
//二項係数：nCk = n!/((n-k)!*k!)、nPk = n!/(n-k)!
//第2種スターリング数：包除原理
//ベル数：第2種スターリング数の和

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_B&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_E&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I&lang=ja

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

template<int mod>
struct Mod_Int{
    int x;

    Mod_Int() : x(0) {}

    Mod_Int(long long y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    Mod_Int &operator += (const Mod_Int &p){
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    Mod_Int &operator -= (const Mod_Int &p){
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    Mod_Int &operator *= (const Mod_Int &p){
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    Mod_Int &operator /= (const Mod_Int &p){
        *this *= p.inverse();
        return *this;
    }

    Mod_Int &operator ++ () {return *this += Mod_Int(1);}

    Mod_Int operator ++ (int){
        Mod_Int tmp = *this;
        ++*this;
        return tmp;
    }

    Mod_Int &operator -- () {return *this -= Mod_Int(1);}

    Mod_Int operator -- (int){
        Mod_Int tmp = *this;
        --*this;
        return tmp;
    }

    Mod_Int operator - () const {return Mod_Int(-x);}

    Mod_Int operator + (const Mod_Int &p) const {return Mod_Int(*this) += p;}

    Mod_Int operator - (const Mod_Int &p) const {return Mod_Int(*this) -= p;}

    Mod_Int operator * (const Mod_Int &p) const {return Mod_Int(*this) *= p;}

    Mod_Int operator / (const Mod_Int &p) const {return Mod_Int(*this) /= p;}

    bool operator == (const Mod_Int &p) const {return x == p.x;}

    bool operator != (const Mod_Int &p) const {return x != p.x;}

    Mod_Int inverse() const {
        assert(*this != Mod_Int(0));
        return pow(mod-2);
    }

    Mod_Int pow(long long k) const{
        Mod_Int now = *this, ret = 1;
        for(; k > 0; k >>= 1, now *= now){
            if(k&1) ret *= now;
        }
        return ret;
    }

    friend ostream &operator << (ostream &os, const Mod_Int &p){
        return os << p.x;
    }

    friend istream &operator >> (istream &is, Mod_Int &p){
        long long a;
        is >> a;
        p = Mod_Int<mod>(a);
        return is;
    }
};

using mint = Mod_Int<MOD>;

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

using comb = Combination<MOD>;

int main(){
    int N, K; cin >> N >> K;

    comb c(K);

    cout << c.comb(K, N) << '\n';
}
