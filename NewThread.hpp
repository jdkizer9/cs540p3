//
//  NewThread.hpp
//  CS540project3
//
//  Created by James Kizer on 4/27/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __CS540project3__NewThread__
#define __CS540project3__NewThread__

#include <iostream>

template <typename T, typename R, typename... ATs>
pthread_t NewThread(T *obj, R (T::*mem)(ATs...), ATs... args);

// 1) need to generate a thread entry point that invokes obj->mem(args...)
// 2) can we create a class that contains an object, member function pointer and another object to contain the variadic arguments?
// 2a) is there a way to store args such that it can be reproduced and used as a argument pack again?
// 3) try std::tuple

//template <typename T, typename R, typename... ATs>
//void entry<T,R,ATs...>(){
//    
//}

//obj->mem(args...);

#endif /* defined(__CS540project3__NewThread__) */
