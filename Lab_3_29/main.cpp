//
//  main.cpp
//  Lab_3_29
//
//  Created by Alyona Borushnova on 13.10.2020.
//

#include <iostream>
#include "Charset.hpp"

int main(int argc, const char * argv[]) {

    ThirdLab3::CharSet c1(4);
    ThirdLab3::CharSet c2(3);
    ThirdLab3::CharSet c3("hjkbhjbj");
    ThirdLab3::CharSet c4('h');
    c2 += 'a';
//    ThirdLab3::CharSet c3 = c3.Subtraction(c1, c2);
//    ThirdLab3::CharSet c3(10);
//    ThirdLab3::CharSet c4;
//    std::cin >> c4;
//    char symbol[1] = {'n'};
//    bool b = c4.Existence(symbol, c4);
//    ThirdLab3::CharSet * f = c1.Subtraction(c2);
//    ThirdLab3::CharSet * a = c1.intersection(c2);
    //char c = "s";
//    ThirdLab3::CharSet * f = c1.Addition(c2);
    ThirdLab3::CharSet nw = c1 - c2;
//    nw.Injection(symbol);
//    std::cout << nw;

    return 0;
    
}
