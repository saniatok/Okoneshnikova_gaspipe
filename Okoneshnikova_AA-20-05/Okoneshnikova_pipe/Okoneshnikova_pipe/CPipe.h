#pragma once
#include <iostream>

using namespace std;

class Pipe
{
    
public:
    int diam;
    float length;
    bool in_repair;

 
    void Repair();
   
    friend ostream& operator << (ostream& out, const Pipe& p);
    friend istream& operator >> (istream& in, Pipe& p);
};

