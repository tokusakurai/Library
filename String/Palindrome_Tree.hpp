#pragma once

// 回文木
// 計算量 O(|S|)

// 概要
// 文字列 S に現れる奇数長回文と偶数長回文それぞれについて、中心より右側の部分で Trie 木を作る。
// 各回文 P について、P の接尾辞回文で最長のもの (P を除く) に有向辺 (suffix link) を貼る。
// 文字列を前から 1 文字ずつ追加していって構成することを考える。
// S の i 文字目を末尾とする最長回文を P_i とすると、i 文字目の追加で新しく発生しうる回文は P_i のみである。
// P_i を計算するには、P_{i-1} から始めて、回文の前の文字が S_i になるまで suffix_link を辿ればよい。
// P_i の suffix_link を計算するには、P_i の先頭・末尾を除いた回文から始めて、回文の前の文字が S_i になるまで suffix_link を辿ればよい。
// 計算量はならしで O(|S|) になる。

// verified with
// https://contest.ucup.ac/contest/1440/problem/7876
// https://judge.yosupo.jp/problem/eertree

#include <bits/stdc++.h>
using namespace std;

template <int char_size, char base>
struct Palindrome_Tree {
    struct Node {
        array<int, char_size> next;
        int len, count, suffix_link;

        Node(int len, int suffix_link) : len(len), count(0), suffix_link(suffix_link) { fill(begin(next), end(next), -1); }
    };

    vector<Node> nodes;
    string s;
    int n;
    vector<int> longest_palindromes; // i 文字目を末尾とする最長回文の index を格納

    Palindrome_Tree() : n(0) {
        nodes.emplace_back(-1, -1); // 奇数長の空回文
        nodes.emplace_back(0, 0);   // 偶数長の空回文
    }

    Palindrome_Tree(string s) : Palindrome_Tree() {
        for (char c : s) push_back(c);
        build_frequency();
    }

    // 回文の種類数
    int count() { return (int)nodes.size() - 2; }

    // r-1 文字目を末尾とする palindrome に c を追加したときの suffix_link
    int suffix_palindrome(int palindrome, char c, int r) {
        while (palindrome != -1) {
            const Node &node = nodes[palindrome];
            if (node.len < r && s[r - 1 - node.len] == c) return palindrome;
            palindrome = node.suffix_link;
        }
        return -1;
    }

    void push_back(char c) {
        s.push_back(c);
        n++;
        int current_palindrome = (n == 1 ? 0 : longest_palindromes.back());
        int p = suffix_palindrome(current_palindrome, c, n - 1);
        if (nodes[p].next[c - base] == -1) {
            nodes[p].next[c - base] = (int)nodes.size();
            int q = suffix_palindrome(nodes[p].suffix_link, c, n - 1);
            if (q != -1) {
                nodes.emplace_back(nodes[p].len + 2, nodes[q].next[c - base]);
            } else {
                nodes.emplace_back(1, 1);
            }
        }
        int palindrome = nodes[p].next[c - base];
        nodes[palindrome].count++;
        longest_palindromes.push_back(palindrome);
    }

    void build_frequency() {
        for (int i = (int)nodes.size() - 1; i > 0; i--) {
            int suffix = nodes[i].suffix_link;
            nodes[suffix].count += nodes[i].count;
        }
    }
};
