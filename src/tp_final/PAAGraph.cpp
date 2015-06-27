/*
 * PAAGraph.cpp
 *
 *  Created on: 15/06/2015
 *      Author: vagner
 */

#include "PAAGraph.h"
#include <iostream>

namespace PAA {

/*
 * PAAGraph member implementations
 */
PAAGraph::PAAGraph() : PAA::Graph<Vertex, Edge>() {

	//Habilitando o reset dos dados de um grafo
    this->resetEnabled = true;
    this->fm = new PAA::FileManager();

}

//Destrutor não sera utilizado. Sem alocação dinâmica
PAAGraph::~PAAGraph(){

	delete this->fm;

}

void PAAGraph::clearEdges() {

	//Coletando as aretas as serem removidas.
    std::set<PAA::Edge*> edges = this->getEdgeSet();
    std::set<PAA::Edge*>::iterator itEdges;

    for (itEdges = edges.begin(); itEdges != edges.end(); itEdges++) {

        removeEdge(*itEdges);
    }
}

bool PAAGraph::containsEdge(Vertex* v1, Vertex* v2) const {

    return this->getEdge(v1, v2) != NULL;

}

bool PAAGraph::containsEdge(const std::string& v1, const std::string& v2) const {

    return this->getEdge(v1, v2) != NULL;
}

bool PAAGraph::containsEdge(Edge* edge) const {

	std::set<PAA::Edge*> edgeSet;
    if (edge == NULL) {
        return false;
    } else {

    	edgeSet = this->getEdgeSet();
    	return edgeSet.end() != edgeSet.find(edge);
    }
}



bool PAAGraph::containsVertex(const std::string& name) const {

    return this->getNode(name) != NULL;

}

bool PAAGraph::containsVertex(Vertex* v) const {

	std::set<PAA::Vertex*> vertexSet;
    if (v == NULL) {
        return false;
    } else {

    	vertexSet = this->getNodeSet();

    	return vertexSet.end() != vertexSet.find(v);

    }
}


Edge* PAAGraph::getEdge(Vertex* v1, Vertex* v2) const {

	std::set<PAA::Edge*>::iterator itEdges;

	for(itEdges = this->getEdgeSet(v1).begin(); itEdges != this->getEdgeSet(v1).end();itEdges++){
		if ( (*itEdges)->getFinishVertex() == v2){
			return (*itEdges);
		}
	}

    return NULL;
}

Edge* PAAGraph::getEdge(const std::string& v1, const std::string& v2) const {

    return this->getEdge(this->getVertex(v1), this->getVertex(v2));

}

Edge* PAAGraph::getInverseArc(Edge* edge) const {

    return this->getEdge(edge->getFinishVertex(), edge->getStartVertex());
}

Edge* PAAGraph::getInverseEdge(Edge* edge) const {

    return this->getInverseArc(edge);

}

bool PAAGraph::isNeighbor(const std::string& v1, const std::string& v2) const {
    return this->isNeighbor(this->getVertex(v1), this->getVertex(v2));
}

bool PAAGraph::isNeighbor(Vertex* v1, Vertex* v2) const {

	std::set<PAA::Edge*>::iterator itEdges;

	for(itEdges = this->getEdgeSet(v1).begin(); itEdges != this->getEdgeSet(v1).end();itEdges++){

		if( (*itEdges)->getFinishVertex() == v2){
			return true;
		}
	}
    return false;
}

void PAAGraph::resetData() {

	std::set<PAA::Edge*>::iterator itStartEdge;
	std::set<PAA::Edge*>::iterator itEndEdge;
	std::set<PAA::Edge*>::iterator itEdge;

	std::set<PAA::Vertex*>::iterator itStartVertex;
	std::set<PAA::Vertex*>::iterator itEndVertex;
	std::set<PAA::Vertex*>::iterator itVertex;

	itStartVertex = this->getVertexSet().begin();
	itEndVertex	  = this->getVertexSet().end();

	itStartEdge = this->getEdgeSet().begin();
	itEndEdge	= this->getEdgeSet().end();

    if (this->resetEnabled) {

    	for(itVertex = itStartVertex; itVertex != itEndVertex; itVertex++){

    		(*itVertex)->resetData();
    	}

    	for(itEdge = itStartEdge; itEdge != itEndEdge; itEdge++ ){

    		(*itEdge)->resetData();
    	}

    }
}

void PAAGraph::setResetEnabled(bool enabled) {

   this->resetEnabled = enabled;

}



Edge* PAAGraph::addEdge(const std::string& v1, const std::string& v2, double cost, bool directed) {

    return this->addEdge(getVertex(v1), getVertex(v2), cost, directed);

}

Edge* PAAGraph::addEdge(Vertex* v1, Vertex* v2, double cost, bool directed) {

    Edge* e = new Edge(v1, v2, cost);
    return addEdge(e, directed);

}

Edge* PAAGraph::addEdge(Edge* e, bool directed) {

    Edge* result = this->addArc(e);
    if (!directed) {

        Edge* result2 = this->addArc(e->getFinishVertex(), e->getStartVertex());

        result2->setWeight(e->getWeight());
    }
    return result;
}

Vertex* PAAGraph::addVertex(const std::string& name) {
    return this->addNode(name);
}

Vertex* PAAGraph::addVertex(Vertex* v) {
    return this->addNode(v);
}

const std::set<Edge*>& PAAGraph::getEdgeSet() const {
    return this->getArcSet();
}

const std::set<Edge*>& PAAGraph::getEdgeSet(Vertex* v) const {
    return this->getArcSet(v);
}

const std::set<Edge*>& PAAGraph::getEdgeSet(const std::string& v) const {
    return this->getArcSet(v);
}

Vertex* PAAGraph::getVertex(const std::string& name) const {
    return this->getNode(name);
}

const std::set<Vertex*>& PAAGraph::getVertexSet() const {
    return this->getNodeSet();
}

void PAAGraph::removeEdge(const std::string& v1, const std::string& v2, bool directed) {
    this->removeEdge(this->getVertex(v1), this->getVertex(v2), directed);
}

void PAAGraph::removeEdge(Vertex* v1, Vertex* v2, bool directed) {
    this->removeArc(v1, v2);
    if (!directed) {
        this->removeArc(v2, v1);
    }
}

void PAAGraph::removeEdge(Edge* e, bool directed) {
    this->removeArc(e);
    if (!directed) {
        this->removeArc(e->getFinishVertex(), e->getStartVertex());
    }
}

void PAAGraph::removeVertex(const std::string& name) {
    this->removeNode(name);
}

void PAAGraph::removeVertex(Vertex* v) {
    this->removeNode(v);
}



void PAAGraph::load(const std::string& filePath){

	 std::string line;
	 std::vector<std::string> valuesRead;
	 std::vector<std::string>::iterator itStr;
	 std::stringstream ss;
	 const char delimiter = '\t';


	 try {

		 //Abrindo o arquivo em modo leitura
		 this->openFile(filePath,'R');

		 while(this->fm->hasMore()) {
			 line = this->fm->readLine();

			 if(!line.empty() && line.at(0) != '#') {

				 valuesRead = this->fm->splitString(line.c_str(), delimiter);

				 if(!this->containsVertex(valuesRead.at(0))){
					 this->addVertex(valuesRead.at(0));
					 //std::cout << "Adicionado o vértice " << this->getVertex(valuesRead.at(0))->toString() << std::endl;

				 }

				if (!this->containsVertex(valuesRead.at(1))) {
					this->addVertex(valuesRead.at(1));
					//std::cout << "Adicionado o vértice " << this->getVertex(valuesRead.at(1))->toString() << std::endl;
				}

				this->addEdge(valuesRead.at(0), valuesRead.at(1),1,true);

			 }
		}

	this->closeFile(filePath);
	} catch (const std::exception& e) {

		ss << "Erro ao ler o arquivo " << filePath << " Detalhes: " << e.what() << std::endl;

		throw PAA::PAAException("PAAGraph::load( )", ss.str());
	}

}

void PAAGraph::openFile(const std::string& fileName, const char mode){
	try {

		this->fm->openFile(fileName,mode);

	} catch (const PAAException& e) {

		throw PAAException("PAAGraph::openFile", "Erro ao abrir o arquivo " + fileName + "no modo " + mode);
	}
}

void PAAGraph::closeFile(const std::string& fileName){

	try {

		this->fm->closeFile();

	} catch (const PAAException& e) {

		throw PAAException("PAAGraph::closeFile", "Erro ao abrir o arquivo " + fileName);
	}
}


int PAAGraph::getNumberOfVertex(void)const{
	return PAA::Graph<PAA::Vertex,PAA::Edge>::size();
}



} /* namespace PAA */
