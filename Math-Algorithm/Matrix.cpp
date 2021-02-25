
//行列計算
//計算量 積:O(N*M*P)、K乗:O(N^3*log(K))、簡約化・ガウスの消去法:O(N*M^2)

//verified with
//https://judge.yosupo.jp/problem/matrix_det
//https://judge.yosupo.jp/problem/system_of_linear_equations

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

template<typename T>
struct Matrix{
    vector<vector<T>> A;

    Matrix(int n, int m) : A(n, vector<T>(m, 0)) {}

    int height() const {return A.size();}

    int width() const {return A.front().size();}

    inline const vector<T> &operator [] (int k) const {return A[k];}

    inline vector<T> &operator [] (int k) {return A[k];}

    static Matrix I(int l){
        Matrix ret(l, l);
        for(int i = 0; i < l; i++) ret[i][i] = 1;
        return ret;
    }

    Matrix &operator *= (const Matrix &B){
        int n = height(), m = width(), p = B.width();
        assert(m == B.height());
        Matrix ret(n, p);
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

    Matrix operator * (const Matrix &B) const {return Matrix(*this) *= B;}

    Matrix pow(long long k){
        int n = height(), m = width();
        assert(n == m);
        Matrix now = *this, ret = I(n);
        for(; k > 0; k >>= 1, now *= now){
            if(k&1) ret *= now;
        }
        return ret;
    }

    bool eq(const T &a, const T &b) const{
        return a == b;
        //return abs(a-b) <= EPS; //Tが小数の場合はこちら
    }

    pair<int, T> row_reduction(){ //行基本変形を用いて簡約化を行い、(階数、行列式)の組を返す
        int n = height(), m = width(), check = 0, rank = 0;
        T det = 1;
        for(int j = 0; j < m; j++){
            int pivot = check;
            for(int i = check; i < n; i++){
                if(A[i][j] != 0) pivot = i;
                //if(abs(A[i][j]) > abs(A[pivot][j])) pivot = i; //Tが小数の場合はこちら
            }
            if(check != pivot) det *= T(-1);
            swap(A[check], A[pivot]);
            if(eq(A[check][j], 0)) {det = T(0); continue;}
            rank++;
            det *= A[check][j];
            for(int k = j+1; k < m; k++) A[check][k] /= A[check][j];
            A[check][j] = 1;
            for(int i = 0; i < n; i++){
                if(i == check) continue;
                for(int k = j+1; k < m; k++) A[i][k] -= A[i][j]*A[check][k];
                A[i][j] = 0;
            }
            if(++check == n) break;
        }
        return make_pair(rank, det);
    }

    vector<vector<T>> Gausiann_elimination(const vector<T> &b){ //Ax=bの解の1つと解空間の基底の組を返す
        int n = height(), m = width();
        assert(b.size() == n);
        for(int i = 0; i < n; i++) A[i].push_back(b[i]);
        row_reduction();
        vector<vector<T>> ret;
        vector<int> p(n, m+1);
        vector<bool> is_zero(m, true);
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= m; j++){
                if(!eq(A[i][j], 0)) {p[i] = j; break;}
            }
            if(p[i] < m) is_zero[p[i]] = false;
            if(p[i] == m) return ret;
        }
        vector<T> basis(m, 0);
        for(int i = 0; i < n; i++){
            if(p[i] < m) basis[p[i]] = A[i][m];
        }
        ret.push_back(basis);
        for(int j = 0; j < m; j++){
            if(!is_zero[j]) continue;
            basis[j] = 1;
            for(int i = 0; i < n; i++){
                if(p[i] < m) basis[p[i]] = -A[i][j];
            }
            ret.push_back(basis), basis[j] = 0;
        }
        return ret;
    }
};

int main(){
    int N, M; cin >> N >> M;

    Matrix<mint> A(N, M);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++) cin >> A[i][j];
    }

    vector<mint> b(N);
    for(int i = 0; i < N; i++) cin >> b[i];

    vector<vector<mint>> ans = A.Gausiann_elimination(b);
    cout << (int)ans.size()-1 << '\n';
    
    for(auto &e: ans){
        for(auto &u : e) cout << u << ' ';
        cout << '\n';
    }
}
