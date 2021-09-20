#include <iostream>
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
    p.id++;
    return p;
    cout << endl;
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
    OutputPipe(pl);
    return 0;
}

