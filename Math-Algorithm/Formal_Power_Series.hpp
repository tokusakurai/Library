
// 形式的冪級数
// 計算量 加算・減算・微分・積分：O(n)、積・除算・inv・log・exp・pow・Taylor Shift：O(n log(n))

// 各種演算はテイラー展開を用いて定義される（詳しくは下の verify url）

// 概要
// 積：NTT
// inv・exp：ニュートン法を用いた漸化式を立てて計算する。
// 除算：inv を用いて計算する。
// log：inv を用いて計算する。
// pow：log と exp を用いて計算する。
// Taylor Shift：係数を分解して畳み込みに持ち込む。

// verified with
// https://judge.yosupo.jp/problem/inv_of_formal_power_series
// https://judge.yosupo.jp/problem/log_of_formal_power_series
// https://judge.yosupo.jp/problem/exp_of_formal_power_series
// https://judge.yosupo.jp/problem/pow_of_formal_power_series
// https://judge.yosupo.jp/problem/division_of_polynomials
// https://judge.yosupo.jp/problem/polynomial_taylor_shift

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

template <typename T>
struct Formal_Power_Series : vector<T> {
    using NTT_ = Number_Theoretic_Transform<T>;
    using vector<T>::vector;

    Formal_Power_Series(const vector<T> &v) : vector<T>(v) {}

    Formal_Power_Series pre(int n) const { return Formal_Power_Series(begin(*this), begin(*this) + min((int)this->size(), n)); }

    Formal_Power_Series rev(int deg = -1) const {
        Formal_Power_Series ret = *this;
        if (deg != -1) ret.resize(deg, T(0));
        reverse(begin(ret), end(ret));
        return ret;
    }

    void normalize() {
        while (!this->empty() && this->back() == 0) this->pop_back();
    }

    Formal_Power_Series operator-() const {
        Formal_Power_Series ret = *this;
        for (int i = 0; i < (int)ret.size(); i++) ret[i] = -ret[i];
        return ret;
    }

    Formal_Power_Series &operator+=(const T &x) {
        if (this->empty()) this->resize(1);
        (*this)[0] += x;
        return *this;
    }

    Formal_Power_Series &operator+=(const Formal_Power_Series &v) {
        if (v.size() > this->size()) this->resize(v.size());
        for (int i = 0; i < (int)v.size(); i++) (*this)[i] += v[i];
        this->normalize();
        return *this;
    }

    Formal_Power_Series &operator-=(const T &x) {
        if (this->empty()) this->resize(1);
        *this[0] -= x;
        return *this;
    }

    Formal_Power_Series &operator-=(const Formal_Power_Series &v) {
        if (v.size() > this->size()) this->resize(v.size());
        for (int i = 0; i < (int)v.size(); i++) (*this)[i] -= v[i];
        this->normalize();
        return *this;
    }

    Formal_Power_Series &operator*=(const T &x) {
        for (int i = 0; i < (int)this->size(); i++) (*this)[i] *= x;
        return *this;
    }

    Formal_Power_Series &operator*=(const Formal_Power_Series &v) {
        if (this->empty() || empty(v)) {
            this->clear();
            return *this;
        }
        return *this = NTT_::convolve(*this, v);
    }

    Formal_Power_Series &operator/=(const T &x) {
        assert(x != 0);
        T inv = x.inverse();
        for (int i = 0; i < (int)this->size(); i++) (*this)[i] *= inv;
        return *this;
    }

    Formal_Power_Series &operator/=(const Formal_Power_Series &v) {
        if (v.size() > this->size()) {
            this->clear();
            return *this;
        }
        int n = this->size() - (int)v.size() + 1;
        return *this = (rev().pre(n) * v.rev().inv(n)).pre(n).rev(n);
    }

    Formal_Power_Series &operator%=(const Formal_Power_Series &v) { return *this -= (*this / v) * v; }

    Formal_Power_Series &operator<<=(int x) {
        Formal_Power_Series ret(x, 0);
        ret.insert(end(ret), begin(*this), end(*this));
        return *this = ret;
    }

    Formal_Power_Series &operator>>=(int x) {
        Formal_Power_Series ret;
        ret.insert(end(ret), begin(*this) + x, end(*this));
        return *this = ret;
    }

    Formal_Power_Series operator+(const T &x) const { return Formal_Power_Series(*this) += x; }

    Formal_Power_Series operator+(const Formal_Power_Series &v) const { return Formal_Power_Series(*this) += v; }

    Formal_Power_Series operator-(const T &x) const { return Formal_Power_Series(*this) -= x; }

    Formal_Power_Series operator-(const Formal_Power_Series &v) const { return Formal_Power_Series(*this) -= v; }

    Formal_Power_Series operator*(const T &x) const { return Formal_Power_Series(*this) *= x; }

    Formal_Power_Series operator*(const Formal_Power_Series &v) const { return Formal_Power_Series(*this) *= v; }

    Formal_Power_Series operator/(const T &x) const { return Formal_Power_Series(*this) /= x; }

    Formal_Power_Series operator/(const Formal_Power_Series &v) const { return Formal_Power_Series(*this) /= v; }

    Formal_Power_Series operator%(const Formal_Power_Series &v) const { return Formal_Power_Series(*this) %= v; }

    Formal_Power_Series operator<<(int x) const { return Formal_Power_Series(*this) <<= x; }

    Formal_Power_Series operator>>(int x) const { return Formal_Power_Series(*this) >>= x; }

    T val(const T &x) const {
        T ret = 0;
        for (int i = (int)this->size() - 1; i >= 0; i--) ret *= x, ret += (*this)[i];
        return ret;
    }

    Formal_Power_Series diff() const { // df/dx
        int n = this->size();
        Formal_Power_Series ret(n - 1);
        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * i;
        return ret;
    }

    Formal_Power_Series integral() const { // ∫fdx
        int n = this->size();
        Formal_Power_Series ret(n + 1);
        for (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / (i + 1);
        return ret;
    }

    Formal_Power_Series inv(int deg) const { // 1/f (f[0] != 0)
        assert((*this)[0] != T(0));
        Formal_Power_Series ret(1, (*this)[0].inverse());
        for (int i = 1; i < deg; i <<= 1) {
            Formal_Power_Series f = pre(2 * i), g = ret;
            f.resize(2 * i), g.resize(2 * i);
            NTT_::ntt(f), NTT_::ntt(g);
            Formal_Power_Series h(2 * i);
            for (int j = 0; j < 2 * i; j++) h[j] = f[j] * g[j];
            NTT_::intt(h);
            for (int j = 0; j < i; j++) h[j] = 0;
            NTT_::ntt(h);
            for (int j = 0; j < 2 * i; j++) h[j] *= g[j];
            NTT_::intt(h);
            for (int j = 0; j < i; j++) h[j] = 0;
            ret -= h;
        }
        ret.resize(deg);
        return ret;
    }

    Formal_Power_Series inv() const { return inv(this->size()); }

    Formal_Power_Series log(int deg) const { // log(f) (f[0] = 1)
        assert((*this)[0] == 1);
        Formal_Power_Series ret = (diff() * inv(deg)).pre(deg - 1).integral();
        ret.resize(deg);
        return ret;
    }

    Formal_Power_Series log() const { return log(this->size()); }

    Formal_Power_Series exp(int deg) const { // exp(f) (f[0] = 0)
        assert((*this)[0] == 0);
        Formal_Power_Series inv;
        inv.reserve(deg + 1);
        inv.push_back(0), inv.push_back(1);

        auto inplace_integral = [&](Formal_Power_Series &F) -> void {
            int n = F.size();
            int mod = T::get_mod();
            while ((int)inv.size() <= n) {
                int i = inv.size();
                inv.push_back((-inv[mod % i]) * (mod / i));
            }
            F.insert(begin(F), 0);
            for (int i = 1; i <= n; i++) F[i] *= inv[i];
        };

        auto inplace_diff = [](Formal_Power_Series &F) -> void {
            if (F.empty()) return;
            F.erase(begin(F));
            T coeff = 1, one = 1;
            for (int i = 0; i < (int)F.size(); i++) {
                F[i] *= coeff;
                coeff += one;
            }
        };

        Formal_Power_Series ret{1, this->size() > 1 ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
        for (int m = 2; m < deg; m *= 2) {
            auto y = ret;
            y.resize(2 * m);
            NTT_::ntt(y);
            z1 = z2;
            Formal_Power_Series z(m);
            for (int i = 0; i < m; i++) z[i] = y[i] * z1[i];
            NTT_::intt(z);
            fill(begin(z), begin(z) + m / 2, 0);
            NTT_::ntt(z);
            for (int i = 0; i < m; i++) z[i] *= -z1[i];
            NTT_::intt(z);
            c.insert(end(c), begin(z) + m / 2, end(z));
            z2 = c, z2.resize(2 * m);
            NTT_::ntt(z2);
            Formal_Power_Series x(begin(*this), begin(*this) + min((int)this->size(), m));
            inplace_diff(x);
            x.push_back(0);
            NTT_::ntt(x);
            for (int i = 0; i < m; i++) x[i] *= y[i];
            NTT_::intt(x);
            x -= ret.diff(), x.resize(2 * m);
            for (int i = 0; i < m - 1; i++) x[m + i] = x[i], x[i] = 0;
            NTT_::ntt(x);
            for (int i = 0; i < 2 * m; i++) x[i] *= z2[i];
            NTT_::intt(x);
            x.pop_back();
            inplace_integral(x);
            for (int i = m; i < min((int)this->size(), 2 * m); i++) x[i] += (*this)[i];
            fill(begin(x), begin(x) + m, 0);
            NTT_::ntt(x);
            for (int i = 0; i < 2 * m; i++) x[i] *= y[i];
            NTT_::intt(x);
            ret.insert(end(ret), begin(x) + m, end(x));
        }
        ret.resize(deg);
        return ret;
    }

    Formal_Power_Series exp() const { return exp(this->size()); }

    Formal_Power_Series pow(long long k, int deg) const { // f^k
        int n = this->size();
        for (int i = 0; i < n; i++) {
            if ((*this)[i] == 0) continue;
            T rev = (*this)[i].inverse();
            Formal_Power_Series C(*this * rev), D(n - i, 0);
            for (int j = i; j < n; j++) D[j - i] = C[j];
            D = (D.log() * k).exp() * ((*this)[i].pow(k));
            Formal_Power_Series E(deg, 0);
            if (i > 0 && k > deg / i) return E;
            long long S = i * k;
            for (int j = 0; j + S < deg && j < D.size(); j++) E[j + S] = D[j];
            E.resize(deg);
            return E;
        }
        return Formal_Power_Series(deg, 0);
    }

    Formal_Power_Series pow(long long k) const { return pow(k, this->size()); }

    Formal_Power_Series Taylor_shift(T c) const {
        int n = this->size();
        vector<T> ifac(n, 1);
        Formal_Power_Series f(n), g(n);
        for (int i = 0; i < n; i++) {
            f[n - 1 - i] = (*this)[i] * ifac[n - 1];
            if (i < n - 1) ifac[n - 1] *= i + 1;
        }
        ifac[n - 1] = ifac[n - 1].inverse();
        for (int i = n - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i;
        T pw = 1;
        for (int i = 0; i < n; i++) {
            g[i] = pw * ifac[i];
            pw *= c;
        }
        f *= g;
        Formal_Power_Series b(n);
        for (int i = 0; i < n; i++) b[i] = f[n - 1 - i] * ifac[i];
        return b;
    }
};
