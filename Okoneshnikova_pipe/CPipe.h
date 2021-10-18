#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Pipe
{
    int id;

public:
    static int MaxID;
    int diam;
    float length;
    bool in_repair;

    int getId() const;
    int getDiam() const;
    double getLength() const;
    bool getRepair() const;

    Pipe();
    Pipe(std::ifstream& in);
    void Repair();

    friend ostream& operator << (ostream& out, const Pipe& p);
    friend istream& operator >> (istream& in, Pipe& p);
    friend ofstream& operator << (ofstream& fout, const Pipe& p);
    friend ifstream& operator >> (ifstream& fin, Pipe& p);
};

