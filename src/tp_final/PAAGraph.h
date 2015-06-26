/*
 * PAAGraph.h
 *
 *  Created on: 15/06/2015
 *      Author: vagner
 */

#ifndef PAAGRAPH_H_
#define PAAGRAPH_H_
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include "../lib/FileManager.h"


namespace PAA {

class PAAGraph: public Graph<PAA::Vertex, PAA::Edge> {

private:
	bool resetEnabled;
	PAA::FileManager* fm;
private://@methods
	void closeFile(const std::string&);
	void openFile(const std::string&,const char);
public:
	PAAGraph();
	virtual ~PAAGraph();
	void setResetEnabled(bool enabled);

	//Remove todas as arestas do grafo.
	void clearEdges();

	//Retorna true se existir uma aresta entre os vértices v1  e v2
	bool containsEdge(Vertex* v1, Vertex* v2) const;

	//Retorna true se existir uma aresta entre os vertices identificaos por v1 e v2
	bool containsEdge(const std::string& v1, const std::string& v2) const;

	//Retorna true se a aresta 'edge' exista no grafo
	bool containsEdge(Edge* edge) const;

	//Retorna true se o veŕtice identificado por 'name' exista no grafo.
	bool containsVertex(const std::string& name) const;


	//Retorna true se o vértice v existe no grafo.
	bool containsVertex(Vertex* v) const;

	Edge* getArc(Vertex* v1, Vertex* v2) const;
	Edge* getArc(const std::string& v1, const std::string& v2) const;
	Edge* getEdge(Vertex* v1, Vertex* v2) const;
	Edge* getEdge(const std::string& v1, const std::string& v2) const;
	Edge* getInverseArc(Edge* edge) const;
	Edge* getInverseEdge(Edge* edge) const;

	bool isNeighbor(const std::string& v1, const std::string& v2) const;
	bool isNeighbor(Vertex* v1, Vertex* v2) const;



	void resetData();


	Edge* addEdge(const std::string& v1, const std::string& v2, double cost = 0.0, bool directed = true);
	Edge* addEdge(Vertex* v1, Vertex* v2, double cost = 0.0, bool directed = true);
	Edge* addEdge(Edge* e, bool directed = true);
	Vertex* addVertex(const std::string& name);
	Vertex* addHonestVertex(const std::string& name);
	Vertex* setVertexAsHonest(const std::string& name);
	Vertex* setVertexAsSybil(const std::string& name);
	Vertex* addVertex(Vertex* v);



	const std::set<Edge*>& getEdgeSet() const;
	const std::set<Edge*>& getEdgeSet(Vertex* v) const;
	const std::set<Edge*>& getEdgeSet(const std::string& v) const;

	Vertex* getVertex(const std::string& name) const;
	const std::set<Vertex*>& getVertexSet() const;

	void removeEdge(const std::string& v1, const std::string& v2,bool directed = true);
	void removeEdge(Vertex* v1, Vertex* v2, bool directed = true);
	void removeEdge(Edge* e, bool directed = true);

	void removeVertex(const std::string& name);
	void removeVertex(Vertex* v);

	//Carrega os dados do grafo de um aarquivo
	void load(const std::string&);

	//
	int getNumberOfVertex(void)const;

	};

} /* namespace PAA */

#endif /* PAAGRAPH_H_ */
