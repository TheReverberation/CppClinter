#pragma once

#include <utility>

namespace clnt::util {
    template <typename T, typename It>
    decltype(auto) accumulate(It begin, It end, T&& init) {
        using ReturnType = std::remove_reference_t<T>;
        ReturnType sum(std::forward<T>(init));
        for (auto i = begin; i != end; ++i) {
            sum += *i;
        }
        return sum;
    }

    template <typename T, typename It, typename Op>
    decltype(auto) accumulate(It begin, It end, T&& init, Op&& operation) {
        using ReturnType = std::remove_reference_t<T>;
        ReturnType sum(std::forward<T>(init));
        for (auto i = begin; i != end; ++i) {
            operation(sum, *i);
        }
        return sum;
    }
}
