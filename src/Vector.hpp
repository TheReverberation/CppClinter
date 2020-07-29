#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <iterator>
#include <iostream>
#include <initializer_list>

namespace cll {

    template <typename T, bool copyable>
    class Vector;

    template <typename T>
    class Vector<T, true> {
        friend Vector<T, false>;
    public:
        using iterator = T*;
        using const_iterator = T const*;
        using value_type = T;

        Vector() {
            size_ = 0;
            cap = 1;
            block = (T*)::operator new (cap * sizeof(T));
            alloc_const = 3. / 2;
        }

        Vector(std::initializer_list<T> l) {
            size_ = l.size();
            cap = l.size() + 1;
            block = (T*)::operator new(cap * sizeof(T));
            alloc_const = 3. / 2;
            std::copy(l.begin(), l.end(), block);
        }

        explicit Vector(size_t size) {
            this->size_ = size;
            this->cap = size;
            block = (T*)::operator new(cap * sizeof(T));
            alloc_const = 3. / 2;
        }

        Vector(Vector&& other): Vector() {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
        }

        Vector(Vector const& other) {
            size_ = other.size_;
            cap = other.cap;
            block = (T*)::operator new(cap * sizeof(T));
            std::copy(other.begin(), other.end(), block);
        }

        Vector(Vector<T, false> other): Vector() {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
        }

        ~Vector() {
            for (size_t i = 0; i < size_; ++i) {
                (block + i)->~T();
            }
            ::operator delete(block);
        }


        Vector& operator=(Vector other) {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
            return *this;
        }

        T const& operator[](size_t i) const {
            return block[i];
        }

        T& operator[](size_t i) {
            return block[i];
        }

        void push_back(T value) {
            resize(size_ + 1);
            //std::cout << "pushback: " << size_ << ' ' << cap << '\n';
            new (block + size_ - 1) T(std::move(value));
        }

        const_iterator begin() const {
            return block;
        }

        const_iterator end() const {
            return block + size_;
        }

        iterator begin() {
            return block;
        }

        iterator end() {
            return block + size_;
        }

        void resize(size_t newsize) {
            if (newsize <= cap) {
                size_ = newsize;
                return;
            } else {
                cap = newsize * alloc_const + 1;
                T* oldblock = block;
                block = (T*)::operator new(cap * sizeof(T));
                block_move(oldblock, block, size_);
                size_ = newsize;
            }
        }


        size_t size() const {
            return size_;
        }
    private:

        T* block;
        size_t size_;
        size_t cap;
        float alloc_const = 3. / 2;

        void block_move(T* oldblock, T* newblock, size_t blocksize) {
            using std::move;
            for (size_t i = 0; i < blocksize; ++i) {
                new(newblock + i) T(move(oldblock[i]));
            }
        }
    };


    template <typename T>
    class Vector<T, false> {
        friend Vector<T, true>;
    public:
        using iterator = T*;
        using const_iterator = T const*;
        using value_type = T;

        Vector() {
            size_ = 0;
            cap = 1;
            block = (T*)::operator new(cap * sizeof(T));
            alloc_const = 3. / 2;
        }

        Vector(std::initializer_list<T> l) {
            size_ = l.size();
            cap = l.size() + 1;
            block = (T*)::operator new(cap * sizeof(T));
            alloc_const = 3. / 2;
            std::copy(l.begin(), l.end(), block);
        }

        explicit Vector(size_t size) {
            this->size_ = size;
            this->cap = size;
            block = (T*)::operator new(cap * sizeof(T));
            alloc_const = 3. / 2;
        }

        Vector(Vector&& other): Vector() {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
        }

        Vector(Vector<T, true> other): Vector() {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
        }

        ~Vector() {
            for (size_t i = 0; i < size_; ++i) {
                (block + i)->~T();
            }
            ::operator delete(block);
        }


        Vector& operator=(Vector&& other) {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
            return *this;
        }

        T const& operator[](size_t i) const {
            return block[i];
        }

        T& operator[](size_t i) {
            return block[i];
        }

        void push_back(T value) {
            resize(size_ + 1);
            //std::cout << "pushback: " << size_ << ' ' << cap << '\n';
            new (block + size_ - 1) T(std::move(value));
        }

        const_iterator begin() const {
            return block;
        }

        const_iterator end() const {
            return block + size_;
        }

        T& front() {
            return block[0];
        }

        T const& front() const {
            return block[0];
        }

        T& back() {
            return block[size_ - 1];
        }

        T const& back() const {
            return block[size_ - 1];
        }

        iterator begin() {
            return block;
        }

        iterator end() {
            return block + size_;
        }

        void resize(size_t newsize) {
            if (newsize <= cap) {
                size_ = newsize;
                return;
            } else {
                cap = newsize * alloc_const + 1;
                T* oldblock = block;
                block = (T*)::operator new(cap * sizeof(T));
                block_move(oldblock, block, size_);
                size_ = newsize;
            }
        }


        size_t size() const {
            return size_;
        }
    private:

        T* block;
        size_t size_;
        size_t cap;
        float alloc_const = 3. / 2;

        void block_move(T* oldblock, T* newblock, size_t blocksize) {
            for (size_t i = 0; i < blocksize; ++i) {
                new (newblock + i) T(move(oldblock[i]));
            }
        }

        void block_copy(T* oldblock, T* newblock, size_t blocksize) {
            using std::move;
            for (size_t i = 0; i < blocksize; ++i) {
                new(newblock + i) T(oldblock[i]);
            }
        }

    };
}