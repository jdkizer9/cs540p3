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
#include <assert.h>

namespace cs540 {
    
template <typename T, typename R, typename... ATs>
class Launcher {
    
public:
    
    Launcher(T *obj, R (T::*mem)(ATs...), ATs... args) : object(obj), ptm(mem),
                                        argsTuple(std::make_tuple(args...)) {}
    
    void entry(void *o) {
        assert(o == this);
        
        ((*object).*ptm)(std::get<0>(argsTuple), std::get<1>(argsTuple), std::get<2>(argsTuple));
        //(*object).*ptm();
    }
    
    T *object;
    R (T::*ptm)(ATs...);
    std::tuple<ATs...> argsTuple;
};
    
template <typename T, typename R>
class Launcher<T,R> {
        
    public:
        
        Launcher(T *obj, R (T::*mem)()) : object(obj), ptm(mem) {}
        
        void entry(void *o) {
            assert(o == this);
            
            //(*object).*ptm(std::get<0>(argsTuple), std::get<1>(argsTuple), std::get<2>(argsTuple));
            ((*object).*ptm)();
        }
        
        T *object;
        R (T::*ptm)();
    };
template <typename T, typename R>
    pthread_t NewThread( T *obj, R (T::*mem)() ) {
        Launcher<T, R> l(obj, mem);
        
        l.entry(&l);
    }

template <typename T, typename R, typename... ATs>
pthread_t NewThread(T *obj, R (T::*mem)(ATs...), ATs... args) {
    Launcher<T, R, ATs...> l(obj, mem, args...);
    
    l.entry(&l);
}
    


// 1) need to generate a thread entry point that invokes obj->mem(args...)
// 2) can we create a class that contains an object, member function pointer and another object to contain the variadic arguments?
// 2a) is there a way to store args such that it can be reproduced and used as a argument pack again?
// 3) try std::tuple
//  can use std::tie (args...) = tuple?

//template <typename T, typename R, typename... ATs>
//void entry<T,R,ATs...>(){
//    
//}

//obj->mem(args...);
    
}

#endif /* defined(__CS540project3__NewThread__) */
