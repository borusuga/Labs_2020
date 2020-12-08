//
//  main.cpp
//  Lab_4
//
//  Created by Alyona Borushnova on 28.11.2020.
//

#include <iostream>
#include "HRD.hpp"
//#include "vector.hpp"

using namespace Org;
using namespace std;
//using namespace vctr;

int main(int argc, const char * argv[]) {
    
//   Vector<int> v;
//    v.push_back(3);
//    cout << v.size();
    cout << "Do u want to:\n1. Create ur own organization\n2. Create default one\n ";
    int ch = 0;
    cin >> ch;
    string name;
    int shifr;
    Department* dp = nullptr;
    if (ch == 1){
            cout << "Enter the name of organization:\n";
            cin >> name;
            dp = new Department(name);
    }
    else{
        dp = new Department();
    }
    bool b = true;
    while (b) {
        cout << "\n--------------------------------\nChoose action:\n 0. Exit\n 1. Add slave\n 2. Add master\n 3. Change position\n 4. Fire worker\n 5. Show workers of the department\n--------------------------------\n";
        cin >> ch;
        switch (ch) {
            case 0:
                b = false;
                break;
                
            case 1:
                cout << "Enter department name where slave will work:\n";
                cin >> name;
                dp->add_slave(name, nullptr, -1);
                break;
                
            case 2:
                cout << "Enter department name where master will work:\n";
                cin >> name;
                dp->add_master(name);
                break;
                
            case 3:
                cout << "Enter with which shifr u want to lvlup:\n";
                cin >> shifr;
                dp->lvlup(shifr);
                break;
                
            case 4:
                cout << "Enter with which shifr u want to fire:\n";
                cin >> shifr;
                dp->fire(shifr);
                break;
            case 5:
                cout << "Enter department name to get the info:\n";
                cin >> name;
                dp->show_workers(name);
                break;
            default:{
                cout << "Try to choose smth else!!!\n";
                break;
            }
        }

    }
    delete dp;
    return 0;
}
