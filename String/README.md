# 文字列

## Z algorithm
文字列の各接尾辞が、元の文字列と何文字の接頭辞を共通に持っているかを求めるアルゴリズム。

- [Z algorithm](https://github.com/tokusakurai/Library/blob/main/String/Z_Algorithm.hpp)

## Manachar
文字列の各文字を中心とした最長回分の半径を求めるアルゴリズム。

- [Manachar](https://github.com/tokusakurai/Library/blob/main/String/Manachar.hpp)

## MP法・KMP法
文字列のすべての接頭辞について、その共通する最長の接頭辞・接尾辞を求めるアルゴリズム。

- [MP法・KMP法](https://github.com/tokusakurai/Library/blob/main/String/KMP.hpp)

## トライ木
文字列集合に対してトライ木(各頂点は1文字を表していて、根から1文字ずつたどることで文字列が表現される木)を構築する。

- [トライ木](https://github.com/tokusakurai/Library/blob/main/String/Trie.hpp)

- [Aho-Corasick法](https://github.com/tokusakurai/Library/blob/main/String/Aho_Corasick.hpp) (トライ木に、パターンが存在しない場合の後退辺を新たに付け加えたもの)

## ローリングハッシュ
文字列や配列をハッシュ値に置き換えるアルゴリズム。

- [ローリングハッシュ](https://github.com/tokusakurai/Library/blob/main/String/Rolling_Hash.hpp)

## 接尾辞配列
文字列の全ての接尾辞を辞書順にソートしたものを記録するアルゴリズム。

- [接尾辞配列・高さ配列](https://github.com/tokusakurai/Library/blob/main/String/Suffix_Array.hpp)
