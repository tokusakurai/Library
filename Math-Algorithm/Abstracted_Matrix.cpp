
//抽象化された行列
//計算量 積：O(N*M*P)、K乗：O(N^3*log(K))

//概要
//半環(R,+,*)に対して行列の積演算を行える。
//単位行列は、対角成分は1元、それ以外は0元。
//累乗：ダブリング

//verified with
//https://atcoder.jp/contests/abc009/tasks/abc009_4

#include <bits/stdc++.h>
using namespace std;

using type = unsigned int;
const type e0 = 0, e1 = UINT_MAX; //0元、1元

struct Semi_Ring{
    type x;
    Semi_Ring() {}
    Semi_Ring(type x) : x(x){}

    Semi_Ring &operator += (const Semi_Ring &p) {
        x ^= p.x;
        return *this;
    }

    Semi_Ring &operator *= (const Semi_Ring &p) {
        x &= p.x;
        return *this;
    }
    
    //(a+b)+c = a+(b+c)、0+a = a+0 = a、a+b = b+a
    //(a*b)*c = a*(b*c)、1*a = a*1 = a
    //a*(b+c) = a*b+a*c、(a+b)*c = a*c+b*c
    //0*a = a*0 = 0
    //これらを満たす演算の組として(+,*)、(XOR,AND)、(min,+)、(max,+)などがある

    Semi_Ring operator + (const Semi_Ring &p) const {return Semi_Ring(*this) += p;}

    Semi_Ring operator * (const Semi_Ring &p) const {return Semi_Ring(*this) *= p;}

    friend ostream &operator << (ostream &os, const Semi_Ring &p){
        return os << p.x;
    }

    friend istream &operator >> (istream &is, Semi_Ring &p){
        long long a;
        is >> a;
        p = Semi_Ring(a);
        return is;
    }
};

template<typename T>
struct Abstracted_Matrix{
    vector<vector<T>> A;

    Abstracted_Matrix(int n, int m) : A(n, vector<T>(m, T(e0))) {}

    int height() const {return A.size();}

    int width() const {return A.front().size();}

    inline const vector<T> &operator [] (int k) const {return A[k];}

    inline vector<T> &operator [] (int k) {return A[k];}

    static Abstracted_Matrix I(int l){
        Abstracted_Matrix ret(l, l);
        for(int i = 0; i < l; i++) ret[i][i] = T(e1);
        return ret;
    }

    Abstracted_Matrix &operator *= (const Abstracted_Matrix &B){
        int n = height(), m = width(), p = B.width();
        assert(m == B.height());
        Abstracted_Matrix ret(n, p);
        for(int i = 0; i < n; i++){
            for(int k = 0; k < m; k++){
                for(int j = 0; j < p; j++){
                    ret[i][j] += A[i][k]*B[k][j];
                }
            }
        }
        swap(A, ret.A);
        return *this;
    }

    Abstracted_Matrix operator * (const Abstracted_Matrix &B) const {return Abstracted_Matrix(*this) *= B;}

    Abstracted_Matrix pow(long long k){
        int n = height(), m = width();
        assert(n == m);
        Abstracted_Matrix now = *this, ret = I(n);
        for(; k > 0; k >>= 1, now *= now){
            if(k&1) ret *= now;
        }
        return ret;
    }
};

int main(){
    int N, K; cin >> N >> K; K--;

    Abstracted_Matrix<Semi_Ring> A(N, N), x(N, 1);

    for(int i = 0; i < N; i++) cin >> x[N-1-i][0];
    for(int i = 0; i < N; i++) cin >> A[0][i];
    for(int i = 0; i < N-1; i++) A[i+1][i] = e1;

    A = A.pow(K), A *= x;
    cout << A[N-1][0] << '\n';
}
