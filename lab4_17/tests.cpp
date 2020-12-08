//
//  tests.cpp
//  Lab_4
//
//  Created by Alyona Borushnova on 03.12.2020.
//

#include <stdio.h>
#include <iostream>
#include "HRD.hpp"

using namespace Org;
int testing(int argc, const char * argv[]) {
    Worker* w = new Worker("fullname", "birthdate", "position", "education", 300);
    Worker w1 = Worker("fullname", "birthdate", "position", "education", 300);

    Department* dp = new Department("first");
    Master* m = new Master("fullname", "birthdate", "position", "education", 300, dp);
    std::cout << w1.get_type() << std::endl << w->get_type() << std::endl << m->get_type();
    std::cout << "Hello, World!\n";
    return 0;
}
