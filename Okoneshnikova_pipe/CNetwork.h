#pragma once
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <iostream>
#include <fstream>

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
		double Capacity;
		double Weight;

	};

public:
	void Connect(int idVer1, int idVer2, int idEdge, double Weight=1.0, double Capacity=1.0, bool is_one_step=true);
	bool HasEdge(int Id) const;
	vector<int> TopologicalSort() const;
	void DeleteVertex(int id);
	void DeleteEdge(int id);
	friend ostream& operator << (ostream& out, const CNetwork& N);
	friend istream& operator >> (istream& in, CNetwork& N);
	friend ifstream& operator >> (ifstream& fin, CNetwork& N);
	friend ofstream& operator << (ofstream& fout, const CNetwork& N);

private:
	CNetwork::Vertex AddVertex(int ownId);
	CNetwork::Edge AddEdge(int startId, int ownId, int endId, double Weight, double Capacity, bool is_directed, bool StartToEnd);
	bool is_cycled() const;
	vector <CNetwork::Edge> GetEjectors(int Id) const;
	vector <int> GetAdjacent(int Id) const;
	map <int, Vertex> mapVertex;
	unordered_map <int, Edge> mapEdge;
	bool HasVertex(int Id) const;
};