//
//  sumTest.cpp
//  CS540project3
//
//  Created by James Kizer on 5/3/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include <iostream>
#include "sum.hpp"




int main() {
    
    std::cout<<cs540::sum(1)<<std::endl;
    std::cout<<cs540::sum(1,2)<<std::endl;
    std::cout<<cs540::sum(1.0, 2, 3.1457, 4)<<std::endl;
    std::cout<<cs540::sum(4, 3.1457, 2, 1.0)<<std::endl;
    
}

