#pragma once

// トライ木
// 計算量 文字列追加・検索：O(|S|)

// 概要
// トライ木の各頂点は、次に各文字を使った際の行き先の情報を記録する。
// 追加：文字列を前から見て、トライ木を根から降りていく。該当する頂点がなくなったら新しい頂点を作る。
// 検索：文字列を前から見て、トライ木を根から降りていく。

// verified with
// https://atcoder.jp/contests/tenka1-2016-final/tasks/tenka1_2016_final_c

#include <bits/stdc++.h>
using namespace std;

template <int char_size, char base>
struct Trie {
    struct Node {
        array<int, char_size> next;
        vector<int> accept;
        int count; // 子以下に追加された文字列の数

        Node() : count(0) { fill(begin(next), end(next), -1); }
    };

    vector<Node> nodes;

    Trie() { nodes.emplace_back(); }

    void insert(const string &s, int id) {
        int now = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int t = s[i] - base;
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
        nodes[now].accept.push_back(id);
    }

    void insert(const string &s) { insert(s, nodes[0].count); }

    int find(const string &s) const {
        int now = 0;
        for (int i = 0; i < s.size(); i++) {
            int t = s[i] - base;
            now = nodes[now].next[t];
            if (now == -1) return -1;
        }
        return now;
    }

    int count(const string &s) const {
        int p = find(s);
        return p == -1 ? 0 : nodes[p].count;
    }
};
