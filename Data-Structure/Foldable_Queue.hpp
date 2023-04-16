
// Sliding Window Aggrication (SWAG)
// 計算量: push,pop amortized O(1), それ以外 O(1)

// 概要
// 2本の stack で queue をシミュレートできることを利用して queue に入っているモノイドの和を計算する。
// 具体的には2本のstackそれぞれの累積和を保持している。

// verified with
// https://judge.yosupo.jp/problem/queue_operate_all_composite

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<class Monoid>
class Foldable_Queue {
    using M = typename Monoid::V;

    struct Node {
        M value;
        M sum;
        Node() : value(Monoid::id), sum(Monoid::id) {}
        Node(M v) : value(v), sum(v) {}
        Node(M v, M s) : value(v), sum(s) {}
    };
    
    vector<Node> head, tail;

    void scan_head() {
        for(size_t i = 1; i < head.size(); i++) {
            head[i].sum = Monoid::merge(head[i - 1].sum, head[i].value);
        }
    }

    public:
    Foldable_Queue() : head(1), tail(1) {}

    // 中に入っている要素の和を計算する。
    // 非可換のモノイドでは右のほうが先頭側であることに注意 (back <-> front)
    M fold() const {
        if(tail.size() == 1) return head.back().sum;
        else if(head.size() == 1) return tail.back().sum; 
        else return Monoid::merge(tail.back().sum, head.back().sum);
    }

    M front() const {
        assert(!empty());
        if(head.size() == 1) return tail.at(1).value;
        return head.back().value;
    }

    M back() const {
        assert(!empty());
        if(tail.size() == 1) {
            return head.at(1).value;
        } else {
            return tail.back().value;
        }
    }

    void push(const M &x) {
        if(head.size() == 1) {
            head.emplace_back(x);
            scan_head();
        } else {
            tail.emplace_back(x, Monoid::merge(x, tail.back().sum));
        }
    }

    template <class... Args>
    decltype(auto) emplace(Args&&... args) {
        if(head.size() == 1) {
            auto res = head.emplace_back(typename Monoid::V(std::forward<Args>(args)...));
            scan_head();
            return res;
        } else {
            auto val = typename Monoid::V(std::forward<Args>(args)...);
            auto res = tail.emplace_back(val, Monoid::merge(val, tail.back().sum));
            return res;
        }
    }

    void pop() {
        assert(!empty());
        head.pop_back();
        if(head.size() == 1) {
            swap(head, tail);
            reverse(begin(head) + 1, end(head));
            scan_head();
        }
    }

    size_t size() const {
        return head.size() + tail.size() - 2;
    }

    bool empty() const {
        return size() == 0;
    }
};