//
//  Array.hpp
//  CS540project3
//
//  Created by James Kizer on 4/27/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __CS540project3__Array__
#define __CS540project3__Array__

#include <iostream>

namespace cs540 {
    
    template<typename T, size_t len, size_t ... args>
    struct ArrayTypeHelper {
        typedef typename ArrayTypeHelper<T, args...>::array_t array_t[len];
        
    };
    
    template<typename T, size_t len>
    struct ArrayTypeHelper<T, len> {
        using array_t = T[len];
    };
    
//    template <typename T, size_t... dims>
//    class Array {
//        typedef T ValueType;
//        
//        
//        //save dims in a tuple for quick run time comparison
//        
//        
//    };
    
}


#endif /* defined(__CS540project3__Array__) */
