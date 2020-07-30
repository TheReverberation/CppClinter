#pragma once

#include <iostream>
#include <memory>
#include <set>

namespace mem {
    template <typename T>
    class PrimeGC {
    public:
        PrimeGC() {}
        PrimeGC(PrimeGC const&) = delete;
        PrimeGC(PrimeGC&&) = delete;

        void link(T* ptr) {
            pointers.insert(ptr);
        }

        template<typename C=T, typename ...Args>
        T* make(Args&& ...args) {
            T* maked = new C(std::forward<Args>(args)...);
            link(maked);
            return maked;
        }

        std::shared_ptr<T> unlink(T* ptr) {
            assert(pointers.find(ptr) != pointers.end());
            pointers.erase(ptr);
            return std::shared_ptr<T>(ptr);
        }

        void unlinkAll() {
            for (auto& now : pointers) {
                delete now;
            }
            pointers.clear();
        }

        ~PrimeGC() {
            unlinkAll();
        }

    private:
        std::set<T*> pointers;
    };
}


