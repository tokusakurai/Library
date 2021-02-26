
//高速ゼータ変換、高速メビウス変換、高速アダマール変換
//計算量 高速ゼータ変換・高速メビウス変換・高速アダマール変換：O(N*log(N))

//ゼータ変換：g(T) = Σf(S) (S⊇T) (上位集合)、 g(T) = Σf(S) (S⊆T) (下位集合)
//メビウス変換：ゼータ変換の逆変換
//アダマール変換：アダマール行列を左から作用させる

//概要
//高速ゼータ変換：長さnの2進数表記をn次元空間での座標のように見なせば、n次元の累積和であるとみなすことができる。
//高速メビウス変換：同様に、n次元の差分であるとみなすことができる。
//高速アダマール変換：アダマール行列の(i,j)成分=(-1)^(i・j) ((i・j)はn次元ベクトルとみたときのiとjの内積)
//AND畳み込み：a,bを上位集合で高速ゼータ変換⇒両者の各項の積を取る⇒上位集合で高速メビウス変換
//OR畳み込み：a,bを上位集合で高速ゼータ変換⇒両者の各項の積を取る⇒上位集合で高速メビウス変換
//XOR畳み込み：a,bを高速アダマール変換⇒両者の各項の積を取る⇒高速逆アダマール変換

//verified with
//https://judge.yosupo.jp/problem/bitwise_and_convolution
//https://judge.yosupo.jp/problem/bitwise_xor_convolution

#include <bits/stdc++.h>
using namespace std;

template<typename T>
void Fast_Zeta_Transform(vector<T> &f, bool upper){
    int n = f.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                if(upper) f[j] += f[j|i];
                else f[j|i] += f[j];
            }
        }
    }
}

template<typename T>
void Fast_Mobius_Transform(vector<T> &f, bool upper){
    int n = f.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                if(upper) f[j] -= f[j|i];
                else f[j|i] -= f[j];
            }
        }
    }
}

template<typename T>
void Fast_Hadamard_Transform(vector<T> &f, bool inverse = false){
    int n = f.size();
    assert((n&(n-1)) == 0);
    for(int i = 1; i < n; i <<= 1){
        for(int j = 0; j < n; j++){
            if(!(j&i)){
                T x = f[j], y = f[j|i];
                f[j] = x+y, f[j|i] = x-y;
            }
        }
    }
    if(inverse) for(auto &e : f) e /= n;
}

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

int main(){
    int N; cin >> N;

    vector<mint> a(1<<N), b(1<<N);
    for(int i = 0; i < (1<<N); i++) cin >> a[i];
    for(int i = 0; i < (1<<N); i++) cin >> b[i];

    Fast_Hadamard_Transform(a, false), Fast_Hadamard_Transform(b, false);

    vector<mint> c(1<<N);
    for(int i = 0; i < (1<<N); i++) c[i] = a[i]*b[i];

    Fast_Hadamard_Transform(c, true);

    for(int i = 0; i < (1<<N); i++) cout << c[i] << ' ';
    cout << '\n';
}
