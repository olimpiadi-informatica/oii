#include <limits>
#include <numeric>
#include <vector>
#include <cassert>

using namespace std;

template <typename T> class pairing_heap {
  protected:
    T value;
    pairing_heap<T>* next;
    pairing_heap<T>* prev;
    pairing_heap<T>* child;

    static pairing_heap<T>* merge_pairs(pairing_heap<T>* a) {
        if(!a)
            return nullptr;
        if(!a->next)
            return a;
        pairing_heap<T>* other = a->next->next;
        pairing_heap<T>* b = a->next;
        a->next = b->next = nullptr;
        b->prev = nullptr;
        if(other)
            other->prev = nullptr;
        return merge(merge(a, b), merge_pairs(other));
    }

  public:
    pairing_heap(const T& _value = T(), pairing_heap<T>* _next = nullptr,
                 pairing_heap<T>* _prev = nullptr,
                 pairing_heap<T>* _child = nullptr) {
        value = _value;
        next = _next;
        prev = _prev;
        child = _child;
    }

    static const T& top(const pairing_heap<T>* a) {
        assert(a);
        return a->value;
    }

    static pairing_heap<T>* merge(pairing_heap<T>* a, pairing_heap<T>* b) {
        if(!a)
            return b;
        if(!b)
            return a;
        pairing_heap<T>* upper = b;
        pairing_heap<T>* lower = a;
        if(top(a) < top(b)) {
            upper = a;
            lower = b;
        }
        assert(!lower->next);
        lower->next = upper->child;
        lower->prev = upper;
        if(upper->child) {
            upper->child->prev = lower;
        }
        upper->child = lower;
        return upper;
    }

    static pairing_heap<T>* insert(pairing_heap<T>* a, const T& v) {
        return merge(a, new pairing_heap<T>(v));
    }

    static pairing_heap<T>* remove_top(pairing_heap<T>* a) {
        if(!a)
            return nullptr;
        pairing_heap<T>* child = a->child;
        if(child)
            child->prev = nullptr;
        delete a;
        return merge_pairs(child);
    }

    static pairing_heap<T>* remove_top_nodelete(pairing_heap<T>* a) {
        if(!a)
            return nullptr;
        pairing_heap<T>* child = a->child;
        if(child)
            child->prev = nullptr;
        a->next = a->prev = a->child = nullptr;
        return merge_pairs(child);
    }

    static pairing_heap<T>* decrease_key(pairing_heap<T>* root,
                                         pairing_heap<T>* node,
                                         const T& new_value) {
        assert(!(top(node) < new_value));
        node->value = new_value;
        if(!node->prev) {
            assert(node == root);
            return node;
        }
        if(node->prev->child == node) {
            if(!(top(node) < top(node->prev)))
                return root;
            node->prev->child = node->next;
        } else {
            node->prev->next = node->next;
        }
        if(node->next)
            node->next->prev = node->prev;
        node->prev = nullptr;
        node->next = nullptr;
        return merge(node, root);
    }
};

using i64 = long long int;
using ii = pair<i64, i64>;
using PHi = pairing_heap<i64>;

long long costruisci(int _n, int _m, vector<long long>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    size_t n = _n;
    size_t m = _m;
    vector<vector<ii>> children(n);
    vector<bool> visited(n);
    vector<PHi> phb;
    phb.reserve(n);
    for(size_t i = 0; i < m; i++) {
        children[a[i]].push_back(make_pair(c[i], b[i]));
    }
    PHi* ph = nullptr;
    for(size_t i = 0; i < n; i++) {
        phb.emplace_back(h[i]);
        ph = PHi::merge(ph, &phb.back());
    }
    int to_extract = n;
    while(to_extract > 0) {
        auto value = PHi::top(ph);
        size_t index = ph - phb.data();
        ph = PHi::remove_top_nodelete(ph);
        to_extract--;
        h[index] = value;
        visited[index] = true;
        for(const auto& i : children[index]) {
            if(!visited[i.second] &&
               value + i.first < PHi::top(&phb[i.second])) {
                ph = PHi::decrease_key(ph, &phb[i.second], value + i.first);
            }
        }
    }
    return accumulate(h.begin(), h.end(), 0LL);
}
