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
    
    template <typename T, size_t... dims>
    class Array {
    public:
        
        //Array Helper Classes
        template<typename U, size_t len, size_t ... args>
        struct ArrayHelper {
            
            static_assert(len>0, "Dimension Out of Range: must be positive");
            
            //typedef typename ArrayTypeHelper<U, args...>::array_t U_A;
            //need to define entry type for [] return type
            using entry_t = ArrayHelper<U, args...>;
            
            //U_A a_[len];
            ArrayHelper<U, args...> a_[len];
            size_t length;
            
            //default constructor
            ArrayHelper () : length(len){};
            
            //assignment operator
            ArrayHelper &operator=(const ArrayHelper &other) {
                
                //if length != other.length, throw
                for (int i=0; i<len; i++)
                    a_[i] = other.a_[i];
                
                return *this;
            }
            
            //assignment operator
            template <typename V>
            ArrayHelper &operator=(const ArrayHelper<V, len, args...> &other) {
                
                //if length != other.length, throw
                for (int i=0; i<len; i++)
                    a_[i] = other.a_[i];
                
                return *this;
            }
            
            //copy constructor
//            ArrayHelper (const ArrayHelper &other) : length(len){
//            
//            }
            
            entry_t &operator[](const size_t i) {
                //throw
                //if(i<0 || i<=len)
                return a_[i];
            }
            
        };
        
        template<typename U, size_t len>
        struct ArrayHelper<U, len> {
            
            static_assert(len>0, "Dimension Out of Range: must be positive");
            
            using entry_t = U;
            U a_[len];
            size_t length;
            
            //default constructor
            ArrayHelper () : length(len) {};
            
            //assignment operator
            ArrayHelper &operator=(const ArrayHelper &other) {
                
                //if length != other.length, throw
                for (int i=0; i<len; i++)
                    a_[i] = other.a_[i];
                
                 return *this;
            }
            
            template <typename V>
            ArrayHelper &operator=(const ArrayHelper<V, len> &other) {
                
                //if length != other.length, throw
                for (int i=0; i<len; i++)
                    //setting type U to type V
                    a_[i] = other.a_[i];
                
                return *this;
            }
            
            //copy constructor
//            ArrayHelper (const ArrayHelper &other) : length(len) {
//                
//            }
            
            U &operator[](const size_t i) {
                //throw
                //if(i<0 || i<=len)
                return a_[i];
            }
        };
        
        //default constructor
        Array () {};
        
        //copy constructor
        Array (const Array &other) {
            
            //this should kick off the assignment operators in
            //the helper class
            a_ = other.a_;
            
        }
        
        template <typename U>
        Array (const Array<U, dims...> &other) {
            
            //this will only be invoked if dimensions are identical
            
            //this should kick off the assignment operators in
            //the helper class
            a_ = other.a_;
            
        }
        
        typedef T ValueType;
        typedef typename ArrayHelper<T, dims...>::entry_t EntryType;
        
        //a_ stores the array in a recursive helper class
        ArrayHelper<T, dims...> a_;
        
        EntryType &operator[](const size_t i) {
            return a_[i];
        }
        
        
    };
    
}


#endif /* defined(__CS540project3__Array__) */
