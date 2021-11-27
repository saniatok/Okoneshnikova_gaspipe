#pragma once
#include <iostream>
#include <unordered_map>

template <typename T>
void swapValues(T& value1, T& value2)
{
    T temp = value1;
    value1 = value2;
    value2 = temp;
}

template <typename T>
T GetCorrectNumber(T max)
{
    T x;
    while ((std::cin >> x).fail() || x<0 || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Try again, please: ";
    }
    return x;
}

template <typename T>
int findMaxID(unordered_map<int, T>& map)
{
    int MaxID = 0;
    for (const auto& data : map)
    {
        if (data.second.getId() > MaxID)
        {
            MaxID = data.second.getId();
        }
    }
    return MaxID;
};

