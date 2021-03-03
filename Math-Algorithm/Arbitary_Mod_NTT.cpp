
//数論変換(高速剰余変換)(任意mod)
//計算量 O((N+M)*log(N+M))

//概要
//modをPとすると、剰余を取らない場合の畳込みをした結果の各項の最大値はP^2*max(N,M)程度となる。
//P<=2*10^9、N,M<=10^6であったとしても、3種類のNTTmod(10^9程度)での畳み込みの結果から復元することができる。

//verified with
//https://atcoder.jp/contests/practice2/tasks/practice2_f
//https://judge.yosupo.jp/problem/convolution_mod_1000000007

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

//(NTT素数、原始根)
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

int main(){
    int N, M; cin >> N >> M;

    vector<mint> a(N), b(M);
    for(int i = 0; i < N; i++) cin >> a[i];
    for(int i = 0; i < M; i++) cin >> b[i];

    vector<mint> c = NTT.convolve(a, b);
    for(auto &e: c) cout << e << ' ';
    cout << '\n';
}
