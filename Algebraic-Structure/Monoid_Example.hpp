#pragma once

// モノイドの例

// 定義
// (M,*,e) がモノイドであるとは
// 任意の a,b,c ∈ M について a*(b*c) = (a*b)*c (結合律)
// 任意の a ∈ M について a*e = e*a = a
// を満たすことである。

#include <bits/stdc++.h>
using namespace std;

// sum
template <typename T>
struct Plus_Monoid {
    using V = T;
    static constexpr V merge(const V &a, const V &b) { return a + b; };
    static const V id;
};

template <typename T>
const T Plus_Monoid<T>::id = 0;

// prod
template <typename T>
struct Product_Monoid {
    using V = T;
    static constexpr V merge(const V &a, const V &b) { return a * b; };
    static const V id;
};

template <typename T>
const T Product_Monoid<T>::id = 1;

// min
template <typename T>
struct Min_Monoid {
    using V = T;
    static constexpr V merge(const V &a, const V &b) { return min(a, b); };
    static const V id;
};

template <typename T>
constexpr T Min_Monoid<T>::id = numeric_limits<T>::max() / 2;

// max
template <typename T>
struct Max_Monoid {
    using V = T;
    static constexpr V merge(V a, V b) { return max(a, b); };
    static const V id;
};

template <typename T>
constexpr T Max_Monoid<T>::id = -(numeric_limits<T>::max() / 2);

// 代入
template <typename T>
struct Update_Monoid {
    using V = T;
    static constexpr V merge(const V &a, const V &b) {
        if (a == id) return b;
        if (b == id) return a;
        return b;
    }
    static const V id;
};

template <typename T>
constexpr T Update_Monoid<T>::id = numeric_limits<T>::max();

// min count (T：最大値の型、S：個数の型)
template <typename T, typename S>
struct Min_Count_Monoid {
    using V = pair<T, S>;
    static constexpr V merge(const V &a, const V &b) {
        if (a.first < b.first) return a;
        if (a.first > b.first) return b;
        return V(a.first, a.second + b.second);
    }
    static const V id;
};

template <typename T, typename S>
constexpr pair<T, S> Min_Count_Monoid<T, S>::id = make_pair(numeric_limits<T>::max() / 2, 0);

// max count (T：最大値の型、S：個数の型)
template <typename T, typename S>
struct Max_Count_Monoid {
    using V = pair<T, S>;
    static constexpr V merge(const V &a, const V &b) {
        if (a.first > b.first) return a;
        if (a.first < b.first) return b;
        return V(a.first, a.second + b.second);
    }
    static const V id;
};

template <typename T, typename S>
constexpr pair<T, S> Max_Count_Monoid<T, S>::id = make_pair(-(numeric_limits<T>::max() / 2), 0);

// 一次関数 ax+b の合成 (左から順に作用)
template <typename T>
struct Affine_Monoid {
    using V = pair<T, T>;
    static constexpr V merge(const V &a, const V &b) { return V(a.first * b.first, a.second * b.first + b.second); };
    static const V id;
};

template <typename T>
const pair<T, T> Affine_Monoid<T>::id = make_pair(1, 0);

// モノイドの直積
template <typename Monoid_1, typename Monoid_2>
struct Cartesian_Product_Monoid {
    using V1 = typename Monoid_1::V;
    using V2 = typename Monoid_2::V;
    using V = pair<V1, V2>;
    static constexpr V merge(const V &a, const V &b) { return V(Monoid_1::merge(a.first, b.first), Monoid_2::merge(a.second, b.second)); }
    static const V id;
};

template <typename Monoid_1, typename Monoid_2>
const pair<typename Monoid_1::V, typename Monoid_2::V> Cartesian_Product_Monoid<Monoid_1, Monoid_2>::id = make_pair(Monoid_1::id, Monoid_2::id);

// 行列積 (l*r)
template <typename T, int n>
struct Matrix_Monoid {
    using V = array<array<T, n>, n>;
    static constexpr V I() {
        V ret;
        for (int i = 0; i < n; i++) fill(begin(ret[i]), end(ret[i]), T(0));
        for (int i = 0; i < n; i++) ret[i][i] = 1;
        return ret;
    }
    static constexpr V merge(V l, V r) {
        V ret;
        for (int i = 0; i < n; i++) fill(begin(ret[i]), end(ret[i]), T(0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) ret[i][k] += l[i][j] * r[j][k];
            }
        }
        return ret;
    }
    static const V id;
};

template <typename T, int n>
const array<array<T, n>, n> Matrix_Monoid<T, n>::id = Matrix_Monoid<T, n>::I();

// 行列積 (r*l)
template <typename T, int n>
struct Matrix_Monoid_Rev {
    using V = array<array<T, n>, n>;
    static constexpr V I() {
        V ret;
        for (int i = 0; i < n; i++) fill(begin(ret[i]), end(ret[i]), T(0));
        for (int i = 0; i < n; i++) ret[i][i] = 1;
        return ret;
    }
    static constexpr V merge(V l, V r) {
        V ret;
        for (int i = 0; i < n; i++) fill(begin(ret[i]), end(ret[i]), T(0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) ret[i][k] += r[i][j] * l[j][k];
            }
        }
        return ret;
    }
    static const V id;
};

template <typename T, int n>
const array<array<T, n>, n> Matrix_Monoid_Rev<T, n>::id = Matrix_Monoid_Rev<T, n>::I();

// range add range min
template <typename T>
struct Min_Plus_Acted_Monoid {
    using Monoid = Min_Monoid<T>;
    using Operator = Plus_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return a + b; };
};

// range add range max
template <typename T>
struct Max_Plus_Acted_Monoid {
    using Monoid = Max_Monoid<T>;
    using Operator = Plus_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return a + b; };
};

// range add range min count (T：最小値の型、S：個数の型)
template <typename T, typename S>
struct Min_Count_Add_Acted_Monoid {
    using Monoid = Min_Count_Monoid<T, S>;
    using Operator = Plus_Monoid<T>;
    using M = pair<T, S>;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return make_pair(a.first + b, a.second); };
};

// range add range max count (T：最大値の型、S：個数の型)
template <typename T, typename S>
struct Max_Count_Add_Acted_Monoid {
    using Monoid = Max_Count_Monoid<T, S>;
    using Operator = Plus_Monoid<T>;
    using M = pair<T, S>;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return make_pair(a.first + b, a.second); };
};

// range add range sum
template <typename T>
struct Plus_Plus_Acted_Monoid {
    using Monoid = Cartesian_Product_Monoid<Plus_Monoid<T>, Plus_Monoid<int>>;
    using Operator = Plus_Monoid<T>;
    using M = pair<T, int>;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return M(a.first + b * a.second, a.second); }
};

// range update range sum
template <typename T>
struct Plus_Update_Acted_Monoid {
    using Monoid = Cartesian_Product_Monoid<Plus_Monoid<T>, Plus_Monoid<int>>;
    using Operator = Update_Monoid<T>;
    using M = pair<T, int>;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return b == Operator::id ? a : M(b * a.second, a.second); }
};

// range update range min
template <typename T>
struct Min_Update_Acted_Monoid {
    using Monoid = Min_Monoid<T>;
    using Operator = Update_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return b == Operator::id ? a : b; }
};

// range update range max
template <typename T>
struct Max_Update_Acted_Monoid {
    using Monoid = Max_Monoid<T>;
    using Operator = Update_Monoid<T>;
    using M = T;
    using O = T;
    static constexpr M merge(const M &a, const O &b) { return b == Operator::id ? a : b; }
};

// range affine range sum
template <typename T>
struct Plus_Affine_Acted_Monoid {
    using Monoid = Cartesian_Product_Monoid<Plus_Monoid<T>, Plus_Monoid<T>>;
    using Operator = Affine_Monoid<T>;
    using M = pair<T, T>;
    using O = pair<T, T>;
    static constexpr M merge(const M &a, const O &b) { return M(b.first * a.first + b.second * a.second, a.second); };
};
