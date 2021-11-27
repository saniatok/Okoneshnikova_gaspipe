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
            AddEdge(idVer1, idVer2, idEdge, Weight, Capacity, true, is_one_step);
        }
        else if (!Ver1Connect && !Ver2Connect)
        {
            AddVertex(idVer1);
            AddVertex(idVer2);
            AddEdge(idVer1, idVer2, idEdge, Weight, Capacity, true, is_one_step);
        }
        else if (Ver1Connect && !Ver2Connect)
        {
            AddVertex(idVer2);
            AddEdge(idVer1, idVer2, idEdge, Weight, Capacity, true, is_one_step);
        }
        else if (!Ver1Connect && Ver2Connect)
        {
            AddVertex(idVer1);
            AddEdge(idVer1, idVer2, idEdge, Weight, Capacity, true, is_one_step);
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

//vector<int> CNetwork::TopologicalSort() const
//{
//    vector<int> res;
//    if (!is_cycled())
//    {
//        map<int, Vertex> workmap;
//        stack<int> stackvert;
//
//    }
//    return vector<int>();
//}

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
    e.EdgeId = endId;
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

vector<CNetwork::Edge> CNetwork::GetEjectors(int IdV) const
{
    vector <Edge> Ejectors;
    auto it = mapVertex.find(IdV);
    for (int id : it->second.EdgeIds)
    {
        auto itE = mapEdge.find(id);
        Edge E = itE->second;
        if ((E.is_directed && E.StartVertexId == IdV) || !E.is_directed)
        {
            if (E.EndVertexId == IdV)
            {
                swapValues(E.StartVertexId, E.EndVertexId);
            }
            Ejectors.push_back(E);
        }
    }
    return Ejectors;
}

vector<int> CNetwork::GetAdjacent(int IdV) const
{
    vector <int> Adjacent;
    vector <Edge> Ejectors = GetEjectors(IdV);
    for (const Edge& E : Ejectors)
    {
        Adjacent.push_back(mapVertex.find(E.EndVertexId)->second.VertexId);
    }
    return Adjacent;
}
    
