#ifndef ASD_SMART_VECTOR_HPP
#define ASD_SMART_VECTOR_HPP

#ifdef CHECK_INTERFACE
#define OVERRIDE override
#include <cstddef>
#include <functional>

template<typename T>
class smart_vector;

template<typename T>
class smart_vector_abs {
public:
    // Get elements in a given position
    virtual const T& front() const = 0;
    virtual T& front() = 0;
    virtual const T& back() const = 0;
    virtual T& back() = 0;
    virtual const T& operator[](std::size_t pos) const = 0;
    virtual T& operator[](std::size_t pos) = 0;

    // Insert/remove element in a given position
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(std::size_t pos, T value) = 0;
    virtual T pop_back() = 0;
    virtual T pop_front() = 0;
    virtual T erase(std::size_t pos) = 0;

    // Split/join. split makes the current vector exactly
    // size long, and returns the rest of the vector. Append
    // adds the other vector to the end of the current vector
    // and clears the other vector.
    virtual smart_vector<T> split(std::size_t size) = 0;
    virtual void append(smart_vector<T>& other) = 0;

    // Other methods
    virtual std::size_t size() const = 0;
    virtual void reverse() = 0;
    virtual void set_callback(std::function<void(T, void*)> callback) = 0;
};

#endif

#endif
