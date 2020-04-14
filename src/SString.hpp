#pragma once

#include <iostream>
#include <string>
#include <memory>

using std::shared_ptr;

namespace clnt {
    class SString {
        friend std::ostream& operator<<(std::ostream&, SString const&);
    public:
        SString(shared_ptr<std::string> source, int i, int j);
        SString(shared_ptr<std::string> source);
        SString(SString const&);
        SString(SString&&) noexcept;

        SString slice(int i, int j) const;
        SString slice(int i) const;

        char operator[](int i) const;

        size_t size() const;

        SString& operator=(SString const&);
        bool operator==(SString const&) const;

        size_t i() const;
        size_t j() const;
        std::string const& source() const;
    private:
        shared_ptr<std::string> source_;
        int i_, j_;
    };
}
