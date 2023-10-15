
// 接尾辞配列、高さ配列
// 計算量 接尾辞配列構築：O(|S|)、二分探索：O(|T|log(|S|))、高さ配列構築：O(|S|)

// 接尾辞配列 (suffix array)：文字列の全ての接尾辞を辞書順にソートしたものを記録する (実際には何文字目からの接尾辞かを記録する)。
// 高さ配列 (longest common prefix array)：接尾辞配列の隣同士で接頭辞が何文字一致しているかを記録する。

// 概要
// sa[i] := 辞書順 i 番目 (0-indexed) の接尾辞のスタート地点 (0-indexed)
// rank[i] := i 文字目 (0-indexed) から始まる接尾辞は辞書順何番目か (0-indexed)
// k 文字分の sa 配列を用いることで 2k 文字分の sa 配列を構築できる。
// lcp[i] := S の rank[i] 文字目から始まる部分列と rank[i+1] 文字目から始まる部分列の最長共通接頭辞のサイズ。

// SA-IS の概要
// 1. 文字列の各文字を L 型と S 型に分類する。
// 2. LMS(left most S) をビンに入れて、induced sort をする。(結果、LMS 部分文字列は昇順に並ぶ)
// 3. LMS から始まる suffix をソートするために、lms 部分文字列の rank を順に並べた文字列の sa を再帰的に求める。 (lms の個数は n/2 個以下)
// 4. LMS を、suffix の順にビンに入れて induced sort する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja
// https://atcoder.jp/contests/practice2/tasks/practice2_i
// https://judge.yosupo.jp/problem/suffixarray
// https://judge.yosupo.jp/problem/number_of_substrings

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T = string>
struct Suffix_Array {
    const T s;
    const int n;
    vector<int> SA, RANK;

    Suffix_Array(const T &s) : s(s), n(s.size()) {
        int n = s.size();
        int mi = *min_element(begin(s), end(s)), ma = *max_element(begin(s), end(s));
        vector<int> a(n);
        if (ma - mi >= n) {
            a = compress(s);
        } else {
            for (int i = 0; i < n; i++) a[i] = s[i] - mi;
        }
        SA = SAIS(a);
        RANK.resize(n);
        for (int i = 0; i < n; i++) RANK[SA[i]] = i;
    }

    vector<int> compress(const T &a) {
        int n = a.size();
        T v = a;
        sort(begin(v), end(v));
        v.erase(unique(begin(v), end(v)), end(v));
        vector<int> ret(n);
        for (int i = 0; i < n; i++) ret[i] = std::lower_bound(begin(v), end(v), a[i]) - begin(v);
        return ret;
    }

    vector<int> SAIS(const vector<int> &a) {
        int n = a.size();
        vector<int> ls_type(n); // 0：s 型、1：l 型
        ls_type[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            ls_type[i] = ls_type[i + 1];
            if (a[i] < a[i + 1]) ls_type[i] = 0;
            if (a[i] > a[i + 1]) ls_type[i] = 1;
        }
        vector<int> lms, lms_id(n, -1);
        for (int i = 1; i < n; i++) {
            if (ls_type[i - 1] == 1 && ls_type[i] == 0) {
                lms_id[i] = lms.size();
                lms.push_back(i);
            }
        }
        int m = lms.size();
        int ma = *max_element(begin(a), end(a));
        vector<int> l(ma + 1, 0), r(ma + 1, 0);
        for (int i = 0; i < n; i++) r[a[i]]++;
        for (int i = 0; i < ma; i++) r[i + 1] += r[i];
        for (int i = 0; i < ma; i++) l[i + 1] = r[i];
        if (m == 0) {
            vector<int> sa(n);
            for (int i = n - 1; i >= 0 && ls_type[i] == 1; i--) {
                int e = a[i];
                sa[l[e]++] = i;
            }
            for (int i = 0; i < n && ls_type[i] == 0; i++) {
                int e = a[i];
                sa[l[e]++] = i;
            }
            return sa;
        }

        auto induced_sort = [&](vector<int> &sa) {
            auto ml = l, mr = r;
            sa[ml[a[n - 1]]++] = n - 1;
            for (int i = 0; i < n; i++) {
                int e = sa[i];
                if (e > 0 && ls_type[e - 1] == 1) sa[ml[a[e - 1]]++] = e - 1;
            }
            for (int i = n - 1; i >= 0; i--) {
                int e = sa[i];
                if (e > 0 && ls_type[e - 1] == 0) sa[--mr[a[e - 1]]] = e - 1;
            }
        };

        vector<int> sa(n, -1);
        for (int i = m - 1; i >= 0; i--) {
            int e = lms[i];
            sa[--r[a[e]]] = e;
        }
        for (auto &e : lms) r[a[e]]++;
        induced_sort(sa);
        vector<int> sa_lms;
        sa_lms.reserve(m);
        for (auto &e : sa) {
            if (lms_id[e] != -1) sa_lms.push_back(lms_id[e]);
        }

        // a[lms[i]:lms[i+1]] と a[lms[j]:lms[j+1]] の一致判定
        auto same = [&](int i, int j) {
            if (i == m - 1 || j == m - 1) return false;
            if (lms[i + 1] - lms[i] != lms[j + 1] - lms[j]) return false;
            int d = lms[i + 1] - lms[i];
            for (int k = 0; k <= d; k++) {
                if (a[lms[i] + k] != a[lms[j] + k]) return false;
            }
            return true;
        };

        vector<int> rank_lms(m);
        rank_lms[sa_lms[0]] = 0;
        for (int i = 1; i < m; i++) {
            rank_lms[sa_lms[i]] = rank_lms[sa_lms[i - 1]];
            if (!same(sa_lms[i - 1], sa_lms[i])) rank_lms[sa_lms[i]]++;
        }
        vector<int> b(m);
        for (int i = 0; i < m; i++) {
            int e = lms[i];
            b[i] = rank_lms[lms_id[e]];
        }
        sa_lms = SAIS(b);
        fill(begin(sa), end(sa), -1);
        for (auto &e : lms) r[a[e]]--;
        for (auto &e : sa_lms) sa[r[a[lms[e]]]++] = lms[e];
        induced_sort(sa);
        return sa;
    }

    int operator[](int i) const { return SA[i]; }

    int rank(int i) const { return RANK[i]; }

    int size() const { return n; }

    bool compare_substr(const T &t, int si = 0, int ti = 0) const {
        int m = t.size();
        while (si < n && ti < m) {
            if (s[si] != t[ti]) return s[si] < t[ti];
            si++, ti++;
        }
        return si == n && ti < m;
    }

    // 辞書順で t 以降となるもので最初の接尾辞
    int lower_bound(const T &t) const {
        int l = -1, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            (compare_substr(t, SA[m]) ? l : r) = m;
        }
        return r;
    }

    int upper_bound(T t) const {
        t.back()++;
        return lower_bound(t);
    }
};

template <typename T = string>
struct Longest_Common_Prefix_Array {
    vector<int> lcp;
    const Suffix_Array<T> sa;
    const int n;

    Longest_Common_Prefix_Array(const Suffix_Array<T> &sa) : sa(sa), n(sa.size()) {
        lcp.resize(n - 1);
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (sa.rank(i) + 1 < n) {
                int j = sa[sa.rank(i) + 1];
                while (max(i, j) + h < n && sa.s[i + h] == sa.s[j + h]) h++;
                lcp[sa.rank(i)] = h;
                if (h > 0) h--;
            }
        }
    }

    int operator[](int i) const { return lcp[i]; }
};
