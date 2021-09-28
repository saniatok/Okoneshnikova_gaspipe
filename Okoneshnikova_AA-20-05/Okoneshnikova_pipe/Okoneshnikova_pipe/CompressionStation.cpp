#include "CompressionStation.h"
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

//CompressionStation::RepairCS()
//{
//    workdep
//}

ostream& operator<<(ostream& out, const CompressionStation& cs)
{
    out << "Compression Station's id: " << cs.id << endl
        << "Compression Station's name: " << cs.name << endl
        << "Compression Station's departments: " << cs.dep << endl
        << "Compression Station's working departments: " << cs.workdep << endl
        << "Compression Station's efficiency: " << cs.eff << endl;
    return out;
	// TODO: insert return statement here
}

istream& operator>>(istream& in, CompressionStation& cs)
{

    cout << "Enter name of Compression Station: ";
    cin >> cs.name;
    cout << "Enter number of Compression Station's departments: ";
    cs.dep = GetCorrectNumber(0);
    cout << "Enter number of Compression Station's working departments: ";
    cs.workdep = GetCorrectNumber(0);
    cout << "Enter efficieny of Compression Station: ";
    cs.eff = GetCorrectNumberC(0,1);

    cout << " " << endl;
    return in;
    // TODO: insert return statement here
}
