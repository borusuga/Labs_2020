//
//  Prog2.hpp
//  lab2_class
//
//  Created by Alyona Borushnova on 29.09.2020.
//

#ifndef Prog2_hpp
#define Prog2_hpp

#include <stdio.h>
#include <iostream>

#endif /* Prog2_hpp */
using namespace std;
namespace prog2 {

    #define ERMSG "Incorrect input.\n"
    #define INFO "Enter a number --> "
    #define PI 3.14159265358979323846

    template <class T>
    int get_num(T &a, const char *info=INFO, const char *ermsg=ERMSG){
      cout << info;
      
      while (!(cin >> a)){
        if (cin.eof())
          return 1;
        cout << ermsg;
        cout << info;
        cin.clear();
        cin.ignore(10000, '\n');
      }
      
      return 0;
    }

    struct Point{
        long double x, y;
        
        Point(long double x, long double y) : x(x), y(y) {}
        Point() : x(0), y(0) {}

        void print_coords();
    };

    class Cardioid{
      
    private:
        long double a;
        
        Point cords;

      public:
        Cardioid() : a(0), cords(Point()) {}
        Cardioid(long double const a, long double x=0, long double y=0);
        Cardioid(long double const a, Point const cords);
//        ~Cardioid() {}; ???????????????

        int change_params(long double const a);
        int get_params(long double &a) const;
        int get_coords(Point &coords) const;
        int change_coords(Point const coords);
        char *get_equation() const;
        char *get_polar_equation() const;
        long double distance_to_center(long double const phi) const;
        Point *most_distant_dots() const;
        long double rad_of_curvature(Point &coords) const;
        long double area_of_card() const;
        long double length_of_card() const;
    };

    int dialog_chage_params(Cardioid &line);
    int dialog_get_params(Cardioid &line);
    int dialog_get_coords(Cardioid &line);
    int dialog_change_coords(Cardioid &line);
    int dialog_distance_to_center(Cardioid &line);
    int dialog_get_equation(Cardioid &line);
    int dialog_get_polar_equation(Cardioid &line);
    int dialog_area_of_card(Cardioid &line);
    int dialog_most_distant_dots(Cardioid &line);
    int dialog_rad_of_curvature(Cardioid &line);
    int dialog_length_of_card(Cardioid &line);


//    struct DialogFunc
//    {
//      int (*func) (Cardioid &line);
//      const char *info;
//    };

//    const char* dialog_menu[]  = {
//        "1. Change parameters",
//        "2. Change coordinates",
//        "3. Get parameters",
//        "4. Get coordinates",
//        "5. Get distance to center",
//        "6. Get equation",
//        "7. Get polar equation",
//        "8. Get area",
//        "9. Get the most distant dots",
//        "10. Get radius of curvature",
//        "11. Get perimeter"
//    };

    void display_menu();

//    int menu_size = 11;

    bool get_command(int &a);

    void calc(int num, Cardioid &line);
};

