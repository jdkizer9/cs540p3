//
//  ArrayTest.cpp
//  CS540project3
//
//  Created by James Kizer on 5/3/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include <iostream>
#include "Array.hpp"

typedef typename cs540::ArrayTypeHelper<double, 2>::array_t ARR;
typedef ARR ARR2[2];


int main() {
    typename cs540::ArrayTypeHelper<double, 2>::array_t array1;
    
    typename cs540::ArrayTypeHelper<int, 2, 2>::array_t array2;
    
    typename cs540::ArrayTypeHelper<int, 2, 2, 2>::array_t array3;
    
    ARR2 i;
    
    
    //typename CS540::ArrayTypeHelper<int, 2, 2, 2>::array_t array3;
    
    array1[0] = 0;
    array1[1] = 1;
    
    size_t len = sizeof(array3);

}