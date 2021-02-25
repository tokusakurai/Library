
//数論変換(高速剰余変換)(modはx*(2^y)+1で表されるもの(N+M<=2^y))
//計算量 O((N+M)*log(N+M))

//verified with
//https://atcoder.jp/contests/practice2/tasks/practice2_f
//https://judge.yosupo.jp/problem/convolution_mod

#include <bits/stdc++.h>
using namespace std;

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

using mint = Mod_Int<998244353>;

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

Number_Theorem_Transform<998244353, 3> NTT; //(素数、原始根)のペア

int main(){
    int N, M; cin >> N >> M;

    vector<mint> a(N), b(M);
    for(int i = 0; i < N; i++) cin >> a[i];
    for(int i = 0; i < M; i++) cin >> b[i];

    vector<mint> c = NTT.convolve(a, b);
    for(auto &e: c) cout << e << ' ';
    cout << '\n';
}
