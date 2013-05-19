//
//  sumTest.cpp
//  CS540project3
//
//  Created by James Kizer on 5/3/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "sum.hpp"
#include <iostream>
#include <cxxabi.h>
#include <assert.h>

using namespace std;

ostream &
operator<<(ostream &os, const type_info &ti) {
    int ec;
    const char *demangled_name = abi::__cxa_demangle(ti.name(), 0, 0, &ec);
    assert(ec == 0);
    os << demangled_name;
    free((void *) demangled_name);
    return os;
}

struct B;
struct C;
struct D;
struct E;

struct A {
    friend A operator+(const A &, const B &);
    friend A operator+(const A &, const C &);
    friend A operator+(const A &, const D &);
    friend A operator+(const A &, const E &);
    friend ostream & operator<<(ostream &os, const A &a);
    A(int i_ = 0) : i(i_) {}
private:
    const int i;
};
struct B {
    friend A operator+(const A &a, const B &b) {
        return A(a.i + b.i);
    }
    B(int i_ = 0) : i(i_) {}
private:
    const int i;
};
struct C {
    friend A operator+(const A &a, const C &c) {
        return A(a.i + c.i);
    }
    C(int i_ = 0) : i(i_) {}
private:
    const int i;
};
struct D {
    friend A operator+(const A &a, const D &d) {
        return A(a.i + d.i);
    }
    D(int i_ = 0) : i(i_) {}
private:
    const int i;
};
struct E {
    friend A operator+(const A &a, const E &e) {
        return A(a.i + e.i);
    }
    E(int i_ = 0) : i(i_) {}
private:
    const int i;
};

ostream &
operator<<(ostream &os, const A &a) {
    return os << a.i;
}

/*
 ostream &
 operator<<(ostream &os, const B &) {
 return os << "B object";
 }
 */

int main() {
    // sum(A(), B(), C());
    //cout << typeid(sum(A(), B(), C())) << endl;
    cout << cs540::sum(A(1), B(2), C(3)) << endl;
    cout << cs540::sum(A(1), B(2), B(3)) << endl;
    cout << cs540::sum(A(1), C(2), C(3)) << endl;
    cout << cs540::sum(A(1), C(2)) << endl;
    cout << hex << showbase;
    // Prints 1, due to overflow.
    cout << cs540::sum(0xffffffffU, 1U, 1UL) << endl;
    // Prints 0x100000001, due to first promoting to UL.
    cout << cs540::sum(1UL, 1U, 0xffffffffU) << endl;
    //0 cout << cs540::sum(1, 3.1, 2) << endl;
}