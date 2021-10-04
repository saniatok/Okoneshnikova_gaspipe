#include "CCompressionStation.h"
#include <iostream>
#include "utils.h"

using namespace std;

int CompressionStation::MaxID = 0;

CompressionStation::CompressionStation()
{
    id = MaxID++;;
    name = "unknown";
    eff = 1;
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

void CompressionStation::EditCS()
{
    bool edit;
    cout << "Launch(1) or stop(0) Compression Station's department: ";
    edit = GetCorrectNumber(1);
    if (edit && workdep<dep)
    {
        ++workdep;
    }
    if (!edit && workdep>0)
    {
        --workdep;
    }
}