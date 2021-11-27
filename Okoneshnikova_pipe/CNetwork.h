#pragma once
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>

using namespace std;

class CNetwork
{
	struct Vertex
	{
		int VertexId;
		unordered_set <int> EdgeIds;
		bool is_marked;
		bool is_passed;
	};

	struct Edge
	{
		int StartVertexId;
		int EndVertexId;
		int EdgeId;
		bool is_directed;

	};

public:
	void Connect(int idVer1, int idVer2, int idEdge, double Weight, double Capacity, bool is_one_step=true);
	bool HasEdge(int Id) const;
	bool HasVertex(int Id) const;
	vector<int> TopologicalSort() const;
private:
	CNetwork::Vertex AddVertex(int ownId);
	CNetwork::Edge AddEdge(int startId, int ownId, int endId, double Weight, double Capacity, bool is_directed, bool StartToEnd);
	bool is_cycled() const;
	vector <CNetwork::Edge> GetEjectors(int Id) const;
	vector <int> GetAdjacent(int Id) const;
	map <int, Vertex> mapVertex;
	unordered_map <int, Edge> mapEdge;
};