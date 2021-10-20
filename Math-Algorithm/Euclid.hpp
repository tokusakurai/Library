
// ユークリッドの互除法を用いた種々の計算
// 計算量 gcd・lcm・extgcd・modinv・floor_sum・中国剰余定理 : O(log(max(a, b))), Garner : O(n^2)

// extgcd : ax+by = gcd(a,b)を満たす(x,y)の組の1つ
// floor_sum : Σ[0<=i<n] floor((ai+b)/m)
// 中国剰余定理 : x ≡ a_1(mod m_1), x ≡ a_2(mod m_2)を満たす最小の非負整数x
// Garner : x ≡ a_i(mod m_i) (0<=i<n)を満たす最小の非負整数xをMで割った余り

// 概要
// gcd・lcm・extgcd : ユークリッドの互除法を使って再帰的に解く。
// modinv : ax+my = 1を満たすxをextgcdで求める。
// floor_sum : 領域内の格子点の数とみなし、A<Mなら縦横をひっくり返すなどする。
// 中国剰余定理 : 解が存在する⇔a_1 ≡ a_2(mod gcd(m_1,m_2))
// Garnerの定理 : 解が存在する⇔任意のi,jについてa_i ≡ a_j(mod gcd(m_i,m_j))

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
T gcd(const T &a, const T &b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

template <typename T>
T lcm(const T &a, const T &b) {
    return a * (b / gcd(a, b));
}

template <typename T>
T extgcd(const T &a, const T &b, T &x, T &y) { // |x|と|y|は結果としてmax(a,b)以下になる。
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

int modinv(const int &a, const int &m) { // aとmは互いに素
    int x, y;
    extgcd(a, m, x, y);
    return mod(x, m);
}

template <typename T>
T floor_sum(const T &n, const T &m, T a, T b) { // Σ[0<=i<n] floor((ai+b)/m)
    T ret = (a / m) * (n * (n - 1) / 2) + (b / m) * n;
    a %= m, b %= m;
    T y = (a * n + b) / m;
    if (y == 0) return ret;
    ret += floor_sum(y, a, m, a * n - (m * y - b));
    return ret;
}

template <typename T>
pair<T, T> Chinese_reminder_theorem(const T &a1, const T &m1, const T &a2, const T &m2) {
    T x, y, g = extgcd(m1, m2, x, y);
    if ((a2 - a1) % g != 0) return make_pair(0, -1);
    T m = m1 * (m2 / g);
    T tmp = mod(x * ((a2 - a1) / g), m2 / g);
    T a = (m1 * tmp + a1) % m;
    return make_pair(a, m);
}

bool prepare_Garner(vector<int> &a, vector<int> &m) { // mの各要素がそれぞれ互いに素とは限らない場合の前処理
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int g = gcd(m[i], m[j]);
            if ((a[i] - a[j]) % g != 0) return false;
            m[i] /= g, m[j] /= g;
            int gi = gcd(m[i], g), gj = g / gi;
            do {
                g = gcd(gi, gj);
                gi *= g, gj /= g;
            } while (g > 1);
            m[i] *= gi, m[j] *= gj;
        }
    }
    return true;
}

int Garner(vector<int> a, vector<int> m, const int &M) { // mの各要素はそれぞれ互いに素
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
