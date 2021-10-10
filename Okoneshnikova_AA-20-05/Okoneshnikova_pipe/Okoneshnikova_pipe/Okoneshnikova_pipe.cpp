#include <iostream>
#include <fstream>
#include <vector>
#include "CPipe.h"
#include "utils.h"
#include "CCompressionStation.h"
#include <string>

using namespace std;

template <typename T>
void LoadAll(vector <T>& vector, int count, ifstream& fin)
{
    vector.resize(0);  
    vector.reserve(count);
    while (count--)
    {
        T exit;
        fin >> exit;
        vector.push_back(exit);
       /* vector.push_back(T(fin));*/
    }
}

void SaveAll(const vector <Pipe>& pipeline, const vector <CompressionStation>& compress )
{
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << pipeline.size() << endl;
        fout << compress.size() << endl;
        for (auto& exit : pipeline)
        {
            fout << exit;
        }
        for (auto& exit : compress)
        {
            fout << exit;
        }
    }
    fout.close();
};

bool Exist(size_t size)
{
    bool i = 0;
    if (size == 0)
    {
        cout  << "Add data first" << endl;
    }
    else
    { 
        i = 1;
    }
    return i;
};

int Empty(ifstream& File)   // https://www.cyberforum.ru/cpp-beginners/thread1983332.html
{
    int size = 0;   
    if (File.is_open())
    {
        File.seekg(0, std::ios::end);
        size = File.tellg();
        File.seekg(0, std::ios::beg);
        if (size == 0)
            cout << endl << "No loading data" << endl;
        File.close();
    }
    return size;
}

void EditPipe(Pipe& p)
{
    p.Repair();
};

void EditCompressionStation(CompressionStation& cs)
{
    cs.EditCS();
};

void PrintMenu()
{
    cout << endl
         << "Choose action:" << endl
         << "1. Input pipe" << endl
         << "2. Output pipes" << endl
         << "3. Edit pipe" << endl
         << "4. Save pipes and compression stations to file" << endl
         << "5. Load pipes and compression stations from file" << endl
         << "6. Input compression station" << endl
         << "7. Output compression stations" << endl
         << "8. Edit compression station" << endl
         << "0. Exit" << endl
         << "Your action: ";
}

Pipe& SelectPipe(vector<Pipe>& g)
{
    cout << "Enter pipe's index: ";
    unsigned int index = GetCorrectNumber(g.size());
    return g[index-1];
}

CompressionStation& SelectCompressionStation(vector<CompressionStation>& g)
{
    cout << "Enter Compression Station's index: ";
    unsigned int index = GetCorrectNumber(g.size());
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
        
        switch (GetCorrectNumber(8))
        {
        case 1:
        {
            cout << endl;
            Pipe pl;
            cin >> pl;
            pipeline.push_back(pl);
            break;
        }
        case 2:
        {
            cout << endl;
            if (Exist(compress.size()))
            {
                for (auto& pl : pipeline)
                    cout << pl << endl;
            }
            break;
        }
        case 4:
        {
            if (pipeline.size() != 0 || compress.size() != 0)
            {
                SaveAll(pipeline, compress);
            }
            else
            {
                cout << endl << "No saving data" << endl;
            }
            break;
        }
        case 5:
        {
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open())
            {
                int size=Empty(fin);
                if (size != 0)
                {
                    int countPipe, countCS;
                    fin >> countPipe;
                    fin >> countCS;
                    LoadAll(pipeline, countPipe, fin);
                    LoadAll(compress, countCS, fin);
                }
            }
            fin.close();
            break;
        }
        case 3:
        {
            cout << endl;
            if (Exist(compress.size()))
            {
                EditPipe(SelectPipe(pipeline));
            }
            break;
        }
        case 6:
        {
            cout << endl;
            CompressionStation css;
            cin >> css;
            compress.push_back(css);
            break;
        }
        case 8:
           {
            cout << endl;
            if (Exist(compress.size()))
            {
                EditCompressionStation(SelectCompressionStation(compress));
            }
            break;
           }
        case 7:
        {
            cout << endl;
            if (Exist(compress.size()))
            {
                for (auto& css : compress)
                    cout << css << endl;
            }
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}