//
//  Prog1list.hpp
//  lab1
//
//  Created by Alyona Borushnova on 18.09.2020.
//  Copyright © 2020 Alyona Borushnova. All rights reserved.
//

#ifndef Prog1list_hpp
#define Prog1list_hpp

#include <stdio.h>
#include <iostream>

#endif /* Prog1list_hpp */
using namespace std;

namespace Prog1list{
    // структура для задания строки матрицы

    struct Elems
    {
        int col;
        double num;
        Elems* next;
        
        Elems(int col, double num, Elems* next) : col(col), num(num), next(next)
        {}
        
    };

    struct Line
    {
        int ln; // номер строки
        int numcol; //количество элементов в ряде
        Elems* columns = nullptr;
        Line* next;
        
        Line(int ln, int numcol, Elems* columns, Line* next) : ln(ln), numcol(numcol), columns(columns), next(next)
        {}
            
    };


    // шаблон функций ввода одного значения
    template <class T>
    int getNum(T &a, const char *msg)
    {
        if (msg != nullptr){
            cout << msg ;
        }
        cin >> a;
        if (!cin.good())    // обнаружена ошибка ввода или конец файла
            return -1;
        return 1;
    }

    // прототипы функций
    Line* input1(int &,int &); // ввод матрицы
    void output(const char *msg, Line * a, int n, int m); // вывод матрицы
    void output_res(double * res, int n); // вывод матрицы
    Line *erase(Line *&a, int n); // освобождение занятой памяти
    int res(Line * a, int n, double *& res); // вычисление главного результата
    double f(Line * a); //нахождение максимального или первого ненулевого
    double average(Line * a); // вычисление главного результата
    void insert_in_line(Line * tmp_ln, int j,double num, bool & b); // вставка в строку
}

