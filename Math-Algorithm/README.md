# 数学アルゴリズム

## ユークリッドの互除法
ユークリッド互除法を用いるアルゴリズム。

- [ユークリッドの互除法](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Euclid.hpp) (gcd、lcm、extgcd、mod逆数、floor sum、中国剰余定理、Garnerのアルゴリズム)

## 素数・約数
素数・約数に関するアルゴリズム。

- [素数・約数](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Prime.hpp) (約数列挙、素因数分解、素数判定、エラトステネスの篩)

## 剰余演算
剰余演算に関するアルゴリズム。

- [剰余演算](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Modulo.hpp) (累乗、オイラーのφ関数、離散対数、位数、原始根)

- [テトレーション](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Tetration.hpp)

- [mod-int構造体](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Mod_Int.hpp)

- [実行時入力mod-int構造体](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Runtime_Mod_Int.hpp)

- [写像12相](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Twelvefold_Way.hpp) (二項係数、第2種スターリング数、ベル数)

## 数列
各種数列のテーブルを計算するアルゴリズム。

- [スターリング数](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Stirling_Number.hpp) (第1種スターリング数、第2種スターリング数のテーブル)

- [モンモール数](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Montmort_Number.hpp) (完全順列の個数のテーブル)

## 2-SAT
リテラル数が2以下のクロージャーの積で表される論理式の充足可能性を判定するアルゴリズム。
- [2-SAT](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Two_SAT.hpp)

## 行列
行列を用いた計算に関するアルゴリズム。加法と乗法の2つの二項演算を備えた集合が半環であるとき、行列積の演算を行うことができる。

- [行列](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Matrix.hpp) (積、累乗、簡約化、ガウスの消去法)

- [二元体行列](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/F2_Matrix.hpp) (bitsetを用いた二元体での簡約化の定数倍高速化)

- [抽象化行列](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Abstract_Matrix.hpp) (半環に対して行列積の演算を行うことができる)

- [疎行列の行列式](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Sparse_Matrix_Determinant.hpp) (black box in linear algebra の適用例)

## 線形漸化式
初期値と線形漸化式で与えられる数列の任意の項を求めるアルゴリズム。

- [Kitamasa法](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Kitamasa.hpp)

- [高速Kitamasa法](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Fast_Kitamasa.hpp) (Kitamasa法をFPSを用いて高速化)

- [Bostan-Moriのアルゴリズム](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Bostan_Mori.hpp)

線形漸化式で得られる数列の先頭の有限項が与えられたとき、それを与える階数最小の線形漸化式を求めることもできる。

- [Berlekamp-Masseyのアルゴリズム](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Berlekamp_Massey.hpp)

## 畳み込み
畳み込み(ここでは多項式の乗算)を行うアルゴリズム。

### 高速フーリエ変換(FFT)
2つの多項式の積は、それぞれを複素数上で離散フーリエ変換し、両者の各項の積を取ったものを逆離散フーリエ変換することで得られる。このとき離散フーリエ変換・逆離散フーリエ変換がボトルネックとなっており、次数が2冪のときにこれらを高速に行えるアルゴリズムとして高速フーリエ変換が知られている。

- [高速フーリエ変換(FFT)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/FFT.hpp)

### 数論変換(NTT)
NTT素数を、自身から1引いたものが(配列の長さより)十分大きい2冪で割り切れる素数とする。NTT素数をmodとした剰余環では1の2冪(十分大きい)乗根を取ることが出来るため、高速フーリエ変換を適用することができる。代表的なNTT素数として998244353がある。

- [数論変換(NTT)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/NTT.hpp) (NTT素数modにおける畳込み)

いくつかのNTT素数modを用意して、Garnerのアルゴリズムで復元することによって任意modで畳み込みを行うことができる。

- [任意mod数論変換(NTT)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Arbitrary_Mod_NTT.hpp) (任意modにおける畳込み)

### 多変数畳み込み
FFT(NTT)を用いることで、多変数多項式の積を次数が大きくなるところは切り捨てで求めることができる。    

- [多変数畳み込み](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Multivariate_Convolution.hpp) 

## 形式的冪級数(FPS)
形式的冪級数(項の数が有限とは限らない多項式)の基本的な計算を行うアルゴリズム。

- [形式的冪級数(FPS)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/FPS.hpp) (NTT素数modにおける形式的冪級数)

- [任意mod形式的冪級数(FPS)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Arbitrary_Mod_FPS.hpp) (任意modにおける形式的羃級数)

## 多項式
多項式補間や、与えられた点での評価を行うアルゴリズム。

- [Subproduct Tree](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Subproduct_Tree.hpp) (多項式の積についてのセグメント木)

- [ラグランジュ補間(1点)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Lagrange_Interpolation.hpp) (f(0),f(1),..,f(n-1)の値からある1点でのfの値を求める)

- [ラグランジュ補間(多項式)](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Polynomial_Interpolation.hpp) (多項式そのものを復元する)

- [多点評価](https://github.com/tokusakurai/Library/blob/main/Math-Algorithm/Multipoint_Evaluation.hpp) (多項式が与えられたときに多点での値を求める)
