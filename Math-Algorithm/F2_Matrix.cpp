
//二元体での行列
//計算量 簡約化：O(N*M^2/64)

//概要
//行iに行jを足す操作は行iに行jをXORする操作と同値なので、bitsetで高速化できる。

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct F2_Matrix{
    vector<T> A;

    F2_Matrix(int n) : A(n) {}

    int height() const {return A.size();}

    int width() const {return A.front().size();}

    inline const T &operator [] (int k) const {return A[k];}

    inline T &operator [] (int k) {return A[k];}

    int row_reduction(){
        int n = height(), m = width(), check = 0, rank = 0;
        for(int j = 0; j < m; j++){
            int pivot = check;
            for(int i = check; i < n; i++){
                if(A[i][j]) pivot = i;
            }
            swap(A[check], A[pivot]);
            if(!A[check][j]) continue;
            rank++;
            for(int i = 0; i < n; i++){
                if(i == check || !A[i][j]) continue;
                A[i] ^= A[check];
            }
            if(++check == n) break;
        }
        return rank;
    }
};

int main(){
    int N; cin >> N;

    F2_Matrix<bitset<10>> A(N);

    for(int i = 0; i < N; i++){
        int a; cin >> a;
        A[i] = a;
    }
    A.row_reduction();

    for(int i = 0; i < N; i++){
        for(int j = 0; j < 10; j++) cout << A[i][j];
        cout << '\n';
    }
}
