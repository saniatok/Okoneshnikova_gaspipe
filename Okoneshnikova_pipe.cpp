#include <iostream>
#include <fstream>
using namespace std;

struct Pipe
{
    int id;
    int diam;
    float length;
    bool in_repair;
};

Pipe InputPipe()
{
    Pipe p;
    cout << "Enter diameter of pipe: ";
    cin >> p.diam;
    cout << "Enter length of pipe: ";
    cin >> p.length;
    cout << " "<< endl;
    p.id++;
    return p;
}

Pipe LoadPipe()
{
    ifstream fin;
    fin.open("data.txt", ios::in);
    Pipe p;
    fin >> p.diam;
    fin >> p.length;
    fin.close();
    p.id++;
    return p;
}

void OutputPipe(const Pipe& p)
{
    cout << "Pipe's id: " << p.id << endl
        << "Pipe's diameter: " << p.diam << endl
        << "Pipe's length: " << p.length << endl;
    if (p.in_repair)
    {
        cout << "This pipe isn't in repair. " << endl;
    }
    else
    {
        cout << "This pipe in repair." << endl;
    };
    cout << endl;
};

void SavePipe(const Pipe& p)
{
    ofstream fout;
    fout.open("data.txt", ios::out);
        fout << p.id << endl
        << p.diam << endl
        << p.length << endl
        << p.in_repair << endl;
    /*if (p.in_repair)
    {
        fout << "This pipe isn't in repair. " << endl;
    }
    else
    {
        fout << "This pipe in repair." << endl;
    };*/
    fout << endl;
};

void EditPipe(Pipe& p)
{
    p.in_repair = !p.in_repair;
};

int main()
{
    Pipe p;
    p.id = 0;
    p.diam = 0;
    p.length = 0.0;
    p.in_repair = false;
    Pipe pl = InputPipe();
    OutputPipe(pl);
    EditPipe(pl);
    SavePipe(pl);
    OutputPipe(LoadPipe());
    return 0;
}

