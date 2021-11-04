#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "CPipe.h"
#include "utils.h"
#include "CCompressionStation.h"
#include <string>

using namespace std;

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

template <typename T>
void Erase(unordered_map <int, T>& map)
{
    cout << endl << "Enter index: ";
    int id = GetCorrectNumber(findMaxID(map));
    if (map.find(id) != map.end())
    {
        map.erase(id);
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
    return cs.getDisDep() >= ddep && paramb || cs.getDisDep() < ddep && !paramb;
}
bool CheckByDiam(const Pipe& p, float diam, bool paramb)
{
    return p.getDiam() >= diam && paramb || p.getDiam() < diam && !paramb;
}
bool CheckByRepair(const Pipe& p, bool repair, bool paramb = true)
{
    return (!p.getRepair() && repair) || (p.getRepair() && !repair);
}

template<typename P, typename T>
vector<int> FindObjectsByFilter(const unordered_map<int, P>& map, Filter<P, T> f, T Param, bool paramb = true)
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
         << "13. Find compression station by percent of working departments " << endl
         << "14. Batch editing of pipes "<< endl
         << "0. Exit" << endl
         << "Your action: ";
}

int main()
{
    unordered_map <int, CompressionStation> compress;
    unordered_map <int, Pipe> pipeline;

    while(1)
    { 
        PrintMenu();
        
        switch (GetCorrectNumber(14))
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
                Erase(pipeline);
            }
            break;
        }
        case 9:
        {
            if (compress.size() != 0)
            {
                Erase(compress);
            }
            break;
        }
        case 10:
        {
            if (pipeline.size() != 0)
            {
                cout << endl << "Find pipes whose diameter is more than : ";
                float diam = GetCorrectNumber(10000);
                for (int& i : FindObjectsByFilter(pipeline, CheckByDiam, diam))
                {
                    cout << endl << pipeline[i];
                }
            }
            else
                cout << endl << "Add data first" << endl;
            break;
        }
        case 11:
        {
            if (pipeline.size() != 0)
            {
                cout << endl << "Find pipes in repair(1) or not in repair(0): ";
                bool repair = GetCorrectNumber(1);
                for (int& i: FindObjectsByFilter(pipeline, CheckByRepair, repair))
                {
                cout << endl << pipeline[i];
                }
            }
            else
                cout << endl << "Add data first" << endl;
            break;
        }
        case 12:
        {
            if (compress.size() != 0)
            {
                cout << endl << "Find compression station with name: ";
                string name;
                cin.ignore(10000, '\n');
                getline(cin, name);
                for (int& i : FindObjectsByFilter(compress, CheckByName, name))
                {
                    cout << endl << compress[i];
                }
            }
            else
                cout << endl << "Add data first" << endl;
            break;
        }
        case 13:
        {
            if (compress.size() != 0)
            {
                cout << endl << "Find compression station with percent of not working departments: ";
                float ddep = GetCorrectNumber(100);
                for (int& i : FindObjectsByFilter(compress, CheckByDisDep, ddep))
                {
                    cout << endl << compress[i];
                }
            }
            else 
                cout << endl << "Add data first" << endl;
            break;
        } 
        case 14:
        {
            if (pipeline.size() != 0)
            {
                    cout << endl << "Choose action: " << endl
                        << "1. Edit chosen pipes " << endl
                        << "2. Edit all pipes in repair" << endl
                        << "3. Edit all pipes not in repair" << endl
                        << "0. Exit batch editing of pipes" << endl
                        << "Your action: ";
                    switch (GetCorrectNumber(3))
                    {
                        case 1:
                        {
                            vector <int> id_vector;
                            bool editing = true;
                            while (editing)
                            {
                                cout << endl << "Enter id of editing pipe or 0 for stop editing: ";
                                int id = GetCorrectNumber(findMaxID(pipeline));
                                if (id != 0)
                                {
                                    if (pipeline.find(id) != pipeline.end())
                                    {
                                        id_vector.push_back(id);
                                    }
                                    else
                                    {
                                        cout << "Id is not correct" << endl;
                                    }
                                }
                                else
                                {
                                    editing = false;
                                }
                            }
                            for (int& i : id_vector)
                            {
                                pipeline[i].Repair();
                            }
                            break;
                        }
                    case 2:
                    {
                        for (int& i : FindObjectsByFilter(pipeline, CheckByRepair, true))
                        {
                            pipeline[i].Repair();
                        }
                        break;
                    }
                    case 3:
                    {
                        for (int& i : FindObjectsByFilter(pipeline, CheckByRepair, false))
                        {
                            pipeline[i].Repair();
                        }
                        break;
                    }
                }
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