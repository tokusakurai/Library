
//行列計算
//計算量 積 : O(M*N*P)、K乗 : O(N^3*log(K))、簡約化・ガウスの消去法 : O(M*N^2)

//累乗：ダブリング
//ガウスの消去法 : 行基本変形を繰り返すことで連立一次方程式の解を求める。

//verified with
//https://judge.yosupo.jp/problem/matrix_det
//https://judge.yosupo.jp/problem/system_of_linear_equations

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Matrix{
    vector<vector<T>> A;

    Matrix(int m, int n) : A(m, vector<T>(n, 0)) {}

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
        int m = height(), n = width(), p = B.width();
        assert(n == B.height());
        Matrix ret(m, p);
        for(int i = 0; i < m; i++){
            for(int k = 0; k < n; k++){
                for(int j = 0; j < p; j++){
                    ret[i][j] += A[i][k]*B[k][j];
                }
            }
        }
        swap(A, ret.A);
        return *this;
    }

    Matrix operator * (const Matrix &B) const {return Matrix(*this) *= B;}

    Matrix pow(long long k) const{
        int m = height(), n = width();
        assert(m == n);
        Matrix now = *this, ret = I(n);
        for(; k > 0; k >>= 1, now *= now){
            if(k&1) ret *= now;
        }
        return ret;
    }

    bool eq(const T &a, const T &b) const{
        return a == b;
        //return abs(a-b) <= EPS; //少数の場合
    }

    pair<int, T> row_reduction(vector<T> &b){ //行基本変形を用いて簡約化を行い、(階数、行列式)の組を返す
        int m = height(), n = width(), check = 0, rank = 0;
        T det = 1;
        assert(b.size() == m);
        for(int j = 0; j < n; j++){
            int pivot = check;
            for(int i = check; i < m; i++){
                if(A[i][j] != 0) pivot = i;
                //if(abs(A[i][j]) > abs(A[pivot][j])) pivot = i; //小数の場合
            }
            if(check != pivot) det *= T(-1);
            swap(A[check], A[pivot]), swap(b[check], b[pivot]);
            if(eq(A[check][j], T(0))) {det = T(0); continue;}
            rank++;
            det *= A[check][j];
            for(int k = j+1; k < n; k++) A[check][k] /= A[check][j];
            b[check] /= A[check][j];
            A[check][j] = T(1);
            for(int i = 0; i < m; i++){
                if(i == check) continue;
                for(int k = j+1; k < n; k++) A[i][k] -= A[i][j]*A[check][k];
                b[i] -= A[i][j]*b[check];
                A[i][j] = T(0);
            }
            if(++check == m) break;
        }
        return make_pair(rank, det);
    }

    pair<int, T> row_reduction(){
        vector<T> b(height(), T(0));
        return row_reduction(b);
    }

    vector<vector<T>> Gausiann_elimination(vector<T> b){ //Ax=bの解の1つと解空間の基底の組を返す
        int m = height(), n = width();
        row_reduction(b);
        vector<vector<T>> ret;
        vector<int> p(m, n);
        vector<bool> is_zero(n, true);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(!eq(A[i][j], T(0))) {p[i] = j; break;}
            }
            if(p[i] < n) is_zero[p[i]] = false;
            else if(!eq(b[i], T(0))) return {};
        }
        vector<T> x(n, T(0));
        for(int i = 0; i < m; i++){
            if(p[i] < n) x[p[i]] = b[i];
        }
        ret.push_back(x);
        for(int j = 0; j < n; j++){
            if(!is_zero[j]) continue;
            x[j] = T(1);
            for(int i = 0; i < m; i++){
                if(p[i] < n) x[p[i]] = -A[i][j];
            }
            ret.push_back(x), x[j] = T(0);
        }
        return ret;
    }
};
