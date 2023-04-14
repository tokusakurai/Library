template<class Monoid>
class FoldableQueue {
    using M = typename Monoid::V;
    vector<M> head, tail, head_sum, tail_sum;

    void scan_head() {
        head_sum.resize(1);
        head_sum.reserve(head.size() + 1);
        partial_sum(begin(head), end(head), back_inserter(head_sum),
                    [](M l, M r){ return Monoid::merge(l, r); });
    }

    public:
    FoldableQueue() : head(), tail(), head_sum(1, Monoid::id), tail_sum(1, Monoid::id) {}

    FoldableQueue(const vector<M> &v) : head(v), tail(), tail_sum(1, Monoid::id) {
        reverse(begin(head), end(head));
    }

    M fold() const {
        return Monoid::merge(tail_sum.back(), head_sum.back());
    }

    M front() const {
        assert(!empty());
        return head.back();
    }

    M back() const {
        assert(!empty());
        if(tail.empty()) {
            return head.at(0);
        } else {
            return tail.back();
        }
    }

    void push(const M &x) {
        if(head.empty()) {
            head.push_back(x);
            scan_head();
        } else {
            tail.push_back(x);
            tail_sum.emplace_back(Monoid::merge(x, tail_sum.back()));
        }
    }

    template <class... Args>
    decltype(auto) emplace(Args&&... args) {
        if(head.empty()) {
            auto res = head.emplace_back(std::forward<Args>(args)...);
            scan_head();
            return res;
        } else {
            auto res = tail.emplace_back(std::forward<Args>(args)...);
            tail_sum.emplace_back(Monoid::merge(tail.back(), tail_sum.back()));
            return res;
        }
    }

    void pop() {
        assert(!empty());
        head.pop_back();
        head_sum.pop_back();
        if(head.empty()) {
            swap(head, tail);
            swap(head_sum, tail_sum);
            reverse(begin(head), end(head));
            scan_head();
            tail_sum.resize(1);
        }
    }

    size_t size() const {
        return head.size() + tail.size();
    }

    bool empty() const {
        return size() == 0;
    }
};