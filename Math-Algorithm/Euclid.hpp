
// ユークリッドの互除法を用いた種々の計算
// 計算量 binary gcd・lcm・extgcd・modinv・floor_sum・linear_mod_min・中国剰余定理：O(log(max(a, b)))、Garner：O(n^2)

// extgcd：ax+by = gcd(a,b) を満たす (x,y) の組の 1 つ
// floor_sum：Σ[0<=i<n] floor((ai+b)/m)
// linear_mod_min：min{(ai+b) mod m | 0<=i<n}
// 中国剰余定理：x ≡ a_1(mod m_1), x ≡ a_2(mod m_2) を満たす最小の非負整数 x
// Garner：x ≡ a_i(mod m_i) (0<=i<n) を満たす最小の非負整数 x を M で割った余り

// 概要
// binary gcd：a, b が 2 で割り切れるなら割り切れるだけ割る。どちらも奇数なら大きい方から小さい方を引くことで偶数にする。
// extgcd：ユークリッドの互除法を使って再帰的に解く。
// modinv：ax+my = 1 を満たす x を extgcd で求める。
// floor_sum：領域内の格子点の数とみなし、a < m なら縦横をひっくり返すなどする。
// linear_mod_min：答えが a 未満である場合、先頭 a 個の推移にのみ注目して再帰することで解ける。
// 中国剰余定理：解が存在する <-> a_1 ≡ a_2(mod gcd(m_1,m_2))
// Garnerの定理：解が存在する <-> 任意の i,j について a_i ≡ a_j(mod gcd(m_i,m_j))

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_B&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_C&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp
// https://judge.yosupo.jp/problem/sum_of_floor_of_linear
// https://yukicoder.me/problems/no/186
// https://yukicoder.me/problems/no/187

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T binary_gcd(T a, T b) {
    T g = 1;
    while (true) {
        if (a < b) swap(a, b);
        if (b == 0) {
            g *= a;
            break;
        }
        if (!(a & 1)) {
            if (!(b & 1)) {
                a >>= 1, b >>= 1, g <<= 1;
            } else {
                a >>= 1;
            }
        } else {
            if (!(b & 1)) {
                b >>= 1;
            } else {
                a = (a - b) >> 1;
            }
        }
    }
    return g;
}

template <typename T>
T binary_lcm(const T &a, const T &b) {
    return a * (b / binary_gcd(a, b));
}

// |x| と |y| は結果として max(a,b) 以下になる。
template <typename T>
T extgcd(const T &a, const T &b, T &x, T &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    T g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

int mod(const long long &a, const int &m) {
    int ret = a % m;
    return ret + (ret < 0 ? m : 0);
}

// a と m は互いに素
int modinv(const int &a, const int &m) {
    int x, y;
    extgcd(a, m, x, y);
    return mod(x, m);
}

// Σ[0<=i<n] floor((ai+b)/m)
template <typename T>
T floor_sum(const T &n, const T &m, T a, T b) {
    T ret = (a / m) * (n * (n - 1) / 2) + (b / m) * n;
    a %= m, b %= m;
    T y = (a * n + b) / m;
    if (y == 0) return ret;
    ret += floor_sum(y, a, m, a * n - (m * y - b));
    return ret;
}

// min{ai+b mod m | 0<=i<n} またがないときコスト p, またぐときコスト q
template <typename T>
T linear_mod_min(T n, const T &m, T a, T b, bool is_min = true, T p = 1, T q = 1) {
    if (a == 0) return b;
    if (is_min) {
        if (b >= a) {
            T t = (m - b + a - 1) / a;
            T c = (t - 1) * p + q;
            if (n <= c) return b;
            n -= c;
            b += a * t - m;
        }
        b = a - 1 - b;
    } else {
        if (b < m - a) {
            T t = (m - b - 1) / a;
            T c = t * p;
            if (n <= c) return a * ((n - 1) / p) + b;
            n -= c;
            b += a * t;
        }
        b = m - 1 - b;
    }
    T d = m / a;
    T c = linear_mod_min(n, a, m % a, b, !is_min, (d - 1) * p + q, d * p + q);
    return is_min ? a - 1 - c : m - 1 - c;
}

template <typename T>
pair<T, T> Chinese_remainder_theorem(const T &a1, const T &m1, const T &a2, const T &m2) {
    T x, y, g = extgcd(m1, m2, x, y);
    if ((a2 - a1) % g != 0) return make_pair(0, -1);
    T m = m1 * (m2 / g);
    T tmp = mod(x * ((a2 - a1) / g), m2 / g);
    T a = (m1 * tmp + a1) % m;
    return make_pair(a, m);
}

// m の各要素がそれぞれ互いに素とは限らない場合の前処理
bool prepare_Garner(vector<int> &a, vector<int> &m) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int g = binary_gcd(m[i], m[j]);
            if ((a[i] - a[j]) % g != 0) return false;
            m[i] /= g, m[j] /= g;
            int gi = binary_gcd(m[i], g), gj = g / gi;
            do {
                g = binary_gcd(gi, gj);
                gi *= g, gj /= g;
            } while (g > 1);
            m[i] *= gi, m[j] *= gj;
        }
    }
    return true;
}

// m の各要素はそれぞれ互いに素
int Garner(vector<int> a, vector<int> m, const int &M) {
    m.push_back(M);
    vector<long long> coeffs(m.size(), 1);
    vector<long long> constants(m.size(), 0);
    for (int k = 0; k < (int)a.size(); k++) {
        long long x = a[k] - constants[k], y = modinv(coeffs[k], m[k]);
        long long t = mod(x * y, m[k]);
        for (int i = k + 1; i < (int)m.size(); i++) {
            constants[i] += t * coeffs[i], constants[i] %= m[i];
            coeffs[i] *= m[k], coeffs[i] %= m[i];
        }
    }
    return constants.back();
}
