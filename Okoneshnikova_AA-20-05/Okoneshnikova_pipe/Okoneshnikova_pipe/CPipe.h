#pragma once
#include <iostream>

using namespace std;

class Pipe
{
    int id;

public:
    static int MaxID;
    int diam;
    float length;
    bool in_repair;

    Pipe();
    void Repair();
   
    friend ostream& operator << (ostream& out, const Pipe& p);
    friend istream& operator >> (istream& in, Pipe& p);
};

