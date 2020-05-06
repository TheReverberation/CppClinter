//
// Created by Daniil Nedaiborsch on 15.04.2020.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <memory>

using std::shared_ptr;
using std::move;


namespace clnt {
    template <class C>
    class Slice {
    public:
        using const_iterator = typename C::const_iterator;
        using value_type = typename C::value_type;

        Slice(shared_ptr<C> container, size_t i, size_t j): container_(move(container)), i_(i), j_(j) {}

        Slice(shared_ptr<C> container): Slice(container, 0, container->size()) {}

        Slice(shared_ptr<C> container, size_t i): Slice(container, i, container->size()) {}

        Slice(C container, size_t i): Slice(std::make_shared<C>(move(container)), i, container.size()) {}

        Slice(C container, size_t i, size_t j): Slice(std::make_shared<C>(move(container)), i, j) {}

        Slice(C container): Slice(std::make_shared<C>(move(container))) {}

        Slice(Slice const& other): container_(other.container_), i_(other.i_), j_(other.j_) {}
        Slice(Slice&& other) noexcept: container_(move(other.container_)), i_(other.i_), j_(other.j_) {}
        
        const_iterator begin() const {
            return container_->begin() + i_;
        }

        const_iterator end() const {
            return container_->begin() + j_;
        }

        value_type const& operator[](size_t i) const {
            return (*container_)[i_ + i];
        }

        size_t size() const {
            return j_ - i_;
        }

        Slice slice(size_t i, size_t j) const {
            return Slice(container_, i_ + i, i_ + j);
        }

        Slice slice(size_t i) const {
            return slice(i, size());
        }

        Slice& operator=(Slice right) {
            container_ = std::move(right.container_);
            i_ = right.i_;
            j_ = right.j_;
            return *this;
        }

        bool operator==(Slice const& right) const {
            if (size() != right.size()) {
                return false;
            }
            return std::equal(container_->begin() + i_, container_->begin() + j_, right.container_->begin() + right.i_);
        }

    private:
        shared_ptr<C> container_;
        size_t const i_, j_;
    };

    template <class C>
    Slice<C> makeSlice(C container) {
        return Slice<C>(move(container));
    }

    template <class C>
    std::ostream& operator<<(std::ostream& out, Slice<C> const& s) {
        std::copy(s.begin(), s.end(), std::ostream_iterator<typename C::value_type>(out));
        return out;
    }

}




