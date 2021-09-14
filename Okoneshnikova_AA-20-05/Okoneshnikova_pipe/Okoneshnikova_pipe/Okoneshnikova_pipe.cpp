// Okoneshnikova_pipe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
struct Pipe
{
    int id;
    int d;
};

int main()
{
    Pipe p;
    p.id = 0;
    p.d = 0;
   std::cout << "¬ведите диаметр трубы";
   std::cin >> p.d;
   std::cout << p.d;

}

