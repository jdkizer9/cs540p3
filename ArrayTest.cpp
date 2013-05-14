//
//  ArrayTest.cpp
//  CS540project3
//
//  Created by James Kizer on 5/3/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include <iostream>
#include "Array.hpp"




int main() {
    
//    cs540::Array<int, 1> a, b;
//    
//    a[0] = 1;
//    
//    cs540::Array<short, 1> c = a;
//    
//    std::tuple<int, char> foo (10, 'x');
//    
//    
//    
//    
//    
//    
//    cs540::Array<int, 1, 1> a1, b1;
//    
//    auto i1 = a1.fmbegin();
//    auto i2 = a1.fmend();
//    
//    
//    if (i1 != i2)
//        std::cout<<*i1<<std::endl;
//    
//    i1++;
//    
//    if (i1 != i2)
//        std::cout<<*i1<<std::endl;
//   
//    a1[0][0] = 1;
//    std::cout<<*i1<<std::endl;
//    a1[0][0] = 2;
//    std::cout<<*i1<<std::endl;
//    *i1 = 3;
//    std::cout<<*i1<<std::endl;
//    
//    for(i1 = a1.fmbegin(); i1 != a1.fmend(); i1++)
//        std::cout<<*i1<<std::endl;
    
    //b1[0][0] = a1[0][0];
    
    // Define a 2X3X4 array of integers.  Elements are uninitialized.
    cs540::Array<int, 2, 3, 4> a, b;
    cs540::Array<short, 2, 3, 4> c;
    cs540::Array<short, 1, 3, 4> d;
    //cs540::Array<int, 0> e1; // This line must cause a compile-time error.
    //cs540::Array<int, 1, 0, 1> e2; // This line must cause a compile-time error.
    //cs540::Array<int, 0, 1, 1> e3; // This line must cause a compile-time error.
    
//    // Range-checked indexing.
    a[0][0][0] = 1234;
    a[1][1][1] = a[0][0][0];
    a[0][2][3] = 5678; // Set the element in the first plane, 3rd row, and 4th column.
//    a[0][3][0] = 1; // Out of range, throws.
//    
    
    auto i1 = a.fmbegin();
    auto i2 = a.fmend();
    
    for(int i=0;i1!=i2;++i1, i++)
        *i1 = i;
    
    auto i3 = b.lmbegin();
    auto i4 = b.lmend();
    
    for(int i=0;i3!=i4;++i3, i++)
        *i3 = i;
    
    
    cs540::Array<int, 2, 3, 4> a2 = a;
    cs540::Array<short, 2, 3, 4> c2 = a;
    a = c2;
    
    a2 = a;
    a = a; // Self-assignment must be a no-op.
    b = a; // Okay, as long as dimensions and type match exactly.
    a = c; // Member template constructor.
    
    const cs540::Array<int, 2, 3, 4> &const_ref(a);
    
    a[0][0][0] = 69;
    int i = const_ref[0][0][0]; // Okay.
    //const_ref[0][0][0] = 1; // Syntax error.
    
    i1 = a.fmbegin();
    i2 = a.fmend();
    for(int i=0;i1!=i2;++i1, i++)
        *i1 = i;

    // Iterate through in plane major order.  (Note: Normally, you would use
    // auto to simplify.)
    for (cs540::Array<int, 2, 3, 4>::FirstDimensionMajorIterator it = a.fmbegin(); it != a.fmend(); ++it) {
        std::cout << *it << std::endl;
    }
    
    // Iterate through in column major order.
    for (cs540::Array<int, 2, 3, 4>::LastDimensionMajorIterator it = a.lmbegin(); it != a.lmend(); ++it) {
        std::cout << *it << std::endl;
    }

}