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
    id.reserve(map.size());
    for (const auto& it : map)
    {
        id.push_back(it.first);
    }
    for (int i : id)
    {
        map.erase(i);
    }
    while (count--)
    {
        T val(fin);
        map.insert(pair<int, T>(val.getId(), val));
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
        for (const auto& p : pipeline)
        {
            fout << p.second;
        }
        for (const auto& css : compress)
        {
            fout << css.second;
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

//void EditPipe(Pipe& p)
//{
//    p.Repair();
//};

//void EditCompressionStation(CompressionStation& cs)
//{
//    cs.EditCS();
//};

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
         << "9. Delete compression station" << endl
         << "10. Find pipe by diam" << endl
         << "11. Find pipe by needing in repair " << endl
         << "12. Find compression station by name" << endl
         << "13. Find compression station by percent of not working departments " << endl
         << "0. Exit" << endl
         << "Your action: ";
}

void EditPipe(unordered_map<int, Pipe>& g)
{
    cout << "Enter pipe's index: ";
    int id = GetCorrectNumber(findMaxID(g));
    unordered_map<int, Pipe>::iterator it = g.find(id);
    if (it != g.end())
    {
        it->second.Repair();
    }
}

void EditCompressionStation(unordered_map<int, CompressionStation>& g)
{
    cout << "Enter Compression Station's index: ";
    int id = GetCorrectNumber(findMaxID(g));
    unordered_map<int, CompressionStation>::iterator it = g.find(id);
    if (it != g.end())
    {
        it->second.EditCS();
    }
}

template<typename P, typename T>
using Filter = bool(*)(const P& p, T Param, bool paramb);

bool CheckByName(const CompressionStation& cs, string name, bool paramb)
{
    return cs.getName() == name && paramb || cs.getName() != name && !paramb;
}
bool CheckByDisDep(const CompressionStation& cs, float ddep, bool paramb)
{
    return cs.getDisDep() >= ddep && paramb || (cs.getEff() < ddep) && !paramb ;
}
bool CheckByDiam(const Pipe& p, float diam, bool paramb)
{
    return p.getDiam() >= diam && paramb || p.getDiam() < diam && !paramb;
}
bool CheckByRepair(const Pipe& p, bool repair, bool paramb=true)
{
    return (!p.getRepair() && paramb)|| (p.getRepair() && !paramb);
}

template<typename P, typename T>
vector<int> FindObjectsByFilter(const unordered_map<int, P>& map, Filter<P, T> f, T Param, bool paramb=true)
{
    vector <int> res;
    int i = 0;
    res.reserve(map.size());
    for (const auto& it : map)
    {
        if (f(it.second, Param, paramb))
        {
            res.push_back(it.first);
        }
    }
    return res;
}

int main()
{
    unordered_map <int, CompressionStation> compress;
    unordered_map <int, Pipe> pipeline;

    while(1)
    { 
        PrintMenu();
        
        switch (GetCorrectNumber(13))
        {
        case 1:
        {
            cout << endl;
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
            string file;
            cout << endl << "Enter name of file: ";
            cin >> file;
            fin.open(file + ".txt", ios::out);
            if (fin.is_open())
            {
                    int countPipe, countCS;
                    fin >> countPipe;
                    fin >> countCS;
                    LoadAll(pipeline, countPipe, fin);
                    LoadAll(compress, countCS, fin);
            }
            fin.close();
            Pipe::MaxID = findMaxID(pipeline);
            CompressionStation::MaxID = findMaxID(compress);
            break;
        }
        case 2:
        {
            cout << endl;
            if (Exist(pipeline.size()))
            {
                EditPipe(pipeline);
            }
            break;
        }
        case 6:
        {
            cout << endl;
            compress.insert(pair <int, CompressionStation> (CompressionStation::MaxID+1,CompressionStation()));
            break;
        }
        case 7:
        {
            cout << endl;
            if (Exist(compress.size()))
            {
                EditCompressionStation(compress);
            }
            break;
        }
        case 8:
        {
            if (pipeline.size() != 0)
            {
                cout << "Enter Pipe's index: ";
                int id = GetCorrectNumber(findMaxID(pipeline));
                if (pipeline.find(id) != pipeline.end())
                {
                    pipeline.erase(id);
                }
                else
                {
                    cout << "Id is not correct" << endl;
                }
            }
            break;
        }
        case 9:
        {
            if (compress.size() != 0)
            {
                cout << "Enter Compression Station's index: ";
                int id = GetCorrectNumber(findMaxID(compress));
                if (compress.find(id) != compress.end())
                {
                    compress.erase(id);
                }
                else
                {
                    cout << "Id is not correct" << endl;
                }
            }
            break;
        }
        case 10:
        {
            float diam = 1420;

            
            break;
        }
        case 11:
        {
            if (pipeline.size() != 0)
                cout << "Find pipes in repair(0) or not in repair(1)";
            bool repair = GetCorrectNumber(1);
            for (int& i: FindObjectsByFilter(pipeline, CheckByRepair, repair))
            {
                cout << pipeline[i];
            }
            break;
        }
        case 12:
        {
           
            break;
        }
        case 13:
        {
            
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