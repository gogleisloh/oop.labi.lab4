#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>
#include <stdexcept>
#include <utility>
#include <algorithm>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data_;  
    size_t size_;
    size_t capacity_;
    
    void reallocate(size_t new_capacity) {
        std::shared_ptr<T[]> new_data(new T[new_capacity]);
        
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
    
public:
    Array() : size_(0), capacity_(10) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }
    
    explicit Array(size_t capacity) : size_(0), capacity_(capacity) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }
    
    ~Array() = default;
    
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_))
        , size_(other.size_)
        , capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = std::shared_ptr<T[]>(new T[capacity_]);
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reallocate(capacity_ * 2);
        }
        data_[size_++] = value;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reallocate(capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }
    
    void remove(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    
    T* begin() { return data_.get(); }
    T* end() { return data_.get() + size_; }
    const T* begin() const { return data_.get(); }
    const T* end() const { return data_.get() + size_; }
};

#endif
