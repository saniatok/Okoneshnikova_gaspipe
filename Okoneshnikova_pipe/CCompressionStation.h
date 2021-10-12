#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CompressionStation
{
    int id;

public:
    static int MaxID;
    string name;
    int dep;
    int workdep;
    float eff;

    CompressionStation();
    void EditCS();

    friend ostream& operator << (ostream& out, const CompressionStation& cs);
    friend istream& operator >> (istream& in, CompressionStation& cs); 
    friend ofstream& operator << (ofstream& fout, const CompressionStation& cs);
    friend ifstream& operator >> (ifstream& fin, CompressionStation& cs);
 };
