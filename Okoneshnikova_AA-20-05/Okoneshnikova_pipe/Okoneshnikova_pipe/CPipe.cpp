#include "CPipe.h"
#include <iostream>
#include "utils.h"

using namespace std;

ostream& operator << (ostream& out, const Pipe& p)
{
    out << "Pipe's diameter: " << p.diam << endl
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
    p.diam = GetCorrectNumber(0);
    cout << "Enter length of pipe: ";
    p.length = GetCorrectNumber(0.0f);
    cout << " " << endl;
    return in;
}

void Pipe::Repair()
{
    in_repair = !in_repair;
}
