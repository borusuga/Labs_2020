//
//  Prog1list.cpp
//  lab1
//
//  Created by Alyona Borushnova on 18.09.2020.
//  Copyright © 2020 Alyona Borushnova. All rights reserved.
//

#include "Prog1list.hpp"
#include <iostream>

namespace Prog1list {
// функция ввода
Line* input1(int &rn, int &rm)
{
    const char *pr = ""; // будущее сообщение об ошибке
    int n, m;    // количество строк матрицы
    Line* lines = nullptr; // массив списков
    
    // сначала вводим количество строк
    do{
        cout << pr << endl;
        pr = "You are wrong; repeat please!";
        if (getNum(n, "Enter number of lines: --> ") < 0) // обнаружена ошибка ввода или конец файла
            return nullptr;
    } while (n < 1);
    
    pr = "";
    
    // сначала вводим количество столбцов
    do {
        cout << pr << std::endl;
        pr = "You are wrong; repeat please!";
        if (getNum(m, "Enter max number of cols: --> ") < 0) // обнаружена ошибка ввода или конец файла
            return nullptr;
    } while (m < 1);

    pr = "";
    rn = n;
    rm = m;

    int boo;
    while ((getNum(boo, "Continue yes(1):no(-1)?\t-->\t" ) == 1) && (boo == 1)) {
        int i = 0, j = 0;
        double num = 0;
        // ввод номера строки
        do {
            cout << pr << std::endl;
            pr = "You are wrong; repeat please!";
            if (getNum(i,  "Enter number of line: --> ") < 0) // обнаружена ошибка ввода или конец файла
                return nullptr;
        } while ((i < 1) || (i > n));
        pr = "";
        // ввод номера столбца
        do {
            cout << pr << std::endl;
            pr = "You are wrong; repeat please!";
            if (getNum(j, "Enter number of column: --> ") < 0) // обнаружена ошибка ввода или конец файла
                return nullptr;
        } while ((j < 1) || (j > m));
        pr = "";
        // ввод числа
        cout << pr << std::endl;
        if (getNum(num, "Enter number: --> ") < 0) // обнаружена ошибка ввода или конец файла
            return nullptr;
        
        // есть координаты элемента и элемент
        
        if (lines == nullptr){           // проверяем, есть ли массив строк
            lines = new Line(i, 1, new Elems(j, num, nullptr), nullptr);
        }
        else    // если уже есть ссылка на список строк
        {
            Line* tmp_ln = lines;
            bool b = true;

            while ((tmp_ln->next != nullptr) && b) {
                if (tmp_ln->ln == i){   //если нашлась строка с таким же номером
                    //начинаем вставлять элемент в строку
                    insert_in_line(tmp_ln, j, num, b);
                }
                if ((tmp_ln->next->ln > i) && (b)){ //надо вставить строку между строками
                    Line *ptr = new Line(i, 1, new Elems(j, num, nullptr), tmp_ln->next);
                    tmp_ln->next = ptr;
                    b = false;
                }
                
                if (b){ // надо вставить строку в конец
                    tmp_ln->next = new Line(i, 1, new Elems(j, num, nullptr), nullptr);
                }
                    
                tmp_ln = tmp_ln->next;
            }
            
            
            if (b){         // попадём сюда, если всего одна строка
                if(tmp_ln->ln < i){     // попадём сюда, если всего одна строка и она меньше вставляемой
                    tmp_ln->next = new Line(i, 1, new Elems(j, num, nullptr), nullptr);
                }
                else if (tmp_ln->ln > i) {      // попадём сюда, если всего одна строка и она больше вставляемой
                    Line * ptr = new Line(i, 1, new Elems(j, num, nullptr), tmp_ln);
                    lines = ptr;
                }
                else {      // попадём сюда, если всего одна строка и она равна вставляемой
                    insert_in_line(tmp_ln, j, num, b);
                }
            }
        }
    }
    return lines;
}

void insert_in_line(Line * tmp_ln, int j, double num, bool & b){ //1/////////////////
    Elems* tmp_el = tmp_ln->columns; //1/////////////////
    if(tmp_el->next == nullptr){    //в строке один элемент
        if (tmp_el->col < j){   // столбец первого меньше вставляемого
            tmp_el->next = new Elems(j, num, nullptr);
            ++tmp_ln->numcol;
            b = false;
        }
        else{   // столбец первого больше вставляемого (вставка на первую позицию)
            Elems *ptr = new Elems(j, num, tmp_el);
            tmp_ln->columns = ptr;
            b = false;
            ++tmp_ln->numcol;
        }
    }
    while ((tmp_el->next != nullptr) && b) { // в строке несколько элементов
        if (tmp_el->next->col > j){
            Elems *ptr = new Elems(j, num, tmp_el->next);
            tmp_el->next = ptr;
            b = false;
            ++tmp_ln->numcol;
        }
        tmp_el = tmp_el->next;
    }
    if (b) { //если цикл пройден и надо вставить в конец
        tmp_el->next = new Elems(j, num, nullptr);
        ++tmp_ln->numcol;
        b = false;
    }
}



// функция вывода
void output(const char *msg, Line* a, int n, int m)
{
    int i;
    std::cout << msg << ":\n";
    if (a != NULL)
        for (i = 1; i <= n; ++i){
            int j = 1;
            Line* Lptr = a;
            while ((Lptr != NULL) && (Lptr->ln != i ))
                Lptr = Lptr->next;
            if (Lptr != NULL)
            {
                Elems* ptr = Lptr->columns;
                while ((ptr != NULL) || (j <= m))
                {
                    if (ptr != NULL)
                    {
                        while ((ptr->col > j) && (j <= m))
                        {
                            j += 1;
                            std::cout << "0 ";
                        }
                        if ((j <= m) && (ptr->col >= j))
                        {
                            j += 1;
                            std::cout << ptr->num << " ";
                        }
                        ptr = ptr->next;

                    }
                    else
                        while (j <= m)
                        {
                            j += 1;
                            std::cout << "0 ";
                        }
                }
            }
            else
                while (j <= m)
                {
                    j += 1;
                    std::cout << "0 ";
                }

            std::cout << std::endl;
        }
    else
        for (i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                std::cout << "0 ";
            std::cout << std::endl;
        }
    
}


double average(Line * tmp_ln){
    double av = 0;
    Elems* tmp = tmp_ln->columns;
    while (tmp != nullptr) {
        av += tmp->num;
        tmp = tmp->next;
    }
    return av/tmp_ln->numcol;
}

double f(Line * tmp_ln){
    if (tmp_ln->columns->col != 1)
        return tmp_ln->columns->num;
    double f = 0;
    Elems* tmp = tmp_ln->columns;
    while (tmp != nullptr) {
        if(tmp->col == 1)
            f = tmp->num;
        else if (tmp->num > f)
            f = tmp->num;
        tmp = tmp->next;
    }
    return f;
}

int res(Line * lines, int n, double *& res){
    Line* tmp = lines;
    try{
        res = new double[n];
    }
    catch (std::bad_alloc &ba){
        std::cout << "------ too many cols in matrix: " << ba.what() << std::endl;
        return 1;
    }
    int i = 0;
    while (tmp != nullptr) {
        if ((i + 1) == tmp->ln){
            double av = average(tmp), fr = f(tmp);
            double r = av/fr;
            res[i] = r;
            tmp = tmp->next;
        }
        else{
            res[i] = 0;
        }
        i++;
    }
    return 1;
}

void output_res(double * res, int n){
    cout << "result is: ";
    for (int i = 0; i < n; ++i) {
        cout << res[i] << "\t";
    }
    cout << endl;
}

Line *erase(Line *&a, int n){ // освобождение занятой памяти
    while (a != nullptr){
        Line * tmp_ln = a;
        while (a->columns != nullptr) {
            Elems * tmp_el = a->columns;
            a->columns = tmp_el->next;
            delete tmp_el;
        }
        a = a->next;
        delete tmp_ln;
        
    }
    delete a;
    return nullptr;
}
}
