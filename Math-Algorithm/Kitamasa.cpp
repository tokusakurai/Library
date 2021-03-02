
//kitamasa法(N階の線形漸化式(N>=2)で与えられる数列の第K項を求める)
//計算量 O(N^2*log(K))

//概要
//a_k=Σb_i*a_i (i=0,1,2....,N-1)の形で表したい。
//f(x):=x^N-c_(N-1)*x^(N-1)-・・・-c_1*x-c_0とすると、
//x^kをf(x)で割った余りのx^iの項の係数がb_iに対応する。

//verified with
//https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Kitamasa{
    //f(x):=x^N-c[N-1]*x^(N-1)-・・・-c[1]*x-c[0]
    //a[k]=c[0]*a[k-N]+c[1]*a[k-N+1]+・・・+c[N-1]*a[k-1]
    const vector<T> a, c;

    Kitamasa(const vector<T> &a, const vector<T> &c) : a(a), c(c) {}

    vector<T> mul(const vector<T> &p, const vector<T> &q) const{ //p(x)*q(x)をf(x)で割った余り
        assert(p.size() == q.size() && p.size() >= 2);
        int n = p.size();
        vector<T> ret(2*n-1, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++) ret[i+j] += p[i]*q[j];
        }
        for(int i = 2*n-2; i >= n; i--){
            for(int j = 0; j < n; j++){
                ret[i-n+j] += ret[i]*c[j];
            }
        }
        ret.resize(n);
        return ret;
    }

    vector<T> pow(vector<T> p, long long k) const{ //p(x)^kをf(x)で割った余り
        int n = p.size();
        vector<T> ret(n, 0);
        ret[0] = 1;
        while(k){
            if(k&1) ret = mul(ret, p);
            p = mul(p, p), k >>= 1;
        }
        return ret;
    }

    T operator [] (int k) const{ //a[k](0-indexed)
        int n = a.size();
        vector<T> x(n, 0);
        x[1] = 1, x = pow(x, k);
        T ret = 0;
        for(int i = 0; i < n; i++) ret += x[i]*a[i];
        return ret;
    }
};

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

int main(){
    int N, K; cin >> N >> K;

    vector<mint> a(N, 1), c(N, 1);

    Kitamasa<mint> A(a, c);
    cout << A[K-1] << '\n';
}
