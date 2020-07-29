//
// Created by daniiln on 27.07.2020.
//

#include <iostream>
#include <src/types.hpp>
#include <memory>

#include <src/Slice.hpp>

using namespace std;

struct A {
    A() {
        cout << "A const\n";
    }
    ~A() {
        cout << "A dest\n";
    }
};

int main() {
    //int n;
    //cin >> n;
    Vector<unique_ptr<int>> a;
    for (int i = 0; i < 10; ++i) {
        a.push_back(make_unique<int>(i));
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << *a[i] << '\n';
    }
    return 0;
}