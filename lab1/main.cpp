//
//  main.cpp
//  lab1
//
//  Created by Alyona Borushnova on 16.09.2020.
//  Copyright © 2020 Alyona Borushnova. All rights reserved.
//

#include <iostream>
#include "Prog1.hpp"
#include "Prog1list.hpp"

using namespace Prog1list;
using namespace std;
int main()
{
    Line *arr = nullptr; // исходный массив
    int m, n; // количество строк и элементов в матрице

    arr = input1(n, m); // ввод матрицы

    output("Matrix", arr, n, m);
    double *b = nullptr;
    res(arr, n, b);
    output_res(b, n);
    erase(arr, n); // освобождение памяти
    delete [] b;
    return 0;
}
