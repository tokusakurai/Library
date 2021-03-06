
//二元体での行列
//計算量 簡約化・ガウスの消去法：O(M*N^2/64)

//概要
//行iに行jを足す操作は行iに行jをXORする操作と同値なので、bitsetで高速化できる。

//verified with
//https://yukicoder.me/problems/no/1421

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct F2_Matrix{
    vector<T> A;

    F2_Matrix(int m) : A(m) {}

    int height() const {return A.size();}

    int width() const {return A.front().size();}

    inline const T &operator [] (int k) const {return A[k];}

    inline T &operator [] (int k) {return A[k];}

    int row_reduction(vector<int> &b){ //行基本変形を用いて簡約化を行い、rankを返す。
        int m = height(), n = width(), check = 0, rank = 0;
        assert(b.size() == m);
        for(int j = 0; j < n; j++){
            int pivot = check;
            for(int i = check; i < m; i++){
                if(A[i][j]) pivot = i;
            }
            swap(A[check], A[pivot]), swap(b[check], b[pivot]);
            if(!A[check][j]) continue;
            rank++;
            for(int i = 0; i < m; i++){
                if(i == check || !A[i][j]) continue;
                A[i] ^= A[check], b[i] ^= b[check];
            }
            if(++check == m) break;
        }
        return rank;
    }

    int row_reduction(){
        vector<int> b(height(), 0);
        return row_reduction(b);
    }

    vector<vector<int>> Gausiann_elimination(vector<int> b){
        int m = height(), n = width();
        row_reduction(b);
        vector<vector<int>> ret;
        vector<int> p(m, n);
        vector<bool> is_zero(n, true);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(A[i][j] == 1) {p[i] = j; break;}
            }
            if(p[i] < n) is_zero[p[i]] = false;
            else if(b[i] == 1) return {};
        }
        vector<int> x(n, 0);
        for(int i = 0; i < m; i++){
            if(p[i] < n) x[p[i]] = b[i];
        }
        ret.push_back(x);
        for(int j = 0; j < n; j++){
            if(!is_zero[j]) continue;
            x[j] = 1;
            for(int i = 0; i < m; i++){
                if(p[i] < n) x[p[i]] ^= A[i][j];
            }
            ret.push_back(x), x[j] = 0;
        }
        return ret;
    }
};

int main(){
    int N, M; cin >> N >> M;

    vector<int> Y(M);
    vector<vector<int>> B(M);

    for(int i = 0; i < M; i++){
        int K; cin >> K;
        B[i].resize(K);
        for(int j = 0; j < K; j++) {cin >> B[i][j]; B[i][j]--;}
        cin >> Y[i];
    }

    using mat = F2_Matrix<bitset<50>>;

    vector<int> ret(N, 0);

    for(int i = 0; i < 30; i++){
        mat A(M);
        vector<int> b(M, 0);

        for(int j = 0; j < M; j++){
            for(auto &e: B[j]) A[j][e] = 1;
            b[j] = (Y[j]>>i)&1;
        }

        vector<vector<int>> ans = A.Gausiann_elimination(b);

        if(ans.empty()) {cout << "-1\n"; return 0;}

        for(int j = 0; j < N; j++){
            if(ans[0][j] == 1) ret[j] |= (1<<i);
        }
    }

    for(int i = 0; i < N; i++) cout << ret[i] << '\n';
}