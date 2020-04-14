#include "SString.hpp"

#include <algorithm>
#include <iterator>


namespace clnt {

    SString::SString(SString const& other): source_(other.source_), i_(other.i_), j_(other.j_) {
    }

    SString::SString(SString&& other) noexcept : source_(other.source_), i_(other.i_), j_(other.j_)  {
    }

    SString::SString(shared_ptr<std::string> source, int i, int j): source_(source), i_(i), j_(j) {}

    SString::SString(shared_ptr<std::string> source): SString(source, 0, source->size()) {}

    SString SString::slice(int i, int j) const {
        return SString(source_, i_ + i, i_ + j);
    }

    SString SString::slice(int i) const {
        return slice(i, size());
    }

    size_t SString::size() const {
        return j_ - i_;
    }

    char SString::operator[](int i) const {
        return (*source_)[i_ + i];
    }

    SString& SString::operator=(SString const& right) {
        source_ = right.source_;
        i_ = right.i_;
        j_ = right.j_;
        return *this;
    }

    size_t SString::i() const {
        return i_;
    }

    size_t SString::j() const {
        return j_;
    }

    std::string const& SString::source() const {
        return *source_;
    }

    std::ostream& operator<<(std::ostream& out, SString const& s) {
        std::copy(s.source_->begin() + s.i_, s.source_->begin() + s.j_, std::ostream_iterator<char>(out));
        return out;
    }

    bool SString::operator==(SString const& right) const {
        if (size() != right.size()) {
            return false;
        }
        return std::equal(source_->begin() + i_, source_->begin() + j_, right.source_->begin() + right.i_);
    }
}
