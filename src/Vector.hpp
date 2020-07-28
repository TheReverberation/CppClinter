#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <iterator>
#include <iostream>
#include <initializer_list>

namespace cll {

    template <typename T, bool copyable=true>
    class Vector;

    template <typename T>
    class Vector<T, true> {
    public:
        using iterator = T*;
        using const_iterator = T const*;

        Vector() {
            size_ = 0;
            cap = 1;
            block = new T[1];
            alloc_const = 3. / 2;
        }

        Vector(std::initializer_list<T> l) {
            std::cout << "asdasd\n";
            //std::copy(l.begin(), l.end(), std::ostream_iterator<T>(std::cout, " ")); std::cout << '\n';
            std::cout << l.size() << '\n';
            size_ = l.size();
            cap = l.size() + 1;
            block = new T[cap];
            alloc_const = 3. / 2;
            std::copy(l.begin(), l.end(), block);
        }

        explicit Vector(size_t size) {
            this->size_ = size;
            this->cap = size;
            block = new T[cap];
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
            block = new T[cap];
            std::copy(other.begin(), other.end(), block);
        }

        ~Vector() {
            if (block) {
                delete[] block;
            }
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
            block[size_ - 1] = move(value);
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
                block = new T[cap];
                block_move(oldblock, block, size_);
                size_ = newsize;
            }
        }


        size_t size() {
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
                newblock[i] = move(oldblock[i]);
            }
        }

        void block_copy(T* oldblock, T* newblock, size_t blocksize) {
            using std::move;
            for (size_t i = 0; i < blocksize; ++i) {
                newblock[i] = oldblock[i];
            }
        }

    };


    template <typename T>
    class Vector<T, false> {
    public:
        using iterator = T*;
        using const_iterator = T const*;

        Vector() {
            size_ = 0;
            cap = 1;
            block = new T[1];
            alloc_const = 3. / 2;
        }

        Vector(std::initializer_list<T> l) {
            std::cout << "asdasd\n";
            //std::copy(l.begin(), l.end(), std::ostream_iterator<T>(std::cout, " ")); std::cout << '\n';
            std::cout << l.size() << '\n';
            size_ = l.size();
            cap = l.size() + 1;
            block = new T[cap];
            alloc_const = 3. / 2;
            std::copy(l.begin(), l.end(), block);
        }

        explicit Vector(size_t size) {
            this->size_ = size;
            this->cap = size;
            block = new T[cap];
            alloc_const = 3. / 2;
        }

        Vector(Vector&& other): Vector() {
            std::swap(block, other.block);
            std::swap(size_, other.size_);
            std::swap(cap, other.cap);
        }

        ~Vector() {
            if (block) {
                delete[] block;
            }
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
            block[size_ - 1] = move(value);
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
                block = new T[cap];
                block_move(oldblock, block, size_);
                size_ = newsize;
            }
        }


        size_t size() {
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
                newblock[i] = move(oldblock[i]);
            }
        }

        void block_copy(T* oldblock, T* newblock, size_t blocksize) {
            using std::move;
            for (size_t i = 0; i < blocksize; ++i) {
                newblock[i] = oldblock[i];
            }
        }

    };
}