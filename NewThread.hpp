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
            std::cout<<"In Helper "<<N<<std::endl;
            
            //entryHelper<N-1, N, Ns...>::helper(obj);
        }
    };
    
    template <size_t... Ns>
    class entryHelper<0, Ns...> {
    public:
        static void helper(Launcher *obj) {
            //std::cout<<"In Helper 0"<<std::endl;
            obj->entryHelper2<0,Ns...>();
        }
    };
    
    template <size_t... Ns>
    void entryHelper2() {
        //((*object).*ptm)(std::get<0>(argsTuple), std::get<1>(argsTuple), std::get<2>(argsTuple));
        ((*object).*ptm)( (std::get<Ns>(argsTuple))... );
    }
    static void* entry(void *o) {
        
        Launcher *l = static_cast<Launcher *>(o);
        //std::cout<<"There are "<<(sizeof...(ATs))<<" arguments"<<std::endl;
        //if there are arguments, handle them and invoke ptm
        //otherwise, just invoke ptm
        
        //
        entryHelper<(sizeof...(ATs))-1>::helper(l);
        
        delete l;
        return nullptr;
    }
      
};
    

template <typename T, typename R, typename... ATs>
pthread_t NewThread(T *obj, R (T::*mem)(ATs...), ATs... args) {
    pthread_t retVal;
    //this will be deleted in static member function entry after mem has executed
    Launcher<T, R, ATs...> *l = new Launcher<T, R, ATs...>(obj, mem, args...);
    std::cout<<"There are "<<sizeof...(ATs)<<" arguments"<<std::endl;
    int i = pthread_create(&retVal, nullptr, Launcher<T,R,ATs...>::entry, l); assert(i==0);
    return retVal;
}
    
}

#endif /* defined(__CS540project3__NewThread__) */
