//
//  NewThreadTest.cpp
//  CS540project3
//
//  Created by James Kizer on 5/3/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include <iostream>
#include "NewThread.hpp"

void test(int i, double d, bool b){
    std::cout<<"In test: i="<<i<<", d="<<d<<", b="<<b<<std::endl;
}

void (*testfunc)(int, double, bool) = &test;

template <typename... ATs>
void TemplateTest(ATs... args){
    testfunc(args...);
}

int main() {
    
    TemplateTest(1, 1.0, true);
    
}