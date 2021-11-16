#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CompressionStation
{
    int id;
    string name;
    int dep;
    int workdep;
    float eff;
public:
    static int MaxID;


    int getId() const;
    string getName() const;
    int getDep() const;
    int getWorkDep() const;
    float getEff() const;
    float getDisDep() const;

    CompressionStation();
    CompressionStation(std::ifstream& in);
    void EditCS();

    friend ostream& operator << (ostream& out, const CompressionStation& cs);
    friend istream& operator >> (istream& in, CompressionStation& cs); 
    friend ofstream& operator << (ofstream& fout, const CompressionStation& cs);
    friend ifstream& operator >> (ifstream& fin, CompressionStation& cs);
 };
