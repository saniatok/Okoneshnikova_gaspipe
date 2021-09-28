#include <iostream>
#include <fstream>
#include <vector>
#include "CPipe.h"
#include "utils.h"
#include "CompressionStation.h"

using namespace std;

Pipe LoadPipe(ifstream& fin)
{
    Pipe p;
        fin >> p.diam;
        fin >> p.length;
        fin >> p.in_repair;
    return p;
}

CompressionStation LoadCompressionStation(ifstream& fin)
{
    CompressionStation cs;
        fin >> cs.name;
        fin >> cs.dep;
        fin >> cs.workdep;
        fin >> cs.eff;
    return css;
}

void SavePipe(ofstream& fout, const Pipe& p)
{
    fout
            << p.diam << endl
            << p.length << endl
            << p.in_repair << endl;
};

void SaveCompressionStation(ofstream& fout, const CompressionStation& cs)
{
    fout
        << cs.name << endl
        << cs.dep; << endl
        << cs.workdep << endl
        << cs.eff << endl;
};

void EditPipe(Pipe& p)
{
    p.Repair();
};

int GetCorrectNumberC(int min, int max)
{
    int x;
    while ((cin >> x).fail() || x<min || x> max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Your action (" << min << "-" << max << "): ";
    }
    return x;
}

void PrintMenu()
{
    cout << "Choose action:" << endl
         << "1. Input pipe" << endl
         << "2. Output pipes and compression stations" << endl
         << "3. Save to file" << endl
         << "4. Load from file" << endl
         << "5. Edit pipe" << endl
         << "6. Input compression station" << endl
         << "7. Edit compression station" << endl
         << "0. Exit" << endl
         << "Your action: ";

}

Pipe& SelectPipe(vector<Pipe>& g)
{
    cout << "Enter pipe's index: ";
    unsigned int index = GetCorrectNumberC(0u, g.size());
    return g[index-1];
}


int main()
{
    vector <CompressionStation> compress;
    vector <Pipe> pipeline;
    CompressionStation css;
    Pipe pl;
    while(1)
    { 
        PrintMenu();
        
        switch (GetCorrectNumberC(0,6))
        {
        case 1:
        {
            cout << " " << endl;
            Pipe pl;
            cin >> pl;
            pipeline.push_back(pl);
            break;
        }
        case 2:
        {
            cout << " " << endl;
            for (auto& pl: pipeline)
            cout << pl << endl;
            for (auto& css: compress)
            cout << css << endl;
            break;
        }
        case 3:
        {
            ofstream fout;
            fout.open("data.txt", ios::out);
            if (fout.is_open())
            {
                fout << pipeline.size() << endl;
                for (Pipe pl : pipeline)
                    SavePipe(fout, pl);
                fout.close();
            }
            break;
        }
        case 4:
        {
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open())
            {
                int count;
                fin >> count;
                pipeline.reserve(count);
                while (count--);
                    pipeline.push_back(LoadPipe(fin));
                fin.close();
            }
            break;
        }
        case 5:
        {
            EditPipe(SelectPipe(pipeline));
            break;
        }
        case 6:
        {
            cout << " " << endl;
            CompressionStation css;
            cin >> css;
            compress.push_back(css);
            break;
        }
     /*   case 7:
        {
            cout << " " << endl;
            CompressionStation css;
            cin >> css;
            compress.push_back(css);
            break;
        }*/
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}