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
#include <assert.h>

namespace cs540 {
    
    class OutOfRange : public std::exception {
        const char* what() const noexcept {return "Index out of range.\n";}
    };
    
    template <typename T, size_t... dims>
    class Array {
    public:
        typedef T ValueType;
        static const size_t numDims;
        static const size_t maxDims[Array::numDims];
        
    public:
        
        class Iterator : public std::iterator<std::forward_iterator_tag, T>
        {
        public:
            
            Iterator(const Iterator &it) {
                a = it.a;
                for(size_t i=0; i<Array::numDims; i++){
                    d[i] = it.d[i];
                }
                endFlag = it.endFlag;
            }
            
            Iterator(const Array *a_) : d{0}, a(const_cast<Array*>(a_)), endFlag(false) {}
            
            
            Iterator &operator=(const Iterator &it) {
                a = it.a;
                for(size_t i=0; i<Array::numDims; i++){
                    d[i] = it.d[i];
                }
                endFlag = it.endFlag;
                return *this;
            }
            
            
            
            
            //equality operators
            bool operator==(const Iterator &i2) {
                
                //check to see if they point to the same array
                if (a != i2.a)
                    return false;
                
                //check for the end
                if (endFlag && i2.endFlag)
                    return true;
                
                for(size_t i=0; i<Array::numDims; i++){
                    if(d[i] != i2.d[i])
                        return false;
                }
                return true;
            }
            
            bool operator!=(const Iterator &i2) {
                return !( *this == i2);
            }
            
            
            //need to use the dimensions stored in an array
            //to access the item
            Array::ValueType &operator*() {
                assert(a != nullptr);
                return a->get(d);
            }
                       
        protected:
        
            //0 is most significant
            //last dim is least significant
            //last dim = Array::numDims-1
            //for First Dimension, we actually access last dim first
            size_t d[Array::numDims];
            Array *a;
            bool endFlag;
        private:
            virtual void increment() = 0;
            
        };
        class FirstDimensionMajorIterator : public Iterator
        {
        public:
            
            FirstDimensionMajorIterator() : Iterator(nullptr) {};
            
            FirstDimensionMajorIterator(const Array *a_, bool end=false) : Iterator(a_) {
                if(end)
                {
                    for(size_t i=0; i<Array::numDims; i++) {
                        this->d[i] = maxDims[i]-1;
                    }
                    this->d[Array::numDims-1]++;
                    this->endFlag = true;
                }
            }
            
            FirstDimensionMajorIterator &operator++() {
                increment();
                return *this;
            }
            
            FirstDimensionMajorIterator operator++(int) {
                auto tmp = *this;
                increment();
                return tmp;
            }
        private:
            void increment() {
                size_t i;
                for(i=0; i<Array::numDims; i++) {
                    assert(maxDims[i] > this->d[i]);
                    
                    size_t index = Array::numDims-(i+1);
                    
                    this->d[index]++;
                    //if this dimension has not reached max, increment over
                    if (this->d[index] < maxDims[index])
                        return;
                    //otherwise, this dimension is maxed out, set to 0 and increment next dimension
                    else
                        this->d[index]=0;
                    
                }
                this->d[Array::numDims-1]++;
                this->endFlag = true;
            }
            
        };
        
        class LastDimensionMajorIterator : public Iterator
        {
        public:
            
            LastDimensionMajorIterator() : Iterator(nullptr) {};
            
            LastDimensionMajorIterator(const Array *a_, bool end=false) : Iterator(a_) {
                if(end)
                {
                    for(size_t i=0; i<Array::numDims; i++) {
                        this->d[i] = maxDims[i]-1;
                    }
                    this->d[0]++;
                    this->endFlag = true;
                }
            }
            
            LastDimensionMajorIterator &operator++() {
                increment();
                return *this;
            }
            
            LastDimensionMajorIterator operator++(int) {
                auto tmp = *this;
                increment();
                return tmp;                
            }
        private:
            void increment() {
                size_t i;
                for(i=0; i<Array::numDims; i++) {
                    assert(maxDims[i] > this->d[i]);
                    
                    this->d[i]++;
                    //if this dimension has not reached max, increment over
                    if (this->d[i] < maxDims[i])
                        return;
                    //otherwise, this dimension is maxed out, set to 0 and increment next dimension
                    else
                        this->d[i]=0;
                    
                }
                this->d[0]++;
                this->endFlag = true;
                
                //assert(i<Array::numDims);
            }
            
        };
        
        
    private:
        //Array Helper Classes
        template<typename U, size_t len, size_t ... args>
        class ArrayHelper {
            
        public:
            static_assert(len>0, "Dimension Out of Range: must be positive");
            
            //typedef typename ArrayTypeHelper<U, args...>::array_t U_A;
            //need to define entry type for [] return type
            using entry_t = ArrayHelper<U, args...>;
            
            //U_A a_[len];
            ArrayHelper<U, args...> a_[len];
            const size_t length;
            const size_t level;
            
            //default constructor
            ArrayHelper () : length(len), level(a_[0].level+1) {};
            
            //assignment operator
            ArrayHelper &operator=(const ArrayHelper &other) {
                
                //if length != other.length, this should never happen
                if (length != other.length)
                    assert(false);
                    throw OutOfRange();
                
                for (int i=0; i<len; i++)
                    a_[i] = other.a_[i];
                
                return *this;
            }
            
            //assignment operator
            template <typename V>
            ArrayHelper &operator=(const ArrayHelper<V, len, args...> &other) {
                
                //if length != other.length, this should never happen
                if (length != other.length)
                    assert(false);
                    throw OutOfRange();
                
                for (int i=0; i<len; i++)
                    a_[i] = other.a_[i];
                
                return *this;
            }
            
            entry_t &operator[](const size_t i) {
                //throw
                if(i>=len)
                    throw OutOfRange();
                return a_[i];
            }
            
            const entry_t &operator[](const size_t i) const {
                //throw
                if(i>=len)
                    throw OutOfRange();
                
                return a_[i];
            }
            
            //top level must access entry 0
            //next level must access entry 1
            //last level must access Array::numDims - 1 
            T &get(const size_t d[Array::numDims]) {
                return a_[ d[(Array::numDims-1)-level] ].get(d);
            }
            
        };
        
        //Base ArrayHelper Class
        template<typename U, size_t len>
        class ArrayHelper<U, len> {
            
            public:
            
            static_assert(len>0, "Dimension Out of Range: must be positive");
            
            using entry_t = U;
            U a_[len];
            const size_t length;
            const size_t level;
            
            //default constructor
            ArrayHelper () : length(len), level(0) {};
            
            //assignment operator
            ArrayHelper &operator=(const ArrayHelper &other) {
                
                //if length != other.length, this should never happen
                if (length != other.length)
                    assert(false);
                    throw OutOfRange();
                
                for (int i=0; i<len; i++)
                    a_[i] = other.a_[i];
                
                 return *this;
            }
            
            template <typename V>
            ArrayHelper &operator=(const ArrayHelper<V, len> &other) {
                
                //if length != other.length, this should never happen
                if (length != other.length)
                    assert(false);
                    throw OutOfRange();
                
                for (int i=0; i<len; i++)
                    //setting type U to type V
                    a_[i] = other.a_[i];
                
                return *this;
            }

            U &operator[](const size_t i) {
                //throw
                if(i>=len)
                    throw OutOfRange();
                return a_[i];
            }
            
            const U &operator[](const size_t i) const {
                //throw
                if(i>=len)
                    throw OutOfRange();
                return a_[i];
            }
            
            //for base, level will be 0. However, this must access the
            //last element in d
            U &get(const size_t d[Array::numDims]) {
                return a_[ d[(Array::numDims-1)-level] ];
            }
        };
    public:
        //default constructor
        Array ()  {};
        
        //copy constructor
        template <typename U>
        Array (const Array<U, dims...> &other) {
            
            //this will only be invoked if dimensions are identical
            
            //reimplement using iterators
            //we know they are the same dimenstions
            auto i1b = this->fmbegin();
            auto i1e = this->fmend();
            auto i2b = other.fmbegin();
            for(;i1b != i1e;) {
                *i1b = *i2b;
                ++i1b;
                ++i2b;
            }
            
        }
        
        Array (const Array &other)  {
            
            if(&other == this)
                return;
            
            //reimplement using iterators
            //we know they are the same dimenstions
            
            auto i1b = this->fmbegin();
            auto i1e = this->fmend();
            auto i2b = other.fmbegin();
            for(;i1b != i1e;) {
                *i1b = *i2b;
                ++i1b;
                ++i2b;
            }
            
        }
        
        Array &operator=(const Array &other) {
            
            if(&other == this)
                return *this;
            
            //reimplement using iterators
            //we know they are the same dimenstions
            
            auto i1b = this->fmbegin();
            auto i1e = this->fmend();
            auto i2b = other.fmbegin();
            for(;i1b != i1e;) {
                *i1b = *i2b;
                ++i1b;
                ++i2b;
            }
            return *this;
        }
        
        template <typename U>
        Array &operator=(const Array<U, dims...> &other) {
            
            if((void*)&other == (void*)this)
                return *this;
            
            auto i1b = this->fmbegin();
            auto i1e = this->fmend();
            auto i2b = other.fmbegin();
            for(;i1b != i1e;) {
                *i1b = *i2b;
                ++i1b;
                ++i2b;
            }
            return *this;
        }

    private:
        typedef typename ArrayHelper<T, dims...>::entry_t EntryType;
        typedef const typename ArrayHelper<T, dims...>::entry_t ConstEntryType;

        //a_ stores the array in a recursive helper class
        ArrayHelper<T, dims...> a_;
        
        T &get(const size_t d[Array::numDims]) {
            return a_.get(d);
        }
        
    public:
        EntryType &operator[](const size_t i) {
            return a_[i];
        }
        
        const EntryType &operator[](const size_t i) const {
            return a_[i];
        }
    
        FirstDimensionMajorIterator fmbegin() const {
            //Array *myArray = this;
            return FirstDimensionMajorIterator(this);
        }
        
        FirstDimensionMajorIterator fmend() const {
            return FirstDimensionMajorIterator(this, true);
        }
        
        LastDimensionMajorIterator lmbegin() const {
            //Array *myArray = this;
            return LastDimensionMajorIterator(this);
        }
        
        LastDimensionMajorIterator lmend() const {
            return LastDimensionMajorIterator(this, true);
        }

        
    };
    
}

template <typename T, size_t... dims>
const size_t cs540::Array<T, dims...>::numDims = sizeof...(dims);

template <typename T, size_t... dims>
const size_t cs540::Array<T, dims...>::maxDims[Array::numDims] = {dims...};


#endif /* defined(__CS540project3__Array__) */
