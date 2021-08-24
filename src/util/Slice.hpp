#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>

namespace {
    template<typename T>
    using remove_all_t = std::remove_const_t<std::remove_reference_t<T>>;
}

namespace clnt::util {
    template <class C>
    class Slice {
    public:
        using const_iterator = typename C::const_iterator;
        using iterator = typename C::iterator;
        using value_type = typename C::value_type;

        Slice(std::shared_ptr<C> container, size_t i, size_t j): container_(std::move(container)), i_(i), j_(j) {}

        Slice(std::shared_ptr<C> container): Slice(std::move(container), 0, container->size()) {}

        Slice(std::shared_ptr<C> container, size_t i): Slice(std::move(container), i, container->size()) {}

        Slice(C container, size_t i): Slice(std::make_shared<C const>(std::move(container)), i, container.size()) {}

        Slice(C container, size_t i, size_t j): Slice(std::make_shared<C const>(std::move(container)), i, j) {}
        
        Slice(C const& container): Slice(std::make_shared<C>(container)) {}
        Slice(C&& container): Slice(std::make_shared<C>(std::move(container))) {}

        Slice(Slice const& other) = default;
        Slice(Slice&& other) = default;
        
        const_iterator begin() const {
            return container_->begin() + i_;
        }

        const_iterator end() const {
            return container_->begin() + j_;
        }

        iterator begin() {
            return container_->begin() + i_;
        }

        iterator end() {
            return container_->begin() + j_;
        }

        value_type const& front() const {
            return (*container_)[i_];
        }

        value_type const& back() const {
            return (*container_)[j_ - 1];
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

        bool operator!=(Slice const& right) const {
            return !(*this == right);
        }

        size_t i() const {
            return i_;
        }

        size_t j() const {
            return j_;
        }

        std::shared_ptr<C const> container() const {
            return container_;
        }

    private:
        std::shared_ptr<C> container_;
        size_t const i_, j_;
    };


    template <typename C>
    decltype(auto) makeSlice(C&& container) {
        return Slice<::remove_all_t<C>>(std::forward<C>(container));
    }

    template <class C>
    std::ostream& operator<<(std::ostream& out, Slice<C> const& s) {
        std::copy(s.begin(), s.end(), std::ostream_iterator<typename C::value_type>(out));
        return out;
    }

}




