// Implementazione dello smart_vector tramite vettore di bucket
// di dimensione sqrt(n)
//
// Autore: Dario Ostuni

#ifndef ASD_SMART_VECTOR_SLOW_HPP
#define ASD_SMART_VECTOR_SLOW_HPP

#ifdef CHECK_INTERFACE
#include "smart_vector.hpp"
#else
#define OVERRIDE
#endif

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <utility>
#include <vector>

template<typename T>
class smart_vector
#ifdef CHECK_INTERFACE
    : smart_vector_abs<T>
#endif
{
public:
    smart_vector() {}

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
        return insert_(pos, value);
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
        return size_();
    }

    void reverse() OVERRIDE {
        return reverse_();
    }

    static std::pair<smart_vector<T>*, std::size_t> find_owner(const T& element, void* ptr) {
        smart_vector<T>* sv = ((bucket<T>*)ptr)->parent;
        std::size_t counter = ((bucket<T>*)ptr)->get_element_position(element);
        if(counter == std::size_t(-1))
            return std::make_pair(nullptr, 0);
        for(const auto& p: sv->data) {
            if(p.get() == ptr) {
                break;
            }
            counter += p->size();
        }
        return std::make_pair(sv, counter);
    }

    smart_vector<T> (const smart_vector<T>&) = delete;

    smart_vector<T>& operator=(const smart_vector<T>&) = delete;

    smart_vector<T>(smart_vector<T>&& other) {*this = std::move(other);}

    smart_vector<T>& operator=(smart_vector<T>&& other) {
        callback_ = std::move(other.callback_);
        data = std::move(other.data);
        for(auto& bkt: data)
            bkt->set_parent(this);
        return *this;
    }
protected:
    template<typename U>
    class bucket {
    public:
        friend class smart_vector<U>;
        bucket(smart_vector<U>* parent_) {
            reversed = false;
            parent = parent_;
        }

        std::size_t get_element_position(const U& element) {
            std::size_t counter = 0;
            if(reversed) {
                for(auto it = data.rbegin(); it != data.rend(); ++it, counter++) {
                    if(element == *it) {
                        return counter;
                    }
                }
            } else {
                for(auto it = data.begin(); it != data.end(); ++it, counter++) {
                    if(element == *it) {
                        return counter;
                    }
                }
            }
            return std::size_t(-1);
        }

        void set_parent(smart_vector<U>* parent_) {
            parent = parent_;
        }

        std::size_t size() const {
            return data.size();
        }

        void reverse() {
            reversed = !reversed;
        }

        void push_back(U element) {
            if(reversed) {
                std::reverse(data.begin(), data.end());
                reversed = false;
            }
            data.push_back(element);
        }

        U pop_front() {
            if(reversed) {
                auto tmp = data.back();
                data.pop_back();
                return tmp;
            } else {
                auto tmp = data.front();
                data.pop_front();
                return tmp;
            }
        }

        U pop_back() {
            if(reversed) {
                auto tmp = data.front();
                data.pop_front();
                return tmp;
            } else {
                auto tmp = data.back();
                data.pop_back();
                return tmp;
            }
        }

        const T& front() {
            return (reversed ? data.back() : data.front());
        }

        const T& back() {
            return (reversed ? data.front() : data.back());
        }

        void insert(std::size_t pos, U element) {
            if(reversed) {
                auto it = data.rbegin();
                std::advance(it, pos);
                data.insert(it.base(), element);
            } else {
                auto it = data.begin();
                std::advance(it, pos);
                data.insert(it, element);
            }
        }

        const T& get(std::size_t pos) {
            if(reversed) {
                auto it = data.rbegin();
                std::advance(it, pos);
                return *it;
            } else {
                auto it = data.begin();
                std::advance(it, pos);
                return *it;
            }
        }

        U erase(std::size_t pos) {
            if(reversed) {
                auto it = data.rbegin();
                std::advance(it, pos);
                U tmp = *it;
                data.erase(--(it.base()));
                return tmp;
            } else {
                auto it = data.begin();
                std::advance(it, pos);
                U tmp = *it;
                data.erase(it);
                return tmp;
            }
        }

        void merge(bucket<U>* other) {
            if(reversed) {
                std::reverse(data.begin(), data.end());
                reversed = false;
            }
            if(other->reversed) {
                std::reverse(other->data.begin(), other->data.end());
                other->reversed = false;
            }
            if(parent->callback_) {
                for(const auto& e: other->data) {
                    parent->callback_(e, this);
                }
            }
            for (const auto& e: other->data) {
                data.push_back(e);
            }
            other->data.clear();
        }

        std::unique_ptr<bucket<U>> split(std::size_t pos) {
            if(reversed) {
                std::reverse(data.begin(), data.end());
                reversed = false;
            }
            std::vector<U> new_data;
            auto it_end = data.begin();
            std::advance(it_end, pos);
            for (unsigned i=pos; i<data.size(); i++) {
                new_data.push_back(data[i]);
            }
            data.resize(pos);
            auto new_bucket = std::unique_ptr<bucket<U>>(new bucket<U>(new_data, parent));
            if (parent->callback_) {
                for(const auto& e: new_bucket->data) {
                    parent->callback_(e, new_bucket.get());
                }
            }
            return new_bucket;
        }

        bucket(std::vector<U> custom_data, smart_vector<U>* parent_) {
            reversed = false;
            data = custom_data;
            parent = parent_;
        }
    protected:
        std::vector<U> data;
        bool reversed;
        smart_vector<U>* parent;
    };

    mutable std::vector<std::unique_ptr<bucket<T>>> data;
    std::function<void(T, void*)> callback_;

    std::size_t ideal_bucket_size_() const {
        return (std::size_t)(std::sqrt(size()));
    }

    void bucket_maintenance_() const {
        while(data.size() != 0 && data.back()->size() == 0)
            data.pop_back();
        if(data.size() == 0)
            return;
        std::size_t bsize = ideal_bucket_size_();
        for(std::size_t i = 0; i < data.size() - 1; i++) {
            if(data[i]->size() < bsize / 2 && data[i + 1]->size() < bsize / 2) {
                data[i]->merge(data[i + 1].get());
                data.erase(data.begin() + i + 1);
            }
        }
        for(std::size_t i = 0; i < data.size(); i++) {
            if(data[i]->size() > bsize * 2) {
                data.insert(data.begin() + i + 1, data[i]->split(bsize));
            }
        }
        if(data.back()->size() == 0) {
            data.pop_back();
        } else if(data.back()->size() > bsize) {
            data.push_back(data.back()->split(bsize));
        }
    }

    std::pair<typename std::vector<std::unique_ptr<bucket<T>>>::iterator, std::size_t> get_bucket_(std::size_t pos) const {
        std::size_t counter = 0;
        auto it = data.begin();
        while(it != data.end() && counter + (*it)->size() <= pos) {
            counter += (*it)->size();
            ++it;
        }
        return std::make_pair(it, counter);
    }

    const T& get_(std::size_t pos) const {
        bucket_maintenance_();
        auto p = get_bucket_(pos);
        return (*p.first)->get(pos - p.second);
    }

    void insert_(std::size_t pos, T value) {
        if(data.size() == 0) {
            data.emplace_back(new bucket<T>(this));
            data.front()->push_back(value);
            if(callback_)
                callback_(value, data.front().get());
        } else {
            auto p = get_bucket_(pos);
            if(p.first == data.end()) {
                data.back()->push_back(value);
                if(callback_)
                    callback_(value, data.back().get());
            } else {
                (*p.first)->insert(pos - p.second, value);
                if(callback_)
                    callback_(value, (*p.first).get());
            }
            bucket_maintenance_();
        }
    }

    T erase_(std::size_t pos) {
        auto p = get_bucket_(pos);
        auto tmp = (*p.first)->erase(pos - p.second);
        if((*p.first)->size() == 0)
            data.erase(p.first);
        bucket_maintenance_();
        return tmp;
    }

    smart_vector<T> split_(std::size_t pos) {
        auto p = get_bucket_(pos);
        if(p.first == data.end())
            return smart_vector<T>();
        smart_vector<T> new_vector;
        new_vector.set_callback(callback_);
        auto new_first_bucket = (*p.first)->split(pos - p.second);
        if(new_first_bucket->size() != 0)
            new_vector.data.push_back(std::move(new_first_bucket));
        auto it = p.first + 1;
        while(it != data.end()) {
            new_vector.data.push_back(std::move(*it));
            ++it;
        }
        data.erase(p.first + 1, data.end());
        if((*p.first)->size() == 0)
            data.erase(p.first);
        for(auto& bkt: new_vector.data)
            bkt->set_parent(&new_vector);
        return new_vector;
    }

    void append_(smart_vector<T>& other) {
        for(auto& bkt: other.data)
            bkt->set_parent(this);
        for(std::size_t i = 0; i < other.data.size(); i++)
            data.push_back(std::move(other.data[i]));
        other.clear_();
    }

    void reverse_() {
        for(auto& bkt: data)
            bkt->reverse();
        std::reverse(data.begin(), data.end());
    }

    std::size_t size_() const {
        std::size_t counter = 0;
        for(auto& bkt: data)
            counter += bkt->size();
        return counter;
    }

    void clear_() {
        data.clear();
    }

    void print_debug_() const {
        std::cout << "VALUES: ";
        for(std::size_t i = 0; i < data->size(); i++) {
            for(std::size_t j = 0; j < data[i]->size(); j++)
                std::cout << data[i]->get(j) << " ";
            if(i != data.size() - 1)
                std::cout << "| ";
        }
        std::cout << std::endl;
    }
};

#endif
