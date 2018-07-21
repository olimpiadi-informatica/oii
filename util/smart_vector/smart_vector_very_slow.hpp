#ifndef ASD_SMART_VECTOR_VERY_SLOW_HPP
#define ASD_SMART_VECTOR_VERY_SLOW_HPP

#ifdef CHECK_INTERFACE
#include "smart_vector.hpp"
#else
#define OVERRIDE
#endif

#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cassert>

template<typename T>
class smart_vector
#ifdef CHECK_INTERFACE
    : smart_vector_abs<T>
#endif
{
public:
    smart_vector(): size_(0) {}
    smart_vector(const smart_vector&) = delete;
    smart_vector(smart_vector&& old) {*this = std::move(old);}
    smart_vector& operator=(smart_vector&& old) {
	    callback_ = std::move(old.callback_);
	    size_ = old.size_;
	    data_ = std::move(old.data_);
        old.size_ = 0;
        old.data_ = {};
	    for (auto& elem : data_) {
            if (callback_) {
                callback_(elem.first, &elem);
            }
		    elem.second = this;
        }
        return *this;
    }

    void set_callback(std::function<void(T, void*)> callback) {
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
        return get_(pos);
    }
    T& operator[](std::size_t pos) OVERRIDE {
        // yes, this is safe
        return const_cast<T &>(const_cast<const smart_vector &>(*this).get_(pos));
    }

    // Insert/remove element in a given position
    void push_back(T value) OVERRIDE {
        insert(size(), std::move(value));
    }
    void push_front(T value) OVERRIDE {
        insert(0, std::move(value));
    }
    void insert(std::size_t pos, T value) OVERRIDE {
        size_++;
        return insert_(pos, value);
    }

    T pop_back() OVERRIDE {
        return erase(size()-1);
    }
    T pop_front() OVERRIDE {
        return erase(0);
    }
    T erase(std::size_t pos) OVERRIDE {
        size_--;
        return erase_(pos);
    }

    // Split/join. split makes the current vector exactly
    // size long, and returns the rest of the vector. Append
    // adds the other vector to the end of the current vector
    // and clears the other vector.
    smart_vector<T> split(std::size_t size) OVERRIDE {
        auto ret = split_(size);
        ret.size_ = size_ - size;
        size_ = size;
        return ret;
    }

    void append(smart_vector<T>& other) OVERRIDE {
        append_(other);
        other.size_ = 0;
    }


    // Other methods
    std::size_t size() const OVERRIDE {
        return size_;
    }

    void reverse() OVERRIDE {
        return reverse_();
    }

    static std::pair<smart_vector<T>*, std::size_t> find_owner(const T& element, void* ptr) {
        (void)element;
        std::pair<T, smart_vector<T>*>* info = (std::pair<T, smart_vector<T>*>*) ptr;
        return {info->second, info - info->second->data_.data()};
    }
private:
    const T& get_(std::size_t pos) const {
        return data_[pos].first;
    }

    void insert_(std::size_t pos, T value) {
        auto old_capacity = data_.capacity();
        data_.emplace(data_.begin()+pos, std::move(value), this);
        if (callback_) {
            if (data_.capacity() != old_capacity) {
                for (auto& elem: data_) {
                    callback_(elem.first, &elem);
                }
            } else {
                for (std::size_t i=pos; i<data_.size(); i++) {
                    auto& elem = data_[i];
                    callback_(elem.first, &elem);
                }
            }
        }
    }
    
    T erase_(std::size_t pos) {
        T ret = std::move(data_[pos].first);
        data_.erase(data_.begin()+pos);
        if (callback_) {
            for (std::size_t i=pos; i<data_.size(); i++) {
                auto& elem = data_[i];
                callback_(elem.first, &elem);
            }
        }
        return ret;
    }

    smart_vector<T> split_(std::size_t size) {
        smart_vector<T> tail;
        tail.set_callback(callback_);
        for (std::size_t i=size; i<size_; i++) {
            tail.push_back(std::move((*this)[i]));
        }
        if (size < size_) {
            data_.resize(size);
        }
        if (callback_) {
            for (auto& elem: data_) {
                callback_(elem.first, &elem);
            }
        }
        return tail;
    }

    void append_(smart_vector<T>& other) {
        for (auto& el: other.data_) {
            push_back(std::move(el.first));
        }
        if (callback_) {
            for (auto& elem: data_) {
                callback_(elem.first, &elem);
            }
        }
        other.data_.clear();
    }

    void reverse_() {
        std::reverse(data_.begin(), data_.end());
    }

    std::vector<std::pair<T, smart_vector<T>*>> data_;
    std::size_t size_;
    std::function<void(T, void*)> callback_;
};

#endif
