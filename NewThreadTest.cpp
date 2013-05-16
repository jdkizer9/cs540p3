//
//  NewThreadTest.cpp
//  CS540project3
//
//  Created by James Kizer on 5/3/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include <iostream>
#include <string>
#include "NewThread.hpp"

void test(int i, double d, bool b){
    std::cout<<"In test: i="<<i<<", d="<<d<<", b="<<b<<std::endl;
}

void (*testfunc)(int, double, bool) = &test;

template <typename... ATs>
void TemplateTest(ATs... args){
    //argsTuple
    
    std::tuple<ATs...> argsTuple(std::make_tuple(args...));
    //testfunc(args...);
}


class LauncherTestClass {
public:
    LauncherTestClass(int i_, double j_, std::string k_):i(i_), j(j_), k(k_){}
    
    void function(int x, double y, std::string z) {
        i=x;
        j=y;
        k=z;
    }
    
    int i;
    double j;
    std::string k;
};

class EmptyLauncherTestClass {
public:
    void function(){
        
    }
};


int main() {
    
    //TemplateTest(1, 1.0, true);
    std::string s("This is my initial test string");
    LauncherTestClass testObj(1, 2.2, s);
    s = "This is my updated string";
    //ptm
    void (LauncherTestClass::* ptmf) (int, double, std::string) = &LauncherTestClass::function;
    
    //TemplateTest(3, 4.5, s);
    
    
    
    pthread_t ret = cs540::NewThread<LauncherTestClass, void, int, double, std::string> (&testObj, ptmf, 3, 4.5, s);
    
    //EmptyLauncherTestClass l1;
    //void (EmptyLauncherTestClass::* lptmf) () = &EmptyLauncherTestClass::function;

    
    //pthread_t ret = cs540::NewThread<EmptyLauncherTestClass, void>( &l1, lptmf);
    
    
}