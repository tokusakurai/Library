# 数学アルゴリズム

## ユークリッドの互除法

ユークリッド互除法を用いるアルゴリズム。

- [ユークリッドの互除法](Euclid.hpp) (gcd、lcm、extgcd、mod 逆数、floor sum、中国剰余定理、Garner のアルゴリズム)

- [ガウス整数環の GCD](Gaussian_Integer_GCD.hpp)

## 素数・約数

素数・約数に関するアルゴリズム。

- [素数・約数](Prime.hpp) (約数列挙、素因数分解、素数判定、エラトステネスの篩、素数え上げ)

- [高速素因数分解](Fast_Prime_Factorization.hpp)

## 剰余環における演算

有理整数環の剰余環 $\mathbb{Z}/n\mathbb{Z}$ における演算に関するアルゴリズム。

- [剰余環における演算](Factor_Ring.hpp) (累乗、オイラーの φ 関数、離散対数、位数、原始根)

- [原子根](Primitive_Root.hpp)

- [テトレーション](Tetration.hpp)

## mod-int 構造体

有理整数環の剰余体 $\mathbb{Z}/p\mathbb{Z}$ を構造体で表現したもので、加減乗除を扱うことができる。除算以外は剰余環 $\mathbb{Z}/n\mathbb{Z}$ でも扱うことができる。

- [mod-int 構造体](Mod_Int.hpp)

- [実行時入力 mod-int 構造体](Runtime_Mod_Int.hpp)

- [モンゴメリ乗算 mod-int 構造体 (64 ビット)](Montgomery_Mod_Int_64.hpp)

## 組み合わせ

前計算をすることによって、二項係数を効率的に求めることができる。

- [組み合わせ](Combination.hpp) (二項係数、第 2 種スターリング数、ベル数)

## 数列

各種数列のテーブルを計算するアルゴリズム。

- [スターリング数](Stirling_Number.hpp) (第 1 種スターリング数、第 2 種スターリング数のテーブル)

- [モンモール数](Montmort_Number.hpp) (完全順列の個数のテーブル)

- [分割数](Partition_Function.hpp) (分割数のテーブル)

## K 乗根

体において K 乗根を求めるアルゴリズム。

- [K 乗根 (整数)](Kth_Root_Integer.hpp) (非負整数の K 乗根以下の最小の整数を求める)

- [K 乗根 (mod)](Kth_Root_Mod.hpp) (素数 $p$ について $\mathbb{Z}/p\mathbb{Z}$ における K 乗根を求める)

## 2-SAT

リテラル数が 2 以下のクロージャーの積で表される論理式の充足可能性を判定するアルゴリズム。

- [2-SAT](Two_SAT.hpp)

## 行列

行列を用いた計算に関するアルゴリズム。加法と乗法の2つの二項演算を備えた集合が半環であるとき、行列積の演算を行うことができる。

- [行列](Matrix.hpp) (積、累乗、簡約化)

- [線形方程式](Linear_Equation.hpp)

- [二元体行列](F2_Matrix.hpp) (bitset を用いた二元体での簡約化の定数倍高速化)

- [二元体上の線形方程式](F2_Linear_Equation.hpp)

- [二元体ベクトル空間の基底](F2_basis.hpp) (ベクトル空間、及びその交差の基底計算)

- [抽象化行列](Abstract_Matrix.hpp) (半環に対して行列積の演算を行うことができる)

- [任意 mod 行列式](Arbitrary_Mod_Determinant.hpp) (素数とは限らない自然数 $m$ に対する $\mathbb{Z}/m\mathbb{Z}$ での行列式)

- [疎行列の行列式](Sparse_Matrix_Determinant.hpp) (black box in linear algebra の適用例)

- [特性多項式](Characteristic_Polynomial.hpp)

- [一次関数行列の行列式](Linear_Function_Matrix_Determinant.hpp)

## 線形漸化式

初期値と線形漸化式で与えられる数列の任意の項を求めるアルゴリズム。

- [Kitamasa 法](Kitamasa.hpp)

- [高速 Kitamasa 法](Fast_Kitamasa.hpp) (Kitamasa 法を FPS を用いて高速化)

- [Bostan-Mori のアルゴリズム](Bostan_Mori.hpp)

- [2 べき分割数の数え上げ](Power_of_Two_Partition.hpp) (非負整数を 2 べきの和に分割する場合の数を重み付きで求める)

- [線形回帰数列の各項列挙](Linear_Recursive_Sequence_Enumeration.hpp) (線形漸化式に従う初項 1 の数列を求める)

線形漸化式で得られる数列の先頭の有限項が与えられたとき、それを与える階数最小の線形漸化式を求めることもできる。

- [Berlekamp-Massey のアルゴリズム](Berlekamp_Massey.hpp)

## 畳み込み

畳み込み (ここでは多項式の乗算)を行うアルゴリズム。

### 高速フーリエ変換 (FFT)

2 つの多項式の積は、それぞれを複素数上で離散フーリエ変換し、両者の各項の積を取ったものを逆離散フーリエ変換することで得られる。このとき離散フーリエ変換・逆離散フーリエ変換がボトルネックとなっており、次数が 2 冪のときにこれらを高速に行えるアルゴリズムとして高速フーリエ変換が知られている。

- [高速フーリエ変換 (FFT)](Fast_Fourier_Transform.hpp)

### 数論変換 (NTT)

NTT 素数を、自身から 1 引いたものが (配列の長さより) 十分大きい 2 冪で割り切れる素数とする。NTT 素数 p を法とした有理整数環の剰余体 Z/pZ では 1 の 2 冪 (十分大きい) 乗根を取ることが出来るため、高速フーリエ変換を適用することができる。代表的な NTT 素数として 998244353 がある。

- [数論変換 (NTT)](Number_Theoretic_Transform.hpp) (NTT 素数 mod における畳込み)

いくつかの NTT 素数を用意して Garner のアルゴリズムで復元することによって、任意 mod で畳み込みを行うことができる。

- [任意 mod 数論変換 (NTT)](Arbitrary_Mod_Number_Theoretic_Transform.hpp) (任意 mod における畳込み)

- [高速フーリエ変換 (64 ビット符号付き整数)](Fast_Fourier_Transform_Integer.hpp) (結果が 64 ビット符号付き整数に収まる場合の畳み込み)

- [オンライン畳み込み](Relaxed_Convolution.hpp) (項が逐次的に与えられるときの畳み込み)

### 多変数畳み込み

FFT (NTT) を用いることで、多変数多項式の積を次数が大きくなるところは切り捨てで求めることができる。

- [多変数畳み込み](Multivariate_Convolution.hpp)

## 疎な多項式のべき乗

疎な多項式をべき乗したときの各項の係数を求める。

- [疎な多項式のべき乗](Sparse_Polynomial_Power.hpp)

## 高速ゼータ・メビウス・アダマール変換

長さが 2 冪であるような配列に対する各種の変換。応用として添字 AND・OR・XOR 畳み込みや subset 畳み込みがある。

- [高速ゼータ・メビウス・アダマール変換](Zeta_Mobius_Hadamard.hpp)

- [ビット演算による添字畳み込み](Bitwise_Convolution.hpp) (添字 AND・OR・XOR 畳み込み、subset 畳み込み)

## 約数系ゼータ・メビウス変換

約数系集合に対するゼータ変換・メビウス変換。応用として添字 GCD・LCM 畳み込みがある。

- [約数系ゼータ・メビウス変換](Divisors_Zeta_Mobius.hpp)

- [添字 GCD・LCM 畳み込み](GCD_LCM_Convolution.hpp)

## 形式的冪級数 (FPS)

形式的冪級数 (項の数が有限とは限らない多項式) の基本的な計算を行うアルゴリズム。

- [形式的冪級数 (FPS)](Formal_Power_Series.hpp) (NTT 素数 mod における形式的冪級数)

- [任意 mod 形式的冪級数 (FPS)](Arbitrary_Mod_Formal_Power_Series.hpp) (任意 mod における形式的羃級数)

## 多項式

多項式補間や、与えられた点での評価を行うアルゴリズム。

- [Subproduct Tree](Subproduct_Tree.hpp) (多項式の積についてのセグメント木)

- [ラグランジュ補間 (1 点)](Single_Point_Interpolation.hpp) (連続した多点での値から 1 点での値を復元する)

- [ラグランジュ補間 (多点)](Multipoint_Interpolation.hpp) (連続した多点での値から連続した多点での値を復元する)

- [ラグランジュ補間 (多項式)](Polynomial_Interpolation.hpp) (多点での値から多項式そのものを復元する)

- [多点評価](Multipoint_Evaluation.hpp) (多項式が与えられたときに多点での値を求める)

- [多点評価 (幾何級数)](Multipoint_Evaluation_Geometric_Series.hpp) (評価点が幾何級数のときの多点評価)

## 多項式とべき乗の積和

- [多項式とべき乗の積和](Polynomial_R_Power_Sum.hpp) ($\sum_{i=0}^{n-1} i^kr^i$, $\sum_{i=0}^{\infty} i^kr^i$)

## 階段状のグリッドにおける最短経路数え上げ

- [階段状のグリッドにおける最短経路数え上げ](Step_Grid_Path_Count.hpp)
