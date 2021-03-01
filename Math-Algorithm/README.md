# 数学アルゴリズム

## ユークリッドの互除法
ユークリッド互除法を用いるアルゴリズム。

- [ユークリッドの互除法](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Euclid.cpp) (gcd、lcm、extgcd、mod逆数、floor sum、中国剰余定理、Garnerのアルゴリズム)

## 素数・約数
素数・約数に関するアルゴリズム。

- [素数・約数](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Prime.cpp) (約数列挙、素因数分解、素数判定、エラトステネスの篩)

## 剰余演算
剰余演算に関するアルゴリズム。

- [剰余演算](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Modulo.cpp) (累乗、オイラーのφ関数、離散対数、位数、原始根)

- [modint構造体](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Mod_Int.cpp)

- [写像12相](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Twelvefold_Way.cpp) (二項係数、第2種スターリング数、ベル数)

## 行列
行列を用いた計算に関するアルゴリズム。加法と乗法の2つの二項演算を備えた集合が半環であるとき、行列積の演算を行うことができる。

- [行列](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Matrix.cpp) (積、累乗、簡約化、ガウスの消去法)

- [二元体行列](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/F2_Matrix.cpp) (bitsetを用いた二元体での簡約化の定数倍高速化)

- [抽象化行列](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Abstracted_Matrix.cpp) (半環に対して行列積の演算を行うことができる)

## Kitamasa法
初期値と線形漸化式で与えられる数列の任意の項を求めるアルゴリズム。

- [Kitamasa法](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Kitamasa.cpp)

## 畳み込み
畳み込み(ここでは多項式の掛け算)を高速に行うアルゴリズム。

### 高速フーリエ変換(FFT)
2つの多項式の積は、それぞれを複素数上で離散フーリエ変換し、両者の各項の積を取ったものを逆離散フーリエ変換することで得られる。このとき離散フーリエ変換・逆離散フーリエ変換がボトルネックとなっており、次数が2冪のときにこれらを高速に行えるアルゴリズムとして高速フーリエ変換が知られている。

- [高速フーリエ変換(FFT)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/FFT.cpp)

### 数論変換(NTT)
NTT素数を、自身から1引いたものが(配列の長さより)十分大きい2冪で割り切れる素数とする。NTT素数をmodとした剰余環では1の2冪(十分大きい)乗根を取ることが出来るため、高速フーリエ変換を適用することができる。代表的なNTT素数として998244353がある。

- [数論変換(NTT)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/NTT.cpp) (NTT素数modにおける畳込み)

いくつかのNTT素数modを用意して、Garnerのアルゴリズムで復元することによって任意modで畳み込みを行うことができる。

- [任意mod数論変換(NTT)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Arbitary_Mod_NTT.cpp) (任意modにおける畳込み)

## 形式的冪級数(FPS)
形式的冪級数(項の数が有限とは限らない多項式)の基本的な計算を行うアルゴリズム。

- [形式的冪級数(FPS)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/FPS.cpp) (NTT素数modにおける形式的冪級数)

- [任意mod形式的冪級数(FPS)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Arbitary_Mod_FPS.cpp) (任意modにおける形式的羃級数)
