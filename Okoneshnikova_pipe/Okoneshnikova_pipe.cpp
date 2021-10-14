#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "CPipe.h"
#include "utils.h"
#include "CCompressionStation.h"
#include <string>

using namespace std;

/*FIX THIS*/
template <typename T>
void LoadAll(unordered_map <int, T>& map, int count, ifstream& fin)
{
    vector <int> id;
    /*vector.resize(0);*/  
    id.reserve(map.size());
    while (map.size()--)
    {
        T data;
        fin >> data;
        vector.push_back(data);
    }
}

void SaveAll(const unordered_map < int, Pipe>& pipeline, const unordered_map <int, CompressionStation>& compress )
{
    ofstream fout;
    string file;
    cout << endl << "Enter name of file: ";
    cin >> file;
    fout.open(file+".txt", ios::out);
    if (fout.is_open())
    {
        fout << pipeline.size() << endl;
        fout << compress.size() << endl;
        for (const auto& data : pipeline)
        {
            fout << data.second;
        }
        for (const auto& data : compress)
        {
            fout << data.second;
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
         << "8. Delete pipe" << endl
         << "9. Delete cimoression station" << endl
         << "0. Exit" << endl
         << "Your action: ";
}

Pipe& SelectPipe(unordered_map<int, Pipe>& g)
{
    cout << "Enter pipe's index: ";
    unsigned int index = GetCorrectSize(g.size());
    return g[index];
}

CompressionStation& SelectCompressionStation(unordered_map<int, CompressionStation>& g)
{
    cout << "Enter Compression Station's index: ";
    unsigned int index = GetCorrectSize(g.size());
    return g[index];
}

int main()
{
    unordered_map <int, CompressionStation> compress;
    unordered_map <int, Pipe> pipeline;

    while(1)
    { 
        PrintMenu();
        
        switch (GetCorrectNumber(7))
        {
        case 1:
        {
            cout << endl;
           /* Pipe pl;
            cin >> pl;*/
            pipeline.insert(pair <int, Pipe> (Pipe::MaxID+1, Pipe()));
            break;
        }
        case 3:
        {
            cout << endl;
            if (pipeline.size() != 0 || compress.size() != 0)
            {
                for (const pair <int, Pipe>& pl:pipeline )
                    cout << pl.second << endl;
                cout << endl;
                for (const pair <int, CompressionStation>& css : compress)
                    cout << css.second << endl;
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
            /*CompressionStation css;
            cin >> css;
            compress.push_back(css);*/
            compress.insert(pair <int, CompressionStation> (CompressionStation::MaxID+1,CompressionStation()));
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
        case 8:
        {

        }
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}