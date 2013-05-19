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
#include <pthread.h>

namespace cs540 {
    
template <typename T, typename R, typename... ATs>
class Launcher {
private:
    T *object;
    R (T::*ptm)(ATs...);
    const std::tuple<ATs...> argsTuple;
public:

    Launcher(T *obj, R (T::*mem)(ATs...), ATs... args) : object(obj), ptm(mem),
                                        argsTuple(std::make_tuple(args...)) {}    
    
    //first case is sizeof...ATs-1
    template <size_t N, size_t... Ns>
    class entryHelper {
    public:
        static void helper(Launcher *obj) {
            entryHelper<N-1, N, Ns...>::helper(obj);
        }
    };
    
    //this is the terminating case where there are one or more arguments
    template <size_t... Ns>
    class entryHelper<0, Ns...> {
    public:
        static void helper(Launcher *obj) {
            obj->entryHelper2<0,Ns...>();
        }
    };
    
    //this handles case where there are no arguments
    template <size_t... Ns>
    class entryHelper<(size_t)-1, Ns...> {
    public:
        static void helper(Launcher *obj) {
            static_assert((sizeof...(ATs) == 0), "Programming error");
            ((*(obj->object)).*(obj->ptm))();
        }
    };
    
    template <size_t... Ns>
    void entryHelper2() {
        ((*object).*ptm)( (std::get<Ns>(argsTuple))... );
    }
    static void* entry(void *o) {
        
        Launcher *l = static_cast<Launcher *>(o);
        entryHelper<(sizeof...(ATs))-1>::helper(l);
        
        //delete Launcher object created by NewThread
        delete l;
        return nullptr;
    }
      
};
    

template <typename T, typename R, typename... ATs>
pthread_t NewThread(T *obj, R (T::*mem)(ATs...), ATs... args) {
    pthread_t retVal;
    //this will be deleted in static member function entry after mem has executed
    Launcher<T, R, ATs...> *l = new Launcher<T, R, ATs...>(obj, mem, args...);
    int i = pthread_create(&retVal, nullptr, Launcher<T,R,ATs...>::entry, l); assert(i==0);
    return retVal;
}
    
}

#endif /* defined(__CS540project3__NewThread__) */
