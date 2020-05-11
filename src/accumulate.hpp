#pragma once

namespace clnt {
    template <typename T, typename It>
    T accumulate(It begin, It end, T init) {
        T sum(init);
        for (auto i = begin; i != end; ++i) {
            sum += *i;
        }
        return sum;
    }

    template <typename T, typename It, typename Op>
    T accumulate(It begin, It end, T init, Op operation) {
        T sum(init);
        for (auto i = begin; i != end; ++i) {
            operation(sum, *i);
        }
        return sum;
    }
}
