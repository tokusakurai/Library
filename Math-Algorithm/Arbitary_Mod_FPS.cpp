
//形式的冪級数(任意mod)
//計算量 加算・減算・微分・積分：O(N)、除算・inv・log・exp・pow：O(N*log(N))

//概要
//複数のmodでの結果を用いて復元する。

//verified with
//https://judge.yosupo.jp/problem/inv_of_formal_power_series
//https://judge.yosupo.jp/problem/log_of_formal_power_series
//https://judge.yosupo.jp/problem/exp_of_formal_power_series
//https://judge.yosupo.jp/problem/pow_of_formal_power_series

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

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

template<int mod, int primitive_root>
struct Number_Theorem_Transform{
    using T = Mod_Int<mod>;
    vector<T> r, ir;

    Number_Theorem_Transform(){
        r.resize(30), ir.resize(30);
        for(int i = 0; i < 30; i++){
            r[i] = -T(primitive_root).pow((mod-1)>>(i+2));
            ir[i] = r[i].inverse();
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

const int m1 = 1045430273, r1 = 3;
const int m2 = 1051721729, r2 = 6;
const int m3 = 1053818881, r3 = 7;

template<int mod>
struct Arbitary_Mod_Number_Theorem_Transform{
    using T = Mod_Int<mod>;
    using mint1 = Mod_Int<m1>;
    using mint2 = Mod_Int<m2>;
    using mint3 = Mod_Int<m3>;
    Number_Theorem_Transform<m1, r1> ntt1;
    Number_Theorem_Transform<m2, r2> ntt2;
    Number_Theorem_Transform<m3, r3> ntt3;

    Arbitary_Mod_Number_Theorem_Transform() {}

    vector<T> convolve(const vector<T> &a, const vector<T> &b){
        int n = a.size(), m = b.size();
        vector<mint1> a1(n), b1(m);
        vector<mint2> a2(n), b2(m);
        vector<mint3> a3(n), b3(m);
        for(int i = 0; i < n; i++) a1[i] = a[i].x, a2[i] = a[i].x, a3[i] = a[i].x;
        for(int i = 0; i < m; i++) b1[i] = b[i].x, b2[i] = b[i].x, b3[i] = b[i].x;
        auto x = ntt1.convolve(a1, b1);
        auto y = ntt2.convolve(a2, b2);
        auto z = ntt3.convolve(a3, b3);
        const auto m1_inv_m2 = mint2(m1).inverse().x;
        const auto m1m2_inv_m3 = (mint3(m1)*m2).inverse().x;
        const auto m1m2_mod = (mint(m1)*m2).x;
        vector<T> ret(n+m-1);
        for(int i = 0; i < n+m-1; i++){
            auto v1 = ((mint2(y[i])+m2-x[i].x)*m1_inv_m2).x;
            auto v2 = ((z[i]+m3-x[i].x-mint3(m1)*v1)*m1m2_inv_m3).x;
            ret[i] = (T(x[i].x))+T(m1)*v1+T(m1m2_mod)*v2;
        }
        return ret;
    }
};

Arbitary_Mod_Number_Theorem_Transform<MOD> NTT;

template<typename T>
struct Formal_Power_Series : vector<T>{
    using vector<T> :: vector;

    Formal_Power_Series(const vector<T> &v) : vector<T>(v) {}

    Formal_Power_Series pre(int n) const{
        return Formal_Power_Series(begin(*this), begin(*this)+min((int)this->size(), n));
    }

    Formal_Power_Series rev() const{
        Formal_Power_Series ret = *this;
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
        int n = this->size()-sz(v)+1;
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
            ret = (ret+ret-ret*ret*pre(i<<1)).pre(i<<1);
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

using fps = Formal_Power_Series<mint>;

int main(){
    int N, M; cin >> N >> M;

    fps f(N);
    for(int i = 0; i < N; i++) cin >> f[i];

    fps ans = f.pow(M);

    for(int i = 0; i < N; i++) cout << ans[i] << ' ';
    cout << '\n';
}
