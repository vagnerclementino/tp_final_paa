/*
 * Graph.h
 *
 *  Created on: 15/06/2015
 *      Author: vagner
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <map>
#include <sstream>
#include <vector>
#include "../lib/PAAException.h"
#include <stdexcept>

namespace PAA {

template <typename NodeType, typename ArcType>
class Graph {
private:
	/**
	 * Atributos
	 */
    std::set<NodeType*> nodes;                  // Conjunto de vértices
    std::set<ArcType*> arcs;                  	// Conjuntto de aretas
    std::map<std::string, NodeType*> nodeMap;   // Mapeamento vértice - nome

    /***
     * Métodos privados
     */
    void deepCopy(const Graph& src);
    NodeType* getExistingNode(const std::string& name, const std::string& member = "") const;
    int graphCompare(const Graph& graph2) const;
    bool isExistingArc(ArcType* arc) const;
    bool isExistingNode(NodeType* node) const;
    void verifyExistingNode(NodeType* node, const std::string& member = "") const;
    void verifyNotNull(void* p, const std::string& member = "") const;
    bool containsKey(const std::string& name) const;

public:
    //Cria um grafo vazio
    Graph();

    //Destroi o grafo liberando memória
    virtual ~Graph();

    //Adiciona uma aresta do grafo dado os identificadore dos vértices v1(s1) e v2(s2). Retorna a aresta inserida
    ArcType* addArc(const std::string& s1, const std::string& s2);

    //Adiciona uma aresta no grafo dado os vertices  n1 e n2.  Retorna a aresta inserida
    ArcType* addArc(NodeType* n1, NodeType* n2);

    //Adicionar uma aresta no grafo dado a aresta arc.  Retorna a aresta inserida
    ArcType* addArc(ArcType* arc);


    //Adicionar um vértice no grafo com um identificador name
    NodeType* addNode(const std::string& name);

    //Adiciona o vértice node no grafo.
    NodeType* addNode(NodeType* node);

    //Torna o grafo vazio e liberar memória alocada.
    void clear();

    //Verifica se dois grafos são iguais.
    bool equals(const Graph<NodeType, ArcType>& graph2) const;

    //Retorna todos as aresta do grafo.
    const std::set<ArcType*>& getArcSet(void) const;

    //Retorna as arestas que o vertice node como o primeiro vértice
    const std::set<ArcType*>& getArcSet(NodeType* node) const;

    //Retorna as arestas que o vertice identificado por name  como o primeiro vértice
    const std::set<ArcType*>& getArcSet(const std::string& name) const;

    //Retorna a lista de adjacência do vértice node
    const std::set<NodeType*> getNeighbors(NodeType* node) const;

    //Retorna a lista de adjacência do vértice identificado por name
    const std::set<NodeType*> getNeighbors(const std::string& name) const;

    //Retorna um vértice identificado por name
    NodeType* getNode(const std::string& name) const;

    //Retorna todos os vertices do grapo
    const std::set<NodeType*>& getNodeSet() const;

    //Retorna true se existe uma aresta entre n1 e n2
    bool isConnected(NodeType* n1, NodeType* n2) const;

    //Retorna true se existe uma aresta entre os vertices indentificados por s1 e s2
    bool isConnected(const std::string& s1, const std::string& s2) const;

    //Retorna true se o grafo está vazio
    bool isEmpty() const;

    //Remove a aresta entre os vertice indentificados por s1 e s2;
    void removeArc(const std::string& s1, const std::string& s2);

    //Remove a aresta entre os vertice n1 e n2;
    void removeArc(NodeType* n1, NodeType* n2);

    //Remove a aresta arc
    void removeArc(ArcType* arc);

    //Remove o vértice indetificado por name
    void removeNode(const std::string& name);

    //Remove o vértice node
    void removeNode(NodeType* node);

    //Retorna um número de vértices do grafo.
    int size() const;

    //Coverte o grafo em uma string para ser impressa
    std::string toString() const;

    //Compara dois grafos
    Graph& operator =(const Graph& src);

    //Constroi um grafo como cópia um do outro
    Graph(const Graph& src);

    static int compare(NodeType* n1, NodeType* n2) {
        if (n1 == n2) {
            return 0;
        }
        if (n1->name < n2->name) {
            return -1;
        }
        if (n1->name > n2->name) {
            return +1;
        }
        return (n1 < n2) ? -1 : +1;
    }

    static int compare(ArcType* a1, ArcType* a2) {
        if (a1 == a2) {
            return 0;
        }
        NodeType* n1 = a1->start;
        NodeType* n2 = a2->start;
        if (n1 != n2) {
            return compare(n1, n2);
        }
        n1 = a1->finish;
        n2 = a2->finish;
        if (n1 != n2) {
            return compare(n1, n2);
        }
        return (a1 < a2) ? -1 : +1;
    }
};


template <typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::Graph() {

    this->nodes = std::set<NodeType*>();
    this->arcs = std::set<ArcType*>();
}

template <typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::Graph(const Graph& src) {

    this->nodes = std::set<NodeType*>();
    this->arcs = std::set<ArcType*>();
    this->deepCopy(src);
}

template <typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::~Graph() {
    this->clear();
}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::addArc(const std::string& s1, const std::string& s2) {

    return this->addArc(getExistingNode(s1, "addArc"), getExistingNode(s2, "addArc"));

}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::addArc(NodeType* n1, NodeType* n2) {

    verifyExistingNode(n1, "addArc");
    verifyExistingNode(n2, "addArc");

    ArcType* arc = new ArcType();
    arc->setStartVertex(n1);
    arc->setFinishVertex(n2);
    return addArc(arc);
}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::addArc(ArcType* arc) {

    verifyNotNull(arc, "addArc");
    if (!isExistingNode(arc->getStartVertex())) {
        addNode(arc->getStartVertex());
    }
    if (!isExistingNode(arc->getFinishVertex())) {
        addNode(arc->getFinishVertex());
    }
    arc->getStartVertex()->addEdges(arc);

    this->arcs.insert(arc);
    return arc;
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::addNode(const std::string& name) {

	std::stringstream ss;
    if (this->containsKey(name)) {

        throw PAA::PAAException(ss.str());

    }
    NodeType* node = new NodeType();

    node->setName(name);
    return addNode(node);
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::addNode(NodeType* node) {

	std::string nodeName = node->getName();

	std::stringstream ss;
    verifyNotNull(node, "addNode");
    if (this->nodeMap.find(nodeName) != this->nodeMap.end()) {

    	ss << "Graph::addNode: O vertice de nome " << node->getName() << " já exite." << std::endl;
    	throw PAA::PAAException(ss.str());
    }
    this->nodes.insert(node);
    this->nodeMap[nodeName] = node;
    return node;
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::clear() {

	typename std::set<NodeType*>::iterator itNodes;
	typename std::set<ArcType*>::iterator itArcs;

	for (itNodes = this->nodes.begin(); itNodes != this->nodes.end(); itNodes++) {
        delete (*itNodes);
    }

    for (itArcs = this->arcs.begin(); itArcs != this->arcs.end(); itArcs++) {
        delete (*itArcs);
    }
    this->arcs.clear();
    this->nodes.clear();
    this->nodeMap.clear();
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::equals(const Graph<NodeType, ArcType>& graph2) const {
    return *this == graph2;
}

template <typename NodeType, typename ArcType>
const std::set<ArcType*>& Graph<NodeType, ArcType>::getArcSet() const {
    return this->arcs;
}

template <typename NodeType, typename ArcType>
const std::set<ArcType*>& Graph<NodeType, ArcType>::getArcSet(NodeType* node) const {
    verifyExistingNode(node, "getArcSet");
    return node->getEdges();
}

template <typename NodeType, typename ArcType>
const std::set<ArcType*>& Graph<NodeType, ArcType>::getArcSet(const std::string& name) const {

    return getArcSet(getExistingNode(name, "getArcSet"));

}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::getExistingNode(const std::string& name, const std::string& member) const {

	std::stringstream ss;

	NodeType* node = nodeMap.at(name);
    if (!node) {
        ss << "Graph::" + member + ": no node named " + name;
        throw PAA::PAAException(ss.str());
    }
    return node;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isExistingArc(ArcType* arc) const {

	typename std::set<ArcType*>::iterator itArcs;
	bool exists = false;

	if ( (arc != NULL) ){

		itArcs = this->arcs.find(arc);

		if(itArcs != this->arcs.end()){

			exists = true;

		}else{

			exists = false;

		}

	}else{

		exists = false;
	}

	return exists;

}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isExistingNode(NodeType* node) const {

    return node && this->containsKey(node->getName()) && nodeMap.at(node->getName()) == node;

}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::verifyExistingNode(NodeType* node, const std::string& member) const {

	std::stringstream ss;
    verifyNotNull(node, member);
    if (!isExistingNode(node)) {
        ss << "Graph::" + member + ": não encontrado!" << std::endl;
        throw PAA::PAAException(ss.str());
    }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::verifyNotNull(void* p, const std::string& member) const {

	std::stringstream ss;
    if (!p) {
        ss << "Graph::" + member + ": parâmetro não pode ser nulo cannot be null";
        throw PAA::PAAException(ss.str());
    }
}

template <typename NodeType, typename ArcType>
const std::set<NodeType*> Graph<NodeType, ArcType>::getNeighbors(NodeType* node) const {

    verifyExistingNode(node, "getNeighbors");

    std::set<NodeType*> nodeSet = std::set<NodeType*>();
    typename std::set<NodeType*>::iterator itNodes;

    for(itNodes = (node->getEdges).begin(); itNodes != (node->getEdges).end(); itNodes++ ){

    	nodeSet.insert((*itNodes)->getFinishVertex());
    }


    return nodeSet;
}

template <typename NodeType, typename ArcType>
const std::set<NodeType*> Graph<NodeType, ArcType>::getNeighbors(const std::string& name) const {
    return getNeighbors(getExistingNode(name, "getNeighbors"));
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::getNode(const std::string& name) const {

	if(this->nodeMap.size() == 0){
		return NULL;
	}
	else{
		try {

			return nodeMap.at(name);

		 } catch (const std::out_of_range& oor) {

			return NULL;
		}
	}

}

template <typename NodeType, typename ArcType>
const std::set<NodeType*>& Graph<NodeType, ArcType>::getNodeSet() const {
    return this->nodes;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isConnected(NodeType* n1, NodeType* n2) const {

	typename std::set<ArcType*>::iterator itArcs;

    if (!isExistingNode(n1) || !isExistingNode(n2)) {
        return false;
    }

    for( (itArcs = n1->getEdges()).begin(); itArcs != (itArcs = n1->getEdges()).end(); itArcs++){

    	(*itArcs)->getFinishVertex() = n2;

    	return true;
    }

    return false;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isConnected(const std::string& s1,
                                           const std::string& s2) const {

    return isConnected(nodeMap.at(s1), nodeMap.at(s2));
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isEmpty() const {
    return this->nodes.empty();
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(const std::string& s1, const std::string& s2) {

    removeArc(nodeMap.at(s1), nodeMap.at(s2));
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(NodeType* n1, NodeType* n2) {

	std::vector<ArcType*> toRemove;
	typename std::vector<ArcType*>::iterator itRemove;
	typename std::set<ArcType*>::iterator itArcs;

    if (!isExistingNode(n1) || !isExistingNode(n2)) {
        return;
    }

    for(itArcs = this->arcs.begin(); itArcs != this->arcs.end(); itArcs++){

    	if ( (*itArcs)->getStartVertex() == n1 && (*itArcs)->getFinishVertex() == n2){

    		toRemove.push_back((*itArcs));

    	}


    }

    for(itRemove = toRemove.begin(); itRemove != toRemove.end(); itRemove++){

    	removeArc(*itRemove);
    }

}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(ArcType* arc) {
    if (!isExistingArc(arc)) {
        return;
    }
    arc->getStartVertex()->removeEdge(arc);
    this->arcs.erase(arc);
}


template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeNode(const std::string& name) {

    removeNode(this->nodeMap.at(name));
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeNode(NodeType* node) {

	std::vector<ArcType*> toRemove;
	typename std::vector<ArcType*>::iterator itRemove;
	typename std::set<ArcType*>::iterator itArcs;

    if (!isExistingNode(node)) {
        return;
    }

    for(itArcs = this->arcs.begin(); itArcs != this->arcs.end(); itArcs++){

    	if((*itArcs)->getStartVertex()== node || (*itArcs)->getFinishVertex() == node){

    		toRemove.push_back((*itRemove));
    	}
    }

    for(itRemove = toRemove.begin(); itRemove != toRemove.end(); itRemove++){

       	removeArc(*itRemove);

    }
    this->nodes.erase(node);
}

template <typename NodeType, typename ArcType>
int Graph<NodeType, ArcType>::size() const {
    return nodes.size();
}

template <typename NodeType, typename ArcType>
std::string Graph<NodeType, ArcType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename NodeType, typename ArcType>
Graph<NodeType,ArcType>&
Graph<NodeType, ArcType>::operator =(const Graph& src) {
    if (this != &src) {
        this->clear();
        this->deepCopy(src);
    }
    return *this;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::containsKey(const std::string& name) const{

	return this->nodeMap.find(name) != this->nodeMap.end();
}



} /* namespace PAA */

#endif /* GRAPH_H_ */
