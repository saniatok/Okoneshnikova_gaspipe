#include "CPipe.h"
#include <iostream>
#include "utils.h"
#include <fstream>

using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe()
{
    this->id = ++MaxID;
    cout  << "Enter diameter of pipe: ";
    this->diam = GetCorrectNumber(10000); 
    cout << "Enter diameter of length: ";
    this->length = GetCorrectNumber(100.0f);
    this->in_repair = true;
}

Pipe::Pipe(std::ifstream& in)
{
    in >> this->id;
    in >> this->diam;
    in >> this->length;
    in >> this->in_repair;
}

ostream& operator << (ostream& out, const Pipe& p)
{
    out << "Pipe's id: " << p.id << endl
        << "Pipe's diameter: " << p.diam << endl
        << "Pipe's length: " << p.length << endl;
    if (p.in_repair)
    {
        out << "This pipe isn't in repair. " << endl;
    }
    else
    {
        out << "This pipe in repair." << endl;
    }
    return out;
}

istream& operator >> (istream& in, Pipe& p)
{
    cout << "Enter diameter of pipe: ";
    p.diam = GetCorrectNumber(10000);
    cout << "Enter diameter of pipe: ";
    p.length = GetCorrectNumber(100.0f);
    cout << endl;
    return in;
}

ofstream& operator<<(ofstream& fout, const Pipe& p)
{
    fout << endl
         << p.id << endl 
         << p.diam << endl 
         << p.length << endl 
         << p.in_repair << endl;
    return fout;
}

ifstream& operator>>(ifstream& fin, Pipe& p)
{
    fin >> p.id;
    fin >> p.diam;
    fin >> p.length;
    fin >> p.in_repair;
    return fin;
}

int Pipe::getId() const
{
    return id;
}

int Pipe::getDiam() const
{
    return diam;
}

double Pipe::getLength() const
{
    return length;
}

bool Pipe::getRepair() const
{
    return in_repair;
}


void Pipe::Repair()
{
    in_repair = !in_repair;
}
