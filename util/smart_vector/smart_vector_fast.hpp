#ifndef ASD_SMART_VECTOR_FAST_HPP
#define ASD_SMART_VECTOR_FAST_HPP

#ifdef CHECK_INTERFACE
#include "smart_vector.hpp"
#else
#define OVERRIDE
#endif

#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <stack>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <functional>

template<typename T>
class smart_vector
#ifdef CHECK_INTERFACE
    : smart_vector_abs<T>
#endif
{
public:
    smart_vector() {init_();}
    ~smart_vector() {destroy_();}

    smart_vector(const smart_vector<T>& other) = delete;
    smart_vector(smart_vector<T>&& other) {
        init_();
        *this = std::move(other);
    }

    smart_vector& operator=(smart_vector<T>&& other) {
        set_root_(other.root_);
        callback_ = other.callback_;
        other.init_();
        return *this;
    }

    void set_callback(std::function<void(T, void*)> callback) OVERRIDE {
        callback_ = callback;
    }

    // Get elements in a given position
    const T& front() const OVERRIDE {
        return (*this)[0];
    }
    T& front() OVERRIDE {
        return (*this)[0];
    }

    const T& back() const OVERRIDE {
        return (*this)[size()-1];
    }
    T& back() OVERRIDE {
        return (*this)[size()-1];
    }

    const T& operator[](std::size_t pos) const OVERRIDE {
        return get_(pos)->value;
    }
    T& operator[](std::size_t pos) OVERRIDE {
        return get_(pos)->value;
    }

    // Insert/remove element in a given position
    void push_back(T value) OVERRIDE {
        insert(size(), std::move(value));
    }
    void push_front(T value) OVERRIDE {
        insert(0, std::move(value));
    }
    void insert(std::size_t pos, T value) OVERRIDE {
        insert_(pos, value);
    }

    T pop_back() OVERRIDE {
        return erase(size()-1);
    }
    T pop_front() OVERRIDE {
        return erase(0);
    }
    T erase(std::size_t pos) OVERRIDE {
        return erase_(pos);
    }

    // Split/join. split makes the current vector exactly
    // size long, and returns the rest of the vector. Append
    // adds the other vector to the end of the current vector
    // and clears the other vector.
    smart_vector<T> split(std::size_t size) OVERRIDE {
        return split_(size);
    }

    void append(smart_vector<T>& other) OVERRIDE {
        append_(other);
    }


    // Other methods
    std::size_t size() const OVERRIDE {
        return size_(root_);
    }

    void reverse() OVERRIDE {
        return reverse_();
    }

    void print_vector() {
        print_vector(root_);
        printf("\n");
    }

    static std::pair<smart_vector<T>*, std::size_t> find_owner(const T& element, void* ptr) {
        (void)element;
        node_t* cur = (node_t*) ptr;
        assert(cur->value == element);
        unlz(cur);
        std::size_t pos = size_(cur->left);
        while (!cur->is_root) {
            bool is_left_child = false;
            if (cur->parent->left == cur) is_left_child = true;
            cur = cur->parent;
            if (!is_left_child) pos += size_(cur->left) + 1;
        }
        smart_vector<T>* ds = (smart_vector<T>*)cur->parent;
        assert(ds->root_ == cur);
        return {ds, pos};
    }
private:
    struct node_t {
        node_t* left;
        node_t* right;
        node_t* parent; // Represents the entire DS for the root
        std::size_t size;
        T value;
        char reversed:1;
        char is_root:1;
    };

    static void unlz(node_t* cur) {
        if (!cur->is_root) unlz(cur->parent);
        unlazy_reverse_(cur);
    }

    smart_vector(node_t* root, std::function<void(T, void*)> callback)
        : callback_(callback) {init_(); set_root_(root);}

    void set_root_(node_t* root) const {
        if (root_) root_->is_root = false;
        root_ = root;
        if (root_) {
            root_->parent = (node_t*) this;
            root_->is_root = true;
        }
    }

    static std::size_t size_(node_t* x) {
        return x ? x->size : 0;
    }

    static void unlazy_reverse_(node_t* x) {
        if (!x) return;
        if (x->reversed) {
            x->reversed = false;
            std::swap(x->left, x->right);
            if (x->left) x->left->reversed = !x->left->reversed;
            if (x->right) x->right->reversed = !x->right->reversed;
        }
    }

    void left_rotate_(node_t* x) const {
        unlazy_reverse_(x);
        node_t* y = x->right;
        unlazy_reverse_(y);
        if (y) {
            x->size -= size_(x->right);
            x->right = y->left;
            x->size += size_(y->left);
            if (y->left) y->left->parent = x;
            y->parent = x->parent;
        }

        if (x->is_root) set_root_(y);
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) {
            y->size -= size_(y->left);
            y->left = x;
            y->size += size_(x);
        }
        x->parent = y;
    }

    void right_rotate_(node_t* x) const {
        unlazy_reverse_(x);
        node_t* y = x->left;
        unlazy_reverse_(y);
        if (y) {
            x->size -= size_(x->left);
            x->left = y->right;
            x->size += size_(y->right);
            if (y->right) y->right->parent = x;
            y->parent = x->parent;
        }

        if (x->is_root) set_root_(y);
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) {
            y->size -= size_(y->right);
            y->right = x;
            y->size += size_(x);
        }
        x->parent = y;
    }

    void splay_(node_t* x) const {
        while (!x->is_root) {
            if (x->parent->is_root) {
                if (x->parent->left == x ) right_rotate_(x->parent);
                else left_rotate_(x->parent);
            } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
                right_rotate_(x->parent->parent);
                right_rotate_(x->parent);
            } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
                left_rotate_(x->parent->parent);
                left_rotate_(x->parent);
            } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
                right_rotate_(x->parent);
                left_rotate_(x->parent);
            } else {
                left_rotate_(x->parent);
                right_rotate_(x->parent);
            }
        }
    }

    void full_splay_(std::size_t pos) const {
        if (!root_) return;
        node_t* x = root_;
        unlazy_reverse_(x);
        while (size_(x->left) != pos) {
            if (size_(x->left) > pos) {
               x = x->left;
            } else {
                pos -= size_(x->left) + 1;
                x = x->right;
            }
            unlazy_reverse_(x);
        }
        splay_(x);
    }

    node_t* new_node_(T value = T()) {
        node_t* n = new node_t;
        n->left = n->right = n->parent = nullptr;
        n->size = 1;
        n->value = std::move(value);
        n->reversed = false;
        n->is_root = false;
        return n;
    }

    const node_t* get_(std::size_t pos) const {
        full_splay_(pos);
        return root_;
    }

    node_t* get_(std::size_t pos) {
        // yes, this is safe
        return const_cast<node_t*>(const_cast<const smart_vector &>(*this).get_(pos));
    }

    void insert_(std::size_t pos, T value) {
        smart_vector<T> temp = split_(pos);
        node_t* new_root = new_node_(std::move(value));
        new_root->left = root_;
        new_root->right = temp.root_;
        new_root->size += size_(root_) + size_(temp.root_);
        if (root_) {
            root_->parent = new_root;
            root_->is_root = false;
        }
        if (temp.root_) {
            temp.root_->parent = new_root;
            temp.root_->is_root = false;
        }
        set_root_(new_root);
        temp.init_();
        if (callback_) callback_(root_->value, root_);
    }

    T erase_(std::size_t pos) {
        full_splay_(pos);
        node_t* old_root = root_;
        smart_vector<T> temp = root_->right;
        set_root_(root_->left);
        append_(temp);
        T ret = std::move(old_root->value);
        delete old_root;
        return ret;
    }

    smart_vector<T> split_(std::size_t size) {
        if (size == size_(root_)) return {};
        full_splay_(size);
        node_t* temp = root_->left;
        root_->size -= size_(root_->left);
        root_->left = nullptr;
        std::swap(temp, root_);
        set_root_(root_);
        return {temp, callback_};
    }

    void append_(smart_vector<T>& other) {
        node_t* other_root = other.root_;
        other.init_();
        if (root_ == nullptr) {
            set_root_(other_root);
            return;
        }
        full_splay_(root_->size-1);
        root_->right = other_root;
        if (other_root) {
            other_root->parent = root_;
            other_root->is_root = false;
        }
        root_->size += size_(other_root);
    }

    void reverse_() {
        if (root_) {
            root_->reversed = !root_->reversed;
        }
    }

    void init_() {
        root_ = nullptr;
    }

    void destroy_() {
        destroy_(root_);
    }

    void destroy_(node_t* rt) {
        if (!rt) return;
        destroy_(rt->left);
        destroy_(rt->right);
        delete rt;
    }

    void print_vector(node_t* rt) {
        if (!rt) return;
        print_vector(rt->left);
        printf("%d ", rt->value);
        print_vector(rt->right);
    }

    void print_tree_(node_t* rt) const{
        if (!rt) return;
        printf("%lu (%p): {", rt->size, rt);
        print_tree_(rt->left);
        printf(", ");
        print_tree_(rt->right);
        printf("}");
    }

    void print_tree_() const {
        printf("\n\n");
        print_tree_(root_);
        printf("\n\n");
    }

    mutable node_t* root_;
    std::function<void(T, void*)> callback_;
};

smart_vector<int> tmp;

#endif
