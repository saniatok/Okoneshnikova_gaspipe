#pragma once
#include <iostream>

template <typename T>
T GetCorrectNumber(T min)
{
    T x;
    while ((std::cin >> x).fail() || x <= min)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Enter length of pipe: ";
    }
    return x;
}