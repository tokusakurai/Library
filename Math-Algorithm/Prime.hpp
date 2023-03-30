
// 素数・約数に関する計算
// 計算量 約数列挙・素因数分解・素数判定：O(√n)、1,2,...,n のうち k と互いに素な自然数の数え上げ：O(2^#{k の素因数})
// エラトステネスの篩：O(n log(log(n)))、オイラーの φ 関数テーブル：O(n log(log(n)))
// n 以下の素数の数え上げ：O(n^(3/4)/log(n))

// 概要
// 約数列挙・素因数分解・素数判定：自然数 n の素因数で √n より大きいものは高々 1 つなので、√n 以下の数全てについて割り切れるか調べる。
// 1,2,...,n のうち k と互いに素な自然数の数え上げ：約数包除
// エラトステネスの篩：前から順番に見て、注目している数が素数ならその数の倍数(その数は含めない)は全て素数ではないことになるので、テーブルを false に切り替える。
// 素数の数え上げ：h(x,n) := n 以下の素数で x 以下の素数で篩をかけたときに残る要素数 を利用する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=jp
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C&lang=jp
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C
// https://yukicoder.me/problems/no/2249

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> divisors(const T &n) {
    vector<T> ret;
    for (T i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    sort(begin(ret), end(ret));
    return ret;
}

template <typename T>
vector<pair<T, int>> prime_factor(T n) {
    vector<pair<T, int>> ret;
    for (T i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) cnt++, n /= i;
        if (cnt > 0) ret.emplace_back(i, cnt);
    }
    if (n > 1) ret.emplace_back(n, 1);
    return ret;
}

template <typename T>
bool is_prime(const T &n) {
    if (n == 1) return false;
    for (T i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// 1,2,...,n のうち k と互いに素である自然数の個数
template <typename T>
T count_coprime(T n, T k) {
    vector<pair<T, int>> ps = prime_factor(k);
    int m = ps.size();
    T ret = 0;
    for (int i = 0; i < (1 << m); i++) {
        T prd = 1;
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) prd *= ps[j].first;
        }
        ret += (__builtin_parity(i) ? -1 : 1) * (n / prd);
    }
    return ret;
}

vector<bool> Eratosthenes(const int &n) {
    vector<bool> ret(n + 1, true);
    if (n >= 0) ret[0] = false;
    if (n >= 1) ret[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (!ret[i]) continue;
        for (int j = i + i; j <= n; j += i) ret[j] = false;
    }
    return ret;
}

vector<int> Eratosthenes2(const int &n) {
    vector<int> ret(n + 1);
    iota(begin(ret), end(ret), 0);
    if (n >= 0) ret[0] = -1;
    if (n >= 1) ret[1] = -1;
    for (int i = 2; i * i <= n; i++) {
        if (ret[i] < i) continue;
        for (int j = i + i; j <= n; j += i) ret[j] = min(ret[j], i);
    }
    return ret;
}

// n 以下の素数の列挙
vector<int> enumerate_prime(int n) {
    if (n < 2) return {};
    if (n == 2) return {2};
    int m = n / 6;
    vector<bool> p1(m + 1, true), p5(m + 1, true);
    p1[0] = false;
    vector<int> ret = {2, 3};
    for (int i = 0; i <= m; i++) {
        int a = 6 * i + 1, b = 6 * i + 5;
        if (a <= n && p1[i]) {
            ret.push_back(a);
            for (int j = a + i; j <= m; j += a) p1[j] = false;
            for (int j = 5 * i; j <= m; j += a) p5[j] = false;
        }
        if (b <= n && p5[i]) {
            ret.push_back(b);
            for (int j = b + i; j <= m; j += b) p5[j] = false;
            for (int j = 5 * i + 4; j <= m; j += b) p1[j] = false;
        }
    }
    return ret;
}

// i 以下で i と互いに素な自然数の個数のテーブル
vector<int> Euler_totient_table(const int &n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) dp[i] = i;
    for (int i = 2; i <= n; i++) {
        if (dp[i] == i) {
            dp[i]--;
            for (int j = i + i; j <= n; j += i) {
                dp[j] /= i;
                dp[j] *= i - 1;
            }
        }
    }
    return dp;
}

// n 以下の素数の数え上げ
template <typename T>
T count_prime(T n) {
    if (n < 2) return 0;
    vector<T> ns = {0};
    for (T i = n; i > 0; i = n / (n / i + 1)) ns.push_back(i);
    vector<T> h = ns;
    for (T &x : h) x--;
    for (T x = 2, m = sqrtl(n), k = ns.size(); x <= m; x++) {
        if (h[k - x] == h[k - x + 1]) continue; // h(x-1,x-1) = h(x-1,x) ならば x は素数ではない
        T x2 = x * x, pi = h[k - x + 1];
        for (T i = 1, j = ns[i]; i < k && j >= x2; j = ns[++i]) h[i] -= h[i * x <= m ? i * x : k - j / x] - pi;
    }
    return h[1];
}

// 約数包除に用いる係数テーブル (平方数で割り切れるなら 0、素因数の種類が偶数なら +1、奇数なら -1)
vector<int> inclusion_exclusion_table(int n) {
    auto p = Eratosthenes2(n);
    vector<int> ret(n + 1, 0);
    if (n >= 1) ret[1] = 1;
    for (int i = 2; i <= n; i++) {
        int x = p[i], j = i / x;
        ret[i] = (p[j] == x ? 0 : -ret[j]);
    }
    return ret;
}
