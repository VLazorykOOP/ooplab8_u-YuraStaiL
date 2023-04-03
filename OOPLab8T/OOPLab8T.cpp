// OOPLab8T.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "example.h"
int main()
{
    int r;       
    std::cout << "Lab 8 \n";
     std::cout << " Enter number task \n";
     std::cin >> r;
     switch (r)
     {
     case 1:
         task1();
         break;

     case 2:
         task2();
         break;

     case 3:
         task3();
         break;

     case 4:
         task4();
         break;
     default:
         break;
     }
    
}

