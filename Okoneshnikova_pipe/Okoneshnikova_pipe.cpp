
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
        cout << endl << "Add data first" << endl;
        return false;
    }
    return true;
};

void EditPipe(unordered_map<int, Pipe>& g, CNetwork& net)
{
    cout << "Enter pipe's index: ";
    int id = GetCorrectNumber(findMaxID(g));
    auto iter =net.mapEdge.find(id);
    unordered_map<int, Pipe>::iterator it = g.find(id);
    if (it != g.end())
    {
        it->second.Repair();
        iter->second.Capacity = it->second.getPerformance();
        iter->second.Weight = it->second.getPressure();

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

void ErasePipe(unordered_map <int, Pipe>& map, CNetwork& net)
{
    cout << endl << "Enter index: ";
    int id = GetCorrectNumber(findMaxID(map));
    if (map.find(id) != map.end())
    {
        map.erase(id);
        if (!net.HasEdge(id))
        {
            net.DeleteEdge(id);
        }
        else
        {
            cout << endl << "Delete pipe from network first";
        }
    }
    else
    {
        cout << endl << "This id is not exist";
    } 
}

void EraseCS(unordered_map <int, CompressionStation>& map, CNetwork& net)
{
    cout << endl << "Enter index: ";
    int id = GetCorrectNumber(findMaxID(map));
    if (map.find(id) != map.end())
    {
        map.erase(id);
        net.DeleteVertex(id);
    }
    else
    {
        cout << endl << "This id is not exist";
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

void PrintTopologicalSort(unordered_map <int, CompressionStation>& compress, CNetwork net)
{
    auto t_sort = net.TopologicalSort();
    if (!t_sort.empty())
    {
        cout << endl << "h" << "\t" << "CS id" << endl;
        cout << "-------------" << endl;
        for (unsigned int i = 0; i < t_sort.size(); i++)
        {
            cout << i + 1 << "\t" << t_sort[i] << endl;
        }
    }
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
        << "8. Calculate max flow" << endl
        << "9. Calculate min path" << endl
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
                for (const pair<const int, Pipe>& pl : pipeline)
                {
                    cout << pl.second << endl;
                }
                for (const pair<const int, CompressionStation>& css : compress)
                {
                    cout << css.second << endl;
                }
            }
            else
            {
                cout << "No data to output" << endl;
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
            string file;
            pipeline.clear();
            compress.clear();
            cout << endl << "Enter name of file: ";
            cin.ignore(10000, '\n');
            getline(cin, file);
            fin.open(file + ".txt", ios::in);
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
                EditPipe(pipeline, net);

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
                ErasePipe(pipeline, net);
            }
            break;
        }
        case 9:
        {
            if (Exist(compress.size()))
            {
                EraseCS(compress, net);
                cout << net;
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
                    switch (GetCorrectNumber(9))
                    {
                    case 1:
                    {
                        cout << endl << "Compression Stations to choose:" << endl;
                        for (auto& cs : compress)
                        {
                            cout << cs.first << endl;
                        }
                        cout << endl << "Enter id of first compression station or 0 for exit: ";
                        int id_FCS = GetCorrectNumber(findMaxID(compress));
                        cout << endl << "Enter id of second compression station or 0 for exit: ";
                        int id_SCS = GetCorrectNumber(findMaxID(compress));
                        if (id_FCS != 0 && id_SCS != 0)
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
                            int id_P = GetCorrectNumber(findMaxID(pipeline));
                            if (id_P != 0)
                            {
                                auto it = pipeline.find(id_P);
                                if (it->second.getRepair() && !net.HasEdge(it->first))
                                {
                                    net.Connect(id_FCS, id_SCS, id_P, it->second.getPressure(), it->second.getPerformance()/*, is_one_step*/);
                                }
                                else
                                {
                                    cout << endl << "This pipe is in repair now, choose another pipe" << endl;
                                }
                            }
                            else
                            {
                                cout << endl << "No available pipes";
                            }
                        }
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
                            fin >> net;
                        }
                        else
                        {
                            cout << endl << "No file with this name" << endl;
                        }
                        fin.close();
                        break;
                    }
                    case 6:
                    {
                        cout << endl << "Enter id of compression station to delete: ";
                        net.DeleteVertex(GetCorrectNumber(findMaxID(compress)));
                        break;
                    }
                    case 7:
                    {
                        cout << endl << "Enter id of pipeline to delete: ";
                        net.DeleteEdge(GetCorrectNumber(findMaxID(pipeline)));
                        break;
                    }
                    case 8:
                    {
                        int idS = 0, idT = 0;
                        cout << endl << "Enter source compression station id or 0 for exit: ";
                        idS = GetCorrectNumber(findMaxID(compress));
                        if (idS != 0)
                        {
                            cout << "Enter target compression station id or 0 for exit: ";
                            idT = GetCorrectNumber(findMaxID(compress));
                            if (idT != 0)
                            {
                                 
                                cout << endl << "Maximum flow: " << net.MaxFlow(idS, idT) << endl;
                            }
                        }
                        break;
                    }
                    case 9:
                    {
                        int idS = 0, idF = 0;
                        cout << endl << "Enter starting compression station id or 0 for exit: ";
                        idS = GetCorrectNumber(findMaxID(compress));
                        if (idS != 0)
                        {
                            cout << "Enter finishing compression station id or 0 for exit: ";
                            idF = GetCorrectNumber(findMaxID(compress));
                            if (idF != 0)
                            {
                                double path = net.MinPath(idS, idF);
                                if (path != 0 || path < INT_MAX)
                                {
                                    cout << endl << "Minimal path: "<< path << endl;
                                }
                                else
                                {
                                    cout << endl << "No path" << endl;
                                }
                            }
                        }
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