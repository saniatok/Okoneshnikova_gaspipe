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

bool IsDiamCorrect(int d)
{
    return d <= 0;
}

bool IsLengthCorrect(float l)
{
    return l <= 0;
}

Pipe InputPipe()
{
    Pipe p;
    p.id = 0;
    do
    {
        /*cin.clear();
        cin.ignore(10000, '/n');*/
        cout << "Enter diameter of pipe: ";
        cin >> p.diam;
    } while (/*cin.fail() ||*/ IsDiamCorrect(p.diam));
    do
    {
        /*cin.clear();
        cin.ignore(1000, '/n');*/
        cout << "Enter length of pipe: ";
        cin >> p.length;
    } while (/*cin.fail() ||*/ IsLengthCorrect(p.length));
    cout << " " << endl;
    return p;
}

Pipe LoadPipe()
{
    Pipe p;
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        fin >> p.id;
        fin >> p.diam;
        fin >> p.length;
        fin >> p.in_repair;
        fin.close();
    }
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
    if (fout.is_open())
    {
        fout << p.id << endl
            << p.diam << endl
            << p.length << endl
            << p.in_repair << endl;
        fout.close();
    }
};

void EditPipe(Pipe& p)
{
    p.in_repair = !p.in_repair;
};

void PrintMenu()
{
    cout << "Choose action:" << endl
         <<"1. Input pipe" << endl
         << "2. Output pipe" << endl
         << "3. Save to file" << endl
         << "4. Load from file" << endl
         << "5. Edit pipe" << endl
         << "0. Exit" << endl;
}

int main()
{
    Pipe p;
    p.id = 0;
    p.diam = 0;
    p.length = 0.0;
    p.in_repair = false;
    Pipe pl;
    while(1)
    { 
        PrintMenu();
        int i = 0;
        cout << "Your action: ";
        cin >> i;
        cout << endl;
        switch (i)
        {
        case 1:
        {
            pl = InputPipe();
            break;
        }
        case 2:
        {
            OutputPipe(pl);
            break;
        }
        case 3:
        {
            SavePipe(pl);
            break;
        }
        case 4:
        {
            pl = LoadPipe();
            break;
        }
        case 5:
        {
            EditPipe(pl);
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "wrong action" << endl;
        }
        }
    }
    return 0;
}