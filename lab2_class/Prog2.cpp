//
//  Prog2.cpp
//  lab2_class
//
//  Created by Alyona Borushnova on 29.09.2020.
//

#include "Prog2.hpp"
#include <cmath>
#include <iostream>
#include <string.h>
//#include <stdio.h>
//#include <cstring>

namespace prog2{

Cardioid::Cardioid(long double const a, long double x, long double y){
    this->a = a;
    this->cords = Point(x, y);
}

Cardioid::Cardioid(long double const a, Point const coords){
    this->a = a;
    this->cords = coords;
}
  

void Point::print_coords(){
    std::cout << "(" << x << ", " << y << ")";
}



int Cardioid::change_params(long double const a){
    this->a = a;
    return 0;
}

int Cardioid::change_coords(Point const coords)
{
  this->cords = coords;
  return 0;
}

int Cardioid::get_params(long double &a) const{
    a = this->a;
    return 0;
}

int Cardioid::get_coords(Point &coords) const{
    coords = this->cords;
    return 0;
}


long double Cardioid::distance_to_center(long double const phi) const{
    return a*(1+cos(phi));
}

Point *Cardioid::most_distant_dots() const{
    Point *end = new Point[2];
    end[0] = Point(3*a/4+cords.x, 3*sqrt(3)*a/4+cords.y);
    end[1] = Point(3*a/4+cords.x, -3*sqrt(3)*a/4+cords.y);
    return end;
}

char *Cardioid::get_equation() const{
    long double a;
    Point coord;
    get_params(a);
    get_coords(coord);
      
    int l;
    char buf[200];

    if (a == 0){
        l = sprintf(buf, "dot with coordinates(%.2Lf, %.2Lf)", coord.x, coord.y);
    }
    else if ((coord.x == 0) && (coord.y == 0))
    {
      l = sprintf(buf, "(x^2+y^2)^2 - 2*%.2Lf*(x^2+y^2) = %.2Lf^2*y^2", a, a);
    }
    else if (coord.x != 0)
    {
      l = sprintf(buf, "((x+%.2Lf)^2+y^2)^2 - 2*%.2Lf*((x+%.2Lf)^2+y^2) = %.2Lf^2*y^2", coord.x, a, coord.x, a);
    }
    else
    {
        l = sprintf(buf, "(x^2+(y+%.2Lf)^2)^2 - 2*%.2Lf*(x^2+y+%.2Lf)^2) = %.2Lf^2*y^2", coord.y, a, coord.y, a);
    }
    buf[++l] = '\0';
    char *end = new char[l];
    end[0] = '\0';
    strcat(end, buf);
//    strcat(end, l, buf);
    
    return end;
  }

    char *Cardioid::get_polar_equation() const{
        long double a;
        Point coord;
        get_params(a);
        get_coords(coord);
          
        int l;
        char buf[200];

        if (a == 0){
            l = sprintf(buf, "dot with coordinates(%.2Lf, %.2Lf)", coord.x, coord.y);
        }
        else
        {
            l = sprintf(buf, "p = a(1 + cos(phi) with center in (%.2Lf, %.2Lf) ", coord.x, coord.y);
        }
        buf[++l] = '\0';
        char *end = new char[l];
        end[0] = '\0';
        strcat(end, buf);
    //    strcat(end, l, buf);
        
        return end;
    }


    long double Cardioid::area_of_card() const{
      return 3*PI*pow(a, 2)/2;
    }

    long double Cardioid::length_of_card() const{
        return 8*a;
    }

    long double Cardioid::rad_of_curvature(Point &coords) const{
        long double cos_phi = coords.x/sqrt(pow(coords.x, 2) + pow(coords.y, 2));
        return pow(2, 1.5)*a*pow(1+cos_phi, 0.5)/3;
    }

  int dialog_chage_params(Cardioid &line)
  {
    long double a;
    if (get_num(a, "Enter new a --> "))
        return 1;
    line.change_params(a);
    return 0;
  }

  int dialog_get_params(Cardioid &line)
  {
    long double a;
    line.get_params(a);
    std::cout << "a: " << a << std::endl;
    return 0;
  }

  int dialog_get_coords(Cardioid &line)
  {
    Point cd;
    line.get_coords(cd);
    std::cout << "coords: ";
    cd.print_coords();
    std::cout << std::endl;
    return 0;
  }

    int dialog_change_coords(Cardioid &line){
        long double x,y;
        get_num(x,"Enter x coord --> ");
        get_num(y,"Enter y coord --> ");

        Point cd(x,y);
        line.change_coords(cd);
        return 0;
    }

    int dialog_distance_to_center(Cardioid &line){
        long double phi;
        get_num(phi,"Enter phi angle --> ");
        std::cout << "Distant to polar center is: " << line.distance_to_center(phi) << std::endl;
        return 0;
    }

    int dialog_get_equation(Cardioid &line){
        char *t = line.get_equation();
        std::cout << "Equation: " << t << std::endl;
        delete[] t;
        return 0;
    }

    int dialog_get_polar_equation(Cardioid &line){
        char *t = line.get_polar_equation();
        std::cout << "Equation: " << t << std::endl;
        delete[] t;
        return 0;
    }

    int dialog_area_of_card(Cardioid &line){
        std::cout << "Area: " << line.area_of_card() << std::endl;
        return 0;
    }

    int dialog_rad_of_curvature(Cardioid &line){
        long double x,y;
        get_num(x,"Enter x coord --> ");
        get_num(y,"Enter y coord --> ");
        Point cd = Point(x, y);
        std::cout << "Radius of curvatured: " << line.rad_of_curvature(cd) << std::endl;
        return 0;
    }

    int dialog_length_of_card(Cardioid &line){
        std::cout << "Perimeter: " << line.length_of_card() << std::endl;
        return 0;
    }
  
    int dialog_most_distant_dots(Cardioid &line){
        Point *cd = line.most_distant_dots();
        printf("The most distant to polar center are: (%.2Lf, %.2Lf) and (%.2Lf, %.2Lf)", cd[0].x, cd[0].y, cd[1].x, cd[1].y);
        std::cout << std::endl;
        delete[] cd;
        return 0;
    }
  
  void display_menu()
  {
      const char* dialog_menu[]  = {
          "1. Change parameters",
          "2. Change coordinates",
          "3. Get parameters",
          "4. Get coordinates",
          "5. Get distance to center",
          "6. Get equation",
          "7. Get polar equation",
          "8. Get area",
          "9. Get the most distant dots",
          "10. Get radius of curvature",
          "11. Get perimeter"
      };
    for (int i=0; i<11; i++)
    {
      std::cout << dialog_menu[i] << std::endl;
    }
  }

bool get_command(int &a){
    const char *err = "";
    int n = 0;
    n=0;
    cout << err;
    //err = ERMSG;
    if (get_num(n, "Enter command --> ")){
        return false;
    }
    if (n <= 0 || n > 11)
        return false;
    a = n;
    return true;
}

void calc(int num, Cardioid &line){
    switch (num) {
        case 1:
            dialog_chage_params(line);
            break;
        case 2:
            dialog_change_coords(line);
            break;
        case 3:
            dialog_get_params(line);
            break;
        case 4:
            dialog_get_coords(line);
            break;
        case 5:
            dialog_distance_to_center(line);
            break;
        case 6:
            dialog_get_equation(line);
            break;
        case 7:
            dialog_get_polar_equation(line);
            break;
        case 8:
            dialog_area_of_card(line);
            break;
        case 9:
            dialog_most_distant_dots(line);
            break;
        case 10:
            dialog_rad_of_curvature(line);
            break;
        case 11:
            dialog_length_of_card(line);
            break;
        default:
            cout << "Hmm..." << endl;
            break;
    }
}
};
