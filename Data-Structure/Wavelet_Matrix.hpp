#pragma once

// ウェーブレット行列
// 計算量 構築：O(n log(m))、rank・access・range_freq：O(log(m))、select：O(log(m)^2) (m は配列の要素の最大値)
// 空間計算量 O(n)

// 概要
// ビットを上から順番に安定ソートすることで構築する。
// 各ビットについて、64 個ずつのブロックに分けることで効率よくデータを保持することで、静的な配列について様々なクエリを扱える。

// verified with
// https://judge.yosupo.jp/problem/range_kth_smallest
// https://judge.yosupo.jp/problem/static_range_frequency

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Wavelet_Matrix {
    vector<vector<unsigned long long>> B; // 各ビットの各ブロックを 64 ビット符号なし整数で表現
    vector<vector<int>> S;                // 各ビットのブロックの popcount の累積和
    vector<int> c;                        // 各 bit の 0 の総数
    vector<unsigned long long> mask;
    const int n, m;
    int h;

    Wavelet_Matrix(vector<T> a) : n(a.size()), m((n >> 6) + 1) {
        T M = (n == 0 ? 0 : *max_element(begin(a), end(a)));
        h = 1;
        while (M >> h) h++;
        mask.assign(64, 0);
        for (int i = 0; i < 63; i++) mask[i + 1] = mask[i] | (1ULL << i);
        B.assign(h, vector<unsigned long long>(m, 0));
        S.assign(h, vector<int>(m + 1, 0));
        c.assign(h, 0);
        for (int i = h - 1; i >= 0; i--) {
            vector<T> b;
            int k = 0;
            for (int j = 0; j < n; j++) {
                if ((a[j] >> i) & 1) {
                    B[i][j >> 6] |= 1ULL << (j & 63);
                    b.push_back(a[j]);
                } else {
                    a[k++] = a[j];
                }
            }
            c[i] = k;
            for (T e : b) a[k++] = e;
            for (int j = 0; j < m; j++) S[i][j + 1] = S[i][j] + __builtin_popcountll(B[i][j]);
        }
    }

    // [0,r) に含まれる i ビット目が bit (0 か 1) であるものの個数
    int rank_01(int i, int r, int bit) const {
        int res = S[i][r >> 6] + __builtin_popcountll(B[i][r >> 6] & mask[r & 63]);
        return bit ? res : r - res;
    }

    // [l,r) に含まれる x の個数
    int rank(int l, int r, const T &x) const {
        for (int i = h - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                l = c[i] + rank_01(i, l, 1), r = c[i] + rank_01(i, r, 1);
            } else {
                l = rank_01(i, l, 0), r = rank_01(i, r, 0);
            }
        }
        return r - l;
    }

    // a[k]
    T access(int k) const {
        assert(k >= 0 && k < n);
        T ret = 0;
        for (int i = h - 1; i >= 0; i--) {
            if (B[i][k >> 6] & (1ULL << (k & 63))) {
                ret |= T(1) << i;
                k = c[i] + rank_01(i, k, 1);
            } else {
                k = rank_01(i, k, 0);
            }
        }
        return ret;
    }

    T operator[](int k) const { return access(k); }

    // k 番目 (0-indexed) の i ビット目が bit (0 か 1) であるものの位置
    int select_01(int i, int k, int bit) const {
        int L = 0, R = m + 1;
        while (R - L > 1) {
            int M = (L + R) / 2, t = S[i][M];
            if (!bit) t = (M << 6) - t;
            (t <= k ? L : R) = M;
        }
        if (L == m) return -1;
        int s = (bit ? S[i][L] : (L << 6) - S[i][L]);
        int l = 0, r = 64;
        while (r - l > 1) {
            int M = (l + r) / 2, t = __builtin_popcountll(B[i][L] & mask[M]);
            if (!bit) t = M - t;
            (s + t <= k ? l : r) = M;
        }
        return ((L << 6) + l < n ? (L << 6) + l : -1);
    }

    // k 番目 (0-indexed) の x の位置
    int select(int k, const T &x) const {
        int l = 0, r = n;
        for (int i = h - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                l = c[i] + rank_01(i, l, 1), r = c[i] + rank_01(i, r, 1);
            } else {
                l = rank_01(i, l, 0), r = rank_01(i, r, 0);
            }
        }
        if (r - l <= k) return -1;
        int p = l + k;
        for (int i = 0; i < h; i++) {
            if ((x >> i) & 1) {
                p = select_01(i, p - c[i], 1);
            } else {
                p = select_01(i, p, 0);
            }
        }
        return p;
    }

    // [l,r) で upper 未満のものの個数
    int range_freq(int l, int r, const T &upper) const {
        if (upper > mask[h]) return r - l;
        int ret = 0;
        for (int i = h - 1; i >= 0; i--) {
            if ((upper >> i) & 1) {
                ret += rank_01(i, r, 0) - rank_01(i, l, 0);
                l = c[i] + rank_01(i, l, 1), r = c[i] + rank_01(i, r, 1);
            } else {
                l = rank_01(i, l, 0), r = rank_01(i, r, 0);
            }
        }
        return ret;
    }

    // [l,r) で lower 以上 upper 未満のものの個数
    int range_freq(int l, int r, const T &lower, const T &upper) const {
        if (lower >= upper) return 0;
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    // [l,r) で小さい方から k 番目 (0-indexed) の値
    T quantile(int l, int r, int k) const {
        assert(k >= 0 && k < r - l);
        T ret = 0;
        for (int i = h - 1; i >= 0; i--) {
            int nl = rank_01(i, l, 0), nr = rank_01(i, r, 0);
            if (k < nr - nl) {
                l = nl, r = nr;
            } else {
                ret |= T(1) << i;
                k -= nr - nl;
                l = c[i] + l - nl, r = c[i] + r - nr;
            }
        }
        return ret;
    }
};
