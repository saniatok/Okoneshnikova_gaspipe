#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "CPipe.h"
#include "utils.h"
#include "CCompressionStation.h"
#include <string>
#include "CNetwork.h"

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
    cin.ignore(10000, '\n');
    getline(cin, file);
    fout.open(file+".txt", ios::out);
    if (fout.is_open())
    {
        fout << pipeline.size() << endl;
        fout << compress.size() << endl;
        for (const auto& p : pipeline)
        {
            fout << p.second;
        }
        for (const auto& cs : compress)
        {
            fout << cs.second;
        }
    }
    else
    {
        cout << endl << "No file with this name" << endl;
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
    else
    {
        cout << endl << "This ID is not exist";
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

void InputNetwork(unordered_map < int, Pipe>& pipeline, unordered_map <int, CompressionStation>& compress, CNetwork net)
{
    cout << endl << "Compression Stations to choose:" << endl;
    for (auto& cs : compress)
    {
        cout << cs.first << endl;
    }
    cout << endl << "Enter id of first compression station or 0 for exit: ";
    int Id_FCS = GetCorrectNumber(findMaxID(compress));
    cout << endl << "Enter id of second compression station or 0 for exit: ";
    int Id_SCS = GetCorrectNumber(findMaxID(compress));
    if (Id_FCS != 0 && Id_SCS != 0)
    {
        cout << endl << "Pipes to choose:" << endl;
        for (auto& p : pipeline)
        {
            if (p.second.getRepair() && !net.HasEdge(p.first))
            {
                cout << p.first << endl;
            }
        }
        cout << endl << "Enter id of pipe or 0 to exit: ";
        int Id_P = GetCorrectNumber(findMaxID(pipeline));
        if (Id_P != 0)
        {
            auto it = pipeline.find(Id_P);
            if (it->second.getRepair() && !net.HasEdge(it->first))
            {
                net.Connect(Id_FCS, Id_SCS, Id_P, it->second.getPressure(), it->second.getPerformance()/*, is_one_step*/);
            }
            else
            {
                cout << "This pipe is in repair now, choose another pipe" << endl;
            }
        }
        else
        {
            cout << "No available pipes";
        }
    }
}

void PrintTopologicalSort(unordered_map <int, CompressionStation>& compress, CNetwork net)
{
    auto t_sort = net.TopologicalSort();
    cout << endl << "h" << "    " << "CS id" << endl;
    for (unsigned int i = 0; i < t_sort.size(); i++)
    {
        cout << i + 1 << "    " << t_sort[i] << endl;
    }
    if (!t_sort.empty())
    {
        for (int i : t_sort)
        {
            cout << compress[i] << endl;
        }
    }
    else
    {
        cout << "Graph has cycle" << endl;
    }
}

void SaveNet(CNetwork net)
{
    ofstream fout;
    string file;
    cout << endl << "Enter name of file: ";
    cin.ignore(10000, '\n');
    getline(cin, file);
    fout.open(file + ".txt", ios::out);
    if (fout.is_open())
    {
        fout << net;
    }
    else
    {
        cout << endl << "No file with this name" << endl;
    }
    fout.close();
}

void LoadNet(CNetwork net)
{
    ifstream fin;
    string file;
    cout << endl << "Enter name of file: ";
    cin.ignore(10000, '\n');
    getline(cin, file);
    fin.open(file + ".txt", ios::out);
    if (fin.is_open())
    {
        fin >> net;
    }
    else
    {
        cout << endl << "No file with this name" << endl;
    }
    fin.close();
}

void PrintMenu()
{
    cout << endl
         << "MAIN MENU" << endl
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
         << "15. Gas transportation Network"<< endl
         << "0. Exit" << endl
         << "Your action: ";
}

void PrintNetwork()
{
    cout << endl 
        <<"NETWORK MENU"<< endl
        <<"Choose action:"<< endl
        << "1. Input gas transmission network  " << endl
        << "2. Output gas transmission network " << endl
        << "3. Topological sort of network " << endl
        << "4. Save network to file" << endl
        << "5. Load network from file" << endl
        << "6. Delete vertex from network" << endl
        << "7. Delete edge fron network" << endl
        << "0. Exit from Network" << endl
        << "Your action: ";
}
void PrintEditingPipe()
{ 
   cout << endl
        << "BATCH EDITING OF PIPES MENU " << endl
        << "Choose action: " << endl
        << "1. Edit chosen pipes " << endl
        << "2. Edit all pipes in repair" << endl
        << "3. Edit all pipes not in repair" << endl
        << "0. Exit batch editing of pipes" << endl
        << "Your action: ";
}

int main()
{
    unordered_map <int, CompressionStation> compress;
    unordered_map <int, Pipe> pipeline;
    CNetwork net;
    while(1)
    { 
        PrintMenu();
        
        switch (GetCorrectNumber(21))
        {
        case 1:
        {
            cout << endl;
            Pipe p;
            cin >> p;
            pipeline.insert(pair <int, Pipe> (p.getId(), p ));
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
            cin.ignore(10000, '\n');
            getline(cin, file);
            fin.open(file + ".txt", ios::out);
            if (fin.is_open())
            {
                int countPipe, countCS;
                fin >> countPipe;
                fin >> countCS;
                LoadAll(pipeline, countPipe, fin);
                LoadAll(compress, countCS, fin);
            }
            else
            {
                cout << endl << "No file with this name" << endl;
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
            CompressionStation cs;
            cin >> cs;
            compress.insert(pair <int, CompressionStation> (cs.getId(), cs));
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
            if (Exist(pipeline.size()))
            {
                Erase(pipeline);
            }
            break;
        }
        case 9:
        {
            if (Exist(compress.size()))
            {
                Erase(compress);
            }
            break;
        }
        case 10:
        {
            if (Exist(pipeline.size()))
            {
                cout << endl << "Find pipes whose diameter is more than : ";
                float diam = GetCorrectNumber(10000);
                for (int& i : FindObjectsByFilter(pipeline, CheckByDiam, diam))
                {
                    cout << endl << pipeline[i];
                }
            }
            break;
        }
        case 11:
        {
            if (Exist(pipeline.size()))
            {
                cout << endl << "Find pipes in repair(1) or not in repair(0): ";
                bool repair = GetCorrectNumber(1);
                for (int& i: FindObjectsByFilter(pipeline, CheckByRepair, repair))
                {
                cout << endl << pipeline[i];
                }
            }
            break;
        }
        case 12:
        {
            if (Exist(compress.size()))
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
            break;
        }
        case 13:
        {
            if (Exist(compress.size()))
            {
                cout << endl << "Find compression station with percent of not working departments: ";
                float ddep = GetCorrectNumber(100);
                for (int& i : FindObjectsByFilter(compress, CheckByDisDep, ddep))
                {
                    cout << endl << compress[i];
                }
            }
            break;
        } 
        case 14:
        {
            if (Exist(pipeline.size()))
            {
                PrintEditingPipe();
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
                                        cout << "ID is not correct" << endl;
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
        case 15:
        {
            if (compress.size() >= 2 && !pipeline.empty())
            {
                bool net_menu = true;
                while (net_menu)
                {
                    PrintNetwork();
                    switch (GetCorrectNumber(7))
                    {
                    case 1:
                    {
                        InputNetwork(pipeline, compress, net);
                        break;
                    }
                    case 2:
                    {
                        cout << endl << net << endl;
                        break;
                    }
                    case 3:
                    {
                        PrintTopologicalSort(compress, net);
                        break;
                    }
                    case 4:
                    {
                        SaveNet(net);
                        break;
                    }
                    case 5:
                    {
                        LoadNet(net);
                        break;
                    }
                    case 6:
                    {
                        cout << endl << "Enter id of compressor station to delete: ";
                        net.DeleteVertex(GetCorrectNumber(findMaxID(compress)));
                        break;
                    }
                    case 7:
                    {
                        cout << endl << "Enter id of pipeline to delete: ";
                        net.DeleteEdge(GetCorrectNumber(findMaxID(pipeline)));
                        break;
                    }
                    case 0:
                    {
                        net_menu = false;
                        break;
                    }
                    }
                }
            }
            else
            {
                Exist(0);
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