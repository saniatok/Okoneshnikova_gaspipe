#include "CCompressionStation.h"
#include <iostream>
#include "utils.h"
#include <string>
#include <fstream>

using namespace std;

int CompressionStation::MaxID = 0;

CompressionStation::CompressionStation()
{
    this->id = ++MaxID;
}

CompressionStation::CompressionStation(std::ifstream& in)
{
    in >> this->id;
    in.ignore();
    getline(in, this->name);
    in >> this->dep;
    in >> this->workdep;
    in >> this->eff;
}

ostream& operator<<(ostream& out, const CompressionStation& cs)
{
    out << "Compression Station's id: " << cs.id << endl
        << "Compression Station's name: " << cs.name << endl
        << "Compression Station's departments: " << cs.dep << endl
        << "Compression Station's working departments: " << cs.workdep << endl
        << "Compression Station's efficiency: " << cs.eff << endl;
    return out;
}

istream& operator>>(istream& in, CompressionStation& cs)
{
    
    cout << "Enter name of Compression Station: ";
    cin.ignore(10000, '\n');
    getline(cin, cs.name);
    cout << "Enter number of Compression Station's departments: ";
    cs.dep = GetCorrectNumber(1000);
    cout << "Enter number of Compression Station's working departments: ";
    cs.workdep = GetCorrectNumber(cs.dep);
    cout << "Enter efficieny of Compression Station(0-1): ";
    cs.eff = GetCorrectNumber(1.0f);
    cout << " " << endl;
    return in;
}

ofstream& operator<<(ofstream& fout, const CompressionStation& cs)
{
    fout << endl
        << cs.id << endl
        << cs.name << endl 
        << cs.dep << endl
        << cs.workdep << endl
        << cs.eff << endl;
    return fout;
}

ifstream& operator>>(ifstream& fin, CompressionStation& cs)
{
    fin >> cs.id;
    fin.clear();
    fin.ignore(10000, '\n');
    getline(fin, cs.name);
    fin >> cs.dep;
    fin >> cs.workdep;
    fin >> cs.eff;
    return fin;
}

int CompressionStation::getId() const
{
    return id;
}

string CompressionStation::getName() const
{
    return name;
}

int CompressionStation::getDep() const
{
    return dep;
}

int CompressionStation::getWorkDep() const
{
    return workdep;
}

float CompressionStation::getEff() const
{
    return eff;
}

float CompressionStation::getDisDep() const
{
    return 100-(workdep * (1.0 / dep) * 100);
}

void CompressionStation::EditCS()
{
    cout << "Launch(1) or stop(0) Compression Station's department: ";
    switch (GetCorrectNumber(1))
    {
    case 1:
    {
        if (workdep < dep)
        {
            ++workdep;
        }
        else
        {
            cout << endl << "excess of permissible count of departments" << endl;
        }
        break;
    }
    case 0:
    {
        if (workdep > 0)
        {
            --workdep;
        }
        else
        {
            cout << endl << "count of working departments can't be less than 0" << endl;
        }
        break;
    }
    }
}