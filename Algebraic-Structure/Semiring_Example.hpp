#pragma once

// 半環の例

// 定義
// (S,+,*,0,1) が半環であるとは
// 任意の a,b,c ∈ S について a+(b+c) = (a+b)+c (和の結合律)
// 任意の a,b ∈ S について a+b = b+a (和の交換律)
// 任意の a ∈ S について a+0 = 0+a = a
// 任意の a,b,c ∈ S について a*(b*c) = (a*b)*c (積の結合律)
// 任意の a ∈ S について a*1 = 1*a = a
// 任意の a,b,c ∈ S について a*(b+c) = (a*b)+(a*c) (分配律)
// 任意の a,b,c ∈ S について (a+b)*c = (a*c)+(b*c) (分配律)
// 任意の a ∈ S について a*0 = 0*a = 0
// を満たすことである。

#include <bits/stdc++.h>
using namespace std;

// (min, max)
template <typename T>
struct Min_Max_Semiring {
    using V = T;
    static constexpr V add(V a, V b) { return min(a, b); }
    static constexpr V mul(V a, V b) { return max(a, b); };
    static const V id_0, id_1;
};

template <typename T>
const T Min_Max_Semiring<T>::id_0 = numeric_limits<T>::max() / 2;

template <typename T>
const T Min_Max_Semiring<T>::id_1 = numeric_limits<T>::min() / 2;

// (max, min)
template <typename T>
struct Max_Min_Semiring {
    using V = T;
    static constexpr V add(V a, V b) { return max(a, b); }
    static constexpr V mul(V a, V b) { return min(a, b); };
    static const V id_0, id_1;
};

template <typename T>
const T Max_Min_Semiring<T>::id_0 = numeric_limits<T>::min() / 2;

template <typename T>
const T Max_Min_Semiring<T>::id_1 = numeric_limits<T>::max() / 2;

// (min, +)
template <typename T>
struct Min_Plus_Semiring {
    using V = T;
    static constexpr V add(V a, V b) { return min(a, b); }
    static constexpr V mul(V a, V b) { return a + b; };
    static const V id_0, id_1;
};

template <typename T>
const T Min_Plus_Semiring<T>::id_0 = numeric_limits<T>::max() / 2;

template <typename T>
const T Min_Plus_Semiring<T>::id_1 = 0;

// (max, +)
template <typename T>
struct Max_Plus_Semiring {
    using V = T;
    static constexpr V add(V a, V b) { return max(a, b); }
    static constexpr V mul(V a, V b) { return a + b; };
    static const V id_0, id_1;
};

template <typename T>
const T Max_Plus_Semiring<T>::id_0 = numeric_limits<T>::min() / 2;

template <typename T>
const T Max_Plus_Semiring<T>::id_1 = 0;

// (XOR, AND)
template <typename T>
struct XOR_AND_Semiring {
    using V = T;
    static constexpr V add(V a, V b) { return a ^ b; }
    static constexpr V mul(V a, V b) { return a & b; };
    static const V id_0, id_1;
};

template <typename T>
const T XOR_AND_Semiring<T>::id_0 = 0;

template <typename T>
const T XOR_AND_Semiring<T>::id_1 = numeric_limits<T>::max();
