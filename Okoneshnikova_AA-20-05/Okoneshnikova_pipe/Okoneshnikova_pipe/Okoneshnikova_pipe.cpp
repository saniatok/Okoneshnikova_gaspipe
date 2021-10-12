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
        T data;
        fin >> data;
        vector.push_back(data);
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
        for (auto& data : pipeline)
        {
            fout << data;
        }
        for (auto& data : compress)
        {
            fout << data;
        }
    }
    fout.close();
};

bool Exist(size_t size)
{
    if (size == 0)
    {
        cout  << "Add data first" << endl;
        return false;
    }
    return true;
};

//int Empty(ifstream& File)   // https://www.cyberforum.ru/cpp-beginners/thread1983332.html
//{
//    int size = 0;   
//    if (File.is_open())
//    {
//        File.seekg(0, std::ios::end);
//        size = File.tellg();
//        //File.seekg(0, std::ios::beg);
//        if (size == 0)
//            cout << endl << "No loading data" << endl;
//        File.close();
//    }
//    return size;
//}

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
         << "2. Edit pipe" << endl
         << "3. Output pipes and compression stations" << endl
         << "4. Save pipes and compression stations to file" << endl
         << "5. Load pipes and compression stations from file" << endl
         << "6. Input compression station" << endl
         << "7. Edit compression station" << endl
         << "0. Exit" << endl
         << "Your action: ";
}

Pipe& SelectPipe(vector<Pipe>& g)
{
    cout << "Enter pipe's index: ";
    unsigned int index = GetCorrectSize(g.size());
    return g[index];
}

CompressionStation& SelectCompressionStation(vector<CompressionStation>& g)
{
    cout << "Enter Compression Station's index: ";
    unsigned int index = GetCorrectSize(g.size());
    return g[index];
}

int main()
{
    vector <CompressionStation> compress;
    vector <Pipe> pipeline;

    while(1)
    { 
        PrintMenu();
        
        switch (GetCorrectNumber(7))
        {
        case 1:
        {
            cout << endl;
            Pipe pl;
            cin >> pl;
            pipeline.push_back(pl);
            break;
        }
        case 3:
        {
            cout << endl;
            if (pipeline.size() != 0 || compress.size() != 0)
            {
                for (auto& pl : pipeline)
                    cout << pl << endl;
                cout << endl;
                for (auto& css : compress)
                    cout << css << endl;
            }
            else
                cout << "No data to output" << endl;
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
                /*int size=Empty(fin);
                if (size != 0)
                {*/
                    int countPipe, countCS;
                    fin >> countPipe;
                    fin >> countCS;
                    LoadAll(pipeline, countPipe, fin);
                    LoadAll(compress, countCS, fin);
                /*}*/
            }
            fin.close();
            break;
        }
        case 2:
        {
            cout << endl;
            if (Exist(pipeline.size()))
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
        case 7:
        {
            cout << endl;
            if (Exist(compress.size()))
            {
                EditCompressionStation(SelectCompressionStation(compress));
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