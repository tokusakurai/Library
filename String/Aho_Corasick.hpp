#pragma once

// Aho-Corasick 法 (複数文字列についてパターンマッチするオートマトンを構築する)
// 計算量 構築 : O(Σ[i]|S_i|)、遷移 : O(1)

// 概要
// 文字列 S_1,...,S_n のトライ木に failure link を加える。
// trie の各頂点に相当する文字列 X について、X_i の suffix で、trie に該当する頂点があるものの中で最長のものを Y_i とする。
// failure link は X_i から Y_i への辺に相当する。
// T に 1 文字加えた際の T の suffix で、trie に該当する頂点があり、最長のものに該当する頂点に移動する。

// verified with
// https://yukicoder.me/problems/no/430
// https://yukicoder.me/problems/no/1269
// https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_h
// https://atcoder.jp/contests/abc268/tasks/abc268_h
// https://atcoder.jp/contests/abc362/tasks/abc362_g

#include <bits/stdc++.h>
using namespace std;

#include "../String/Trie.hpp"

template <int char_size, char base>
struct Aho_Corasick : Trie<char_size + 1, base> {
    const int FAIL = char_size;
    vector<int> correct; // S_i が接尾辞となるような i の個数 (最大でも O(√Σ|S_i|))
    vector<int> suffix;  // S_i が真の接尾辞となるような、最長の S_i に対応する頂点へのリンク

    // heavy : S_i が接尾辞となるような i を全て持つかどうか (持つ場合は accept に保管される)
    void build() {
        correct.resize(this->size(), 0);
        suffix.resize(this->size(), -1);
        for (int i = 0; i < (int)this->size(); i++) correct[i] = (this->nodes[i].accept).size();
        queue<int> que;
        for (int i = 0; i <= char_size; i++) {
            if (this->nodes[0].next[i] != -1) {
                int v = this->nodes[0].next[i];
                this->nodes[v].next[FAIL] = 0;
                suffix[v] = 0;
                que.push(v);
            } else {
                this->nodes[0].next[i] = 0;
            }
        }
        while (!que.empty()) {
            auto &now = this->nodes[que.front()];
            int fail = now.next[FAIL];
            correct[que.front()] += correct[fail];
            que.pop();
            for (int i = 0; i < char_size; i++) {
                if (now.next[i] != -1) {
                    int u = this->nodes[fail].next[i];
                    int v = now.next[i];
                    this->nodes[v].next[FAIL] = u;
                    if (!this->nodes[u].accept.empty()) {
                        suffix[v] = u;
                    } else {
                        suffix[v] = suffix[u];
                    }
                    que.push(v);
                } else {
                    now.next[i] = this->nodes[fail].next[i];
                }
            }
        }
    }

    // 頂点 v の接尾辞となる S_i を列挙する (S_i が相異なる場合 O(√∑|S_i|) 個)
    vector<int> enumerate_suffix(int v) const {
        vector<int> ret;
        while (v != -1) {
            ret.insert(end(ret), begin(this->nodes[v].accept), end(this->nodes[v].accept));
            v = suffix[v];
        }
        return ret;
    }

    // now から s に沿って進めたときのマッチしたパターンの id と回数の組 (build 時に heavy = true にする必要あり)
    vector<int> match(int now, const string &s) const {
        vector<int> ret(this->count(), 0);
        for (auto &c : s) {
            now = this->nodes[now].next[c - base];
            for (auto &u : enumerate_suffix(now)) ret[u]++;
        }
        return ret;
    }

    vector<int> match(const string &s) const { return match(0, s); }

    // now から c の方向に進めたときのマッチしたパターン数と移動先のノードの組
    pair<long long, int> move(int now, const char &c) const {
        now = this->nodes[now].next[c - base];
        return make_pair(correct[now], now);
    }

    pair<long long, int> move(const char &c) const { return move(0, c); }

    pair<long long, int> move(int now, const string &s) const {
        long long sum = 0;
        for (auto &c : s) {
            pair<long long, int> p = move(now, c);
            sum += p.first, now = p.second;
        }
        return make_pair(sum, now);
    }

    pair<long long, int> move(const string &s) const { return move(0, s); }
};
