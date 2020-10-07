//
//  main.cpp
//  lab2_class
//
//  Created by Alyona Borushnova on 29.09.2020.
//

#include <iostream>
#include "Prog2.hpp"

using namespace std;
using namespace prog2;
int main(){
    Cardioid line;
    int rc;
    while (static_cast<void>(display_menu()), get_command(rc)){
        calc(rc, line);
        cout << endl;
    }

    cout << "Bye!" << endl;
    return 0;
}
