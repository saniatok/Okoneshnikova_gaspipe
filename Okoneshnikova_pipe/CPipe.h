#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Pipe
{
    int id;
    int diam;
    float length;
    bool in_repair;

public:
    static int MaxID;

    int getId() const;
    int getDiam() const;
    double getLength() const;
    bool getRepair() const;
    bool getPressure() const;
    bool getPerformance() const;

    Pipe();
    Pipe(ifstream& in);
    void Repair();

    friend ostream& operator << (ostream& out, const Pipe& p);
    friend istream& operator >> (istream& in, Pipe& p);
    friend ofstream& operator << (ofstream& fout, const Pipe& p);
    friend ifstream& operator >> (ifstream& fin, Pipe& p);
};

