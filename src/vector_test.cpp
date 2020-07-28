//
// Created by daniiln on 27.07.2020.
//

#include <iostream>
#include <src/Vector.hpp>
#include <memory>

using namespace std;

int main() {
    //int n;
    //cin >> n;
    cll::Vector<unique_ptr<int>, false> a;
    unique_ptr<int> b(new int(5));
    a.push_back(move(b));
    cll::Vector<unique_ptr<int>, false> c;
    c = a;
    c = move(a);
    std::cout << **c.begin() << '\n';
    return 0;
}