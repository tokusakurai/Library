
// Binary Trie（非負整数値の Trie 木）
// 計算量 挿入・削除・検索・最大（最小）値・k 番目の最小値・x 未満の個数 : O(b)（b は要素の 2 進数表記に必要な桁数）

// 概要
// 非負整数を 2 進数表記で上の桁から見ることで文字列のようにすることで Trie 木を構築する。

// verified with
// https://judge.yosupo.jp/problem/set_xor_min
// https://codeforces.com/contest/1614/problem/E
// https://atcoder.jp/contests/abc234/tasks/abc234_d

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, int MAX_LOG>
struct Binary_Trie {
    struct Node {
        array<int, 2> next;
        int count;

        Node() : next{-1, -1}, count(0) {}
    };

    vector<Node> nodes;

    Binary_Trie() { nodes.emplace_back(); }

    void insert(const T &x) {
        int now = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (x >> i) & 1;
            int next = nodes[now].next[t];
            if (next == -1) {
                next = nodes.size();
                nodes[now].next[t] = next;
                nodes.emplace_back();
            }
            nodes[now].count++;
            now = next;
        }
        nodes[now].count++;
    }

    void erase(const T &x) {
        if (!count(x)) return;
        int now = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (x >> i) & 1;
            nodes[now].count--;
            now = nodes[now].next[t];
        }
        nodes[now].count--;
    }

    int find(const T &x) const {
        int now = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (x >> i) & 1;
            now = nodes[now].next[t];
            if (now == -1) return -1;
        }
        return now;
    }

    int count(const T &x) const {
        int p = find(x);
        return p == -1 ? 0 : nodes[p].count;
    }

    T max_element(const T &xor_val = 0) const {
        int now = 0;
        T ret = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (xor_val >> i) & 1;
            int l = nodes[now].next[t], r = nodes[now].next[t ^ 1];
            if (r == -1 || nodes[r].count == 0) {
                now = l;
                ret |= T(t) << i;
            } else {
                now = r;
                ret |= T(t ^ 1) << i;
            }
        }
        return ret;
    }

    T min_element(const T &xor_val = 0) const {
        int now = 0;
        T ret = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (xor_val >> i) & 1;
            int l = nodes[now].next[t], r = nodes[now].next[t ^ 1];
            if (l == -1 || nodes[l].count == 0) {
                now = r;
                ret |= T(t ^ 1) << i;
            } else {
                now = l;
                ret |= T(t) << i;
            }
        }
        return ret;
    }

    T kth_element(int k, const T &xor_val = 0) const { // k 番目 (0-indexed)
        int now = 0;
        T ret = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (xor_val >> i) & 1;
            int l = nodes[now].next[t], r = nodes[now].next[t ^ 1];
            if (l == -1 || nodes[l].count <= k) {
                now = r;
                k -= (l == -1 ? 0 : nodes[l].count);
                ret |= T(t ^ 1) << i;
            } else {
                now = l;
                ret |= T(t) << i;
            }
        }
        return ret;
    }

    int count_less(const T &x, const T &xor_val = 0) const { // x 未満の個数
        int now = 0;
        int ret = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int t = (xor_val >> i) & 1, s = (x >> i) & 1;
            int l = nodes[now].next[t], r = nodes[now].next[t ^ 1];
            if (s != t && l != -1) ret += nodes[l].count;
            now = nodes[now].next[s];
            if (now == -1) break;
        }
        return ret;
    }
};
