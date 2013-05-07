//
//  sum.hpp
//  CS540project3
//
//  Created by James Kizer on 4/27/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __CS540project3__sum__
#define __CS540project3__sum__

#include <iostream>

namespace cs540 {

    
    template<typename T1, typename T2, typename...Ts>
    struct SumHelper {
        using sum_t = decltype(typename SumHelper<decltype(T1()+T2()), Ts...>::sum_t());
    };
    
    template<typename T1, typename T2>
    struct SumHelper<T1, T2> {
        using sum_t = decltype(T1() + T2());
    };
    
    template <typename T>
    const T &sum(const T &v) {
        //std::cout<<"Single Base Case: "<<v<<std::endl;
        return v;
    }
    
    template <typename T1, typename T2>
    auto sum(const T1 &v1, const T2 &v2) -> typename SumHelper<T1, T2>::sum_t {
        //std::cout<<"Double Base Case: "<<v1<<" + "<<v2<<std::endl;
        return v1+v2;
    }
        
    template <typename T1, typename T2, typename... Ts>
    auto sum(const T1 &v1, const T2 &v2, const Ts &... params) -> typename SumHelper<T1, T2, Ts...>::sum_t {
        //std::cout<<"Long Case: Adding :"<<v1<<" + "<<v2<<std::endl;
        return sum((v1 + v2), params...);
    }
    
    
} //namespace CS540

#endif /* defined(__CS540project3__sum__) */
