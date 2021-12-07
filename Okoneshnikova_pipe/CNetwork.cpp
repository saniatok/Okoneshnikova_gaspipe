#include "CNetwork.h"
#include "utils.h"


void CNetwork::Connect(int idVer1, int idVer2, int idEdge, double Weight, double Capacity, bool is_one_step)
{
    bool Ver1Connect = HasVertex(idVer1);
    bool Ver2Connect = HasVertex(idVer2);
    bool EdgeConnect = HasEdge(idEdge);
    if (!EdgeConnect && idVer1 != 0 && idVer2 != 0 && idEdge != 0)
    {
        if (Ver1Connect && Ver2Connect)
        {
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, is_one_step);
        }
        else if (!Ver1Connect && !Ver2Connect)
        {
            AddVertex(idVer1);
            AddVertex(idVer2);
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, is_one_step);
        }
        else if (Ver1Connect && !Ver2Connect)
        {
            AddVertex(idVer2);
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, is_one_step);
        }
        else if (!Ver1Connect && Ver2Connect)
        {
            AddVertex(idVer1);
            AddEdge(idVer1, idEdge, idVer2, Weight, Capacity, true, is_one_step);
        }
    }
    else
    {
        cout << "This is already connected" << endl;
    }
}

bool CNetwork::HasEdge(int Id) const
{
    if (mapEdge.find(Id) != mapEdge.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CNetwork::HasVertex(int Id) const
{
    if (mapVertex.find(Id) != mapVertex.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CNetwork::is_cycled() const
{
    map<int, Vertex> workmap = mapVertex;
    stack <int> stackvert;

    for (const pair<const int, Vertex>& it : mapVertex)
    {
        workmap = mapVertex;
        stackvert.push(it.first);
        while (!stackvert.empty())
        {
            map<int, Vertex>::iterator it = workmap.find(stackvert.top());
            if (!it->second.is_marked && !it->second.is_passed)
            {
                it->second.is_marked = true;
                for (int U : GetAdjacent(it->second.VertexId))
                {
                    map<int, Vertex>::iterator itC = workmap.find(U);
                    if (!itC->second.is_marked && !itC->second.is_passed)
                    {
                        stackvert.push(itC->second.VertexId);
                    }
                    else if (itC->second.is_marked && !itC->second.is_passed)
                    {
                        return true;
                    }
                }
            }
            else if (it->second.is_marked && !it->second.is_passed)
            {
                it->second.is_passed = true;
                stackvert.pop();
            }
            else if (it->second.is_passed)
            {
                stackvert.pop();
            }
        }
    }
    return false;
}

vector<int> CNetwork::TopologicalSort() const
{
    vector<int> res;
    if (!is_cycled())
    {
        map<int, Vertex> workmap;
        stack<int> stackvert;
        for (const pair<const int, Vertex>& it : mapVertex)
        {
            res.clear();
            workmap = mapVertex;
            stackvert.push(it.first);
            while (!stackvert.empty())
            {
                map<int, Vertex>::iterator it = workmap.find(stackvert.top());
                if (!it->second.is_marked && !it->second.is_passed)
                {
                    it->second.is_marked = true;
                    for (int U : GetAdjacent(it->second.VertexId))
                    {
                        map<int, Vertex>::iterator it = workmap.find(U);
                        if (!it->second.is_marked && !it->second.is_passed)
                        {
                            stackvert.push(it->second.VertexId);
                        }
                    }
                }
                else if (it->second.is_marked && !it->second.is_passed)
                {
                    it->second.is_passed = true;
                    res.insert(res.begin(), it->first);
                    stackvert.pop();
                }
                else if (it->second.is_passed)
                {
                    stackvert.pop();
                }
            }
            if (res.size() == mapVertex.size())
            {
                return res;
            }
        }
        return {};
    }
    else
    {
        return {};
    }
}

void CNetwork::DeleteVertex(int id)
{
    if (HasVertex(id))
    {
        auto it = mapVertex.find(id);
        std::vector<int> IdsForDelete;
        IdsForDelete.reserve(it->second.EdgeIds.size());
        for (int id : it->second.EdgeIds)
        {
            IdsForDelete.push_back(id);
        }
        for (int id : IdsForDelete)
        {
            DeleteEdge(id);
        }
        mapVertex.erase(it);
    }
    else
    {
        cout << endl <<"No Vertex ";
    }
}

void CNetwork::DeleteEdge(int id)
{
    if (HasEdge(id))
    {
        auto it = mapEdge.find(id);
        mapVertex[it->second.StartVertexId].EdgeIds.erase(id);
        mapVertex[it->second.EndVertexId].EdgeIds.erase(id);
        mapEdge.erase(id);
    }
    else
    {
        cout<< endl<<"No Edge ";
    }
}

CNetwork::Vertex CNetwork::AddVertex(int ownId)
{
    Vertex v;
    v.VertexId = ownId;
    v.is_marked = false;
    v.is_passed = false;
    mapVertex.insert(pair<int, Vertex>(ownId, v));
    return v;
}

CNetwork::Edge CNetwork::AddEdge(int startId, int ownId, int endId, double Weight, double Capacity, bool is_directed, bool StartToEnd)
{
    Edge e;
    e.StartVertexId = startId;
    e.EdgeId = ownId;
    e.EndVertexId = endId;
    e.Weight = Weight;
    e.Capacity = Capacity;
    is_directed ? e.is_directed = true : e.is_directed = false;
    if (!StartToEnd)
    {
        e.StartVertexId = endId;
        e.EndVertexId = startId;
    }
    mapEdge.insert(pair <int, Edge>(ownId, e));
    mapVertex[startId].EdgeIds.insert(ownId);
    mapVertex[endId].EdgeIds.insert(ownId);
    return e;
}

vector<CNetwork::Edge> CNetwork::GetEjectors(int IdV) const
{
    vector <Edge> Ejectors;
    auto it = mapVertex.find(IdV);
    for (int id : it->second.EdgeIds)
    {
        auto itE = mapEdge.find(id);
        Edge e = itE->second;
        if ((e.is_directed && e.StartVertexId == IdV) || !e.is_directed)
        {
            if (e.EndVertexId == IdV)
            {
                swapValues(e.StartVertexId, e.EndVertexId);
            }
            Ejectors.push_back(e);
        }
    }
    return Ejectors;
}

vector<int> CNetwork::GetAdjacent(int IdV) const
{
    vector <int> Adjacent;
    vector <Edge> Ejectors = GetEjectors(IdV);
    for (const Edge& e : Ejectors)
    {
        Adjacent.push_back(mapVertex.find(e.EndVertexId)->second.VertexId);
    }
    return Adjacent;
}
    
ostream& operator<<(ostream& out, const CNetwork& N)
{
    vector<vector <int>> matrix;
    matrix.resize(N.mapVertex.size() + 1);
    for (vector <int>& v : matrix)
    {
        v.resize(N.mapVertex.size() + 1);
    }
    matrix[0][0] = 0;
    auto it = N.mapVertex.begin();
    for (unsigned int i = 0; i < N.mapVertex.size(); i++)
    {
        matrix[0][i + 1] = it->first;
        matrix[i + 1][0] = it->first;
        it++;
    }
    for (unsigned int i = 1; i < matrix.size(); i++)
    {
        auto adj = N.GetAdjacent(matrix[i][0]);
        auto eject = N.GetEjectors(matrix[i][0]);
        for (unsigned int j = 1; j < matrix[i].size(); j++)
        {
            for (unsigned int k = 0; k < adj.size(); k++)
            {
                if (adj[k] == matrix[0][j])
                {
                    matrix[i][j] = eject[k].EdgeId;
                }
            }
        }
    }
    for (unsigned int i = 0; i < matrix.size(); i++)
    {
        for (unsigned int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, CNetwork& N)
{
    N.mapEdge.clear();
    N.mapVertex.clear();
    cout << "Enter number of vertexes: ";
    int n = 0;
    cin >> n;
    std::vector <int> VecVertex;
    VecVertex.reserve(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter id of vertex";
        int id = GetCorrectNumber(10000);
        VecVertex.push_back(id);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << "Enter an id of directed edge between vertexes "
                << VecVertex[i] << " and " << VecVertex[j] << " (zero, if there is no edge): ";
            int id = GetCorrectNumber(10000);
            if (id != 0)
            {
                cout << "Enter a weight of this edge: ";
                double w = GetCorrectNumber(1000.0);
                cout << "Enter a capacity of this edge: ";
                double c = GetCorrectNumber(1000.0);
                cout << "Whether this edge is from first to second vertex? ([1] - yes, [0] - revers): ";
                bool IsStraight = GetCorrectNumber(1);
                N.Connect(VecVertex[i], VecVertex[j], id, w, c);
            }
        }
    }
    return in;
}

ifstream& operator>>(ifstream& fin, CNetwork& N)
{
    N.mapEdge.clear();
    N.mapVertex.clear();
    int size = 0;
    fin >> size;
    while (size--)
    {
        int EdgeId = 0, StartVertexId = 0, EndVertexId = 0;
        bool is_directed = true;
        double Weight = 0.0, Capacity = 0.0;
        fin >> EdgeId;
        fin >> StartVertexId;
        fin >> EndVertexId;
        fin >> is_directed;
        fin >> Weight;
        fin >> Capacity;
        if (is_directed)
        {
            N.Connect(StartVertexId, EndVertexId, EdgeId, Weight, Capacity);
        }
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, const CNetwork& N)
{
    fout << N.mapEdge.size() << endl;
    for (auto& e : N.mapEdge)
    {
        fout << e.second.EdgeId << endl;
        fout << e.second.StartVertexId << endl; 
        fout << e.second.EndVertexId << endl;
        fout << e.second.is_directed << endl;
        fout << e.second.Weight << endl;
        fout << e.second.Capacity << endl;
    }
    return fout;
}

