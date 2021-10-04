#include "CPipe.h"
#include <iostream>
#include "utils.h"

using namespace std;

int Pipe::MaxID = 0;

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
    cout << "Enter length of pipe: ";
    p.length = GetCorrectNumber(10000.0f);
    cout << " " << endl;
    return in;
}

Pipe::Pipe()
{
    id = MaxID++;
    diam = 1420;
    length=18.3;
}

void Pipe::Repair()
{
    in_repair = !in_repair;
}
