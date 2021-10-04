#pragma once
#include <iostream>
#include <string>

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
    //RepairCS();

   friend ostream& operator << (ostream& out, const CompressionStation& cs);
   friend istream& operator >> (istream& in, CompressionStation& cs);*/*/
};