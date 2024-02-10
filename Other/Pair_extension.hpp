#pragma once
// std::pair に対する std::numeric_limits と各種演算子の拡張。
// 計算量 O(1)

// 概要
// std::numeric_limits については max() と min() で各要素の最大値と最小値の pair を返す。
// 同じテンプレートパラメータを持つ pair 同士については要素ごとの四則演算に対応。
// 除算と乗算については first, second 両方に数を掛ける/割る演算にも対応している。

#include <bits/stdc++.h>
using namespace std;

template<>
template<class T, class S>
struct numeric_limits<pair<T, S>> {
    static constexpr pair<T, S> min() {
        return  make_pair(numeric_limits<T>::min(),
                          numeric_limits<S>::min());
    }
    static constexpr pair<T, S> max() {
        return  make_pair(numeric_limits<T>::max(),
                          numeric_limits<S>::max());
    }
};

template<class T, class S>
pair<T, S> operator+(const pair<T, S> &lhs, const pair<T, S> &rhs) {
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

template<class T, class S>
pair<T, S> operator+=(pair<T, S> &lhs, const pair<T, S> &rhs) {
    return lhs = lhs + rhs;
}

template<class T, class S>
pair<T, S> operator-(const pair<T, S> &lhs, const pair<T, S> &rhs) {
    return make_pair(lhs.first - rhs.first, lhs.second - rhs.second);
}

template<class T, class S>
pair<T, S> operator-=(pair<T, S> &lhs, const pair<T, S> &rhs) {
    return lhs = lhs - rhs;
}

template<class T, class S>
pair<T, S> operator*(const pair<T, S> &lhs, const pair<T, S> &rhs) {
    return make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}

template<class T, class S, class U>
pair<T, S> operator*(const pair<T, S> &lhs, const U &rhs) {
    return make_pair(lhs.first * rhs, lhs.second * rhs);
}

template<class T, class S, class U>
pair<T, S> operator*(const U &lhs, const pair<T, S> &rhs) {
    return make_pair(lhs * rhs.first, lhs * rhs.second);
}

template<class T, class S, class U>
pair<T, S> operator*=(pair<T, S> &lhs, const U &rhs) {
    return lhs = lhs * rhs;
}

template<class T, class S>
pair<T, S> operator/(const pair<T, S> &lhs, const pair<T, S> &rhs) {
    return make_pair(lhs.first / rhs.first, lhs.second / rhs.second);
}

template<class T, class S, class U>
pair<T, S> operator/(const pair<T, S> &lhs, const U &rhs) {
    return make_pair(lhs.first / rhs, lhs.second / rhs);
}

template<class T, class S, class U>
pair<T, S> operator/=(pair<T, S> &lhs, const U &rhs) {
    return lhs = lhs / rhs;
}

void pair_extention_test() {
    auto eq = [](double a, double b) {
        return abs(a - b) < 1e-10;
    };

    assert((numeric_limits<pair<int, long long>>::min().first == 
            numeric_limits<int>::min()));
    assert((numeric_limits<pair<int, long long>>::min().second == 
            numeric_limits<long long>::min()));
    assert((numeric_limits<pair<int, long long>>::max().first == 
            numeric_limits<int>::max()));
    assert((numeric_limits<pair<int, long long>>::max().second == 
            numeric_limits<long long>::max()));
    pair<double, pair<int, complex<double>>> a = {1.0, {5, {-4.0, 7.0}}},
                                             b = {3.0, {2, { 2.0, 3.0}}};
    {
        auto c = a + b;
        assert(c.first == 4.0);
        assert(c.second.first == 7);
        assert(eq(c.second.second.real(), -2.0));
        assert(eq(c.second.second.imag(), 10.0));
    }
    {
        auto c = a;
        c += b;
        assert(c.first == 4.0);
        assert(c.second.first == 7);
        assert(eq(c.second.second.real(), -2.0));
        assert(eq(c.second.second.imag(), 10.0));
    }
    {
        auto c = a - b;
        assert(c.first == -2.0);
        assert(c.second.first == 3);
        assert(eq(c.second.second.real(), -6.0));
        assert(eq(c.second.second.imag(), 4.0));
    }
    {
        auto c = a;
        c -= b;
        assert(c.first == -2.0);
        assert(c.second.first == 3);
        assert(eq(c.second.second.real(), -6.0));
        assert(eq(c.second.second.imag(), 4.0));
    }
    {
        auto c = a * b;
        assert(c.first == 3.0);
        assert(c.second.first == 10);
        assert(eq(c.second.second.real(), -29.0));
        assert(eq(c.second.second.imag(), 2.0));
    }
    {
        auto c = a;
        c *= b;
        assert(c.first == 3.0);
        assert(c.second.first == 10);
        assert(eq(c.second.second.real(), -29.0));
        assert(eq(c.second.second.imag(), 2.0));
    }
    {
        auto c = a / b;
        assert(c.first == 1.0/3.0);
        assert(c.second.first == 2);
        assert(eq(c.second.second.real(), 1.0));
        assert(eq(c.second.second.imag(), 2.0));
    }
    {
        auto c = a;
        c /= b;
        assert(c.first == 1.0/3.0);
        assert(c.second.first == 2);
        assert(eq(c.second.second.real(), 1.0));
        assert(eq(c.second.second.imag(), 2.0));
    }
    {
        auto c = a * 2.0;
        assert(c.first == 2.0);
        assert(c.second.first == 10);
        assert(eq(c.second.second.real(), -8.0));
        assert(eq(c.second.second.imag(), 14.0));
    }
    {
        auto c = 2.0 * a;
        assert(c.first == 2.0);
        assert(c.second.first == 10);
        assert(eq(c.second.second.real(), -8.0));
        assert(eq(c.second.second.imag(), 14.0));
    }
    {
        auto c = a;
        c *= 2.0;
        assert(c.first == 2.0);
        assert(c.second.first == 10);
        assert(eq(c.second.second.real(), -8.0));
        assert(eq(c.second.second.imag(), 14.0));
    }
    {
        auto c = a / 2.0;
        assert(c.first == 0.5);
        assert(c.second.first == 2);
        assert(eq(c.second.second.real(), -2.0));
        assert(eq(c.second.second.imag(), 3.5));
    }
    {
        auto c = a;
        c /= 2.0;
        assert(c.first == 0.5);
        assert(c.second.first == 2);
        assert(eq(c.second.second.real(), -2.0));
        assert(eq(c.second.second.imag(), 3.5));
    }
}
