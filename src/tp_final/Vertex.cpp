/*
 * Vertex.cpp
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#include "Vertex.h"
#include <sstream>
#include "../lib/PAAException.h"

namespace PAA {

Vertex::Vertex(const std::string& vetexName):edges(arcs) {

	this->name = vetexName;
	this->previous = NULL;
	//Definindo valor padrão para os atributos
	this->resetData();

}

Vertex::Vertex(const Vertex &other): edges(arcs){

	this->name = other.getName();
	this->arcs = other.arcs;
	this->edges = this->arcs;
	this->cost = other.getCost();
	this->visited = other.getVisited();
	this->previous = other.getPreviousVertex();
	this->color = other.getColor();

}
Vertex::~Vertex() {
	//Nada para fazer, não houve alocaçaõ dinâmcia de memória
}

void Vertex::resetData() {

    this->setCost(0.0);
    this->setPreviousVertex(NULL);
    this->setVisited(false);
    this->setColor(WHITE);
    this->setIsSybil(true);



}

std::string Vertex::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

Vertex& Vertex::operator =(const Vertex& other) {
    this->setName(other.getName());
    this->setEdges(other.getEdges());
    this->setCost(other.getCost());
    this->setVisited(other.getVisited());
    this->setPreviousVertex(other.getPreviousVertex());
    this->setColor(other.getColor());

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Vertex& v) {

	std::set<PAA::Edge*> edges;
	std::set<PAA::Edge*>::iterator itEdges;
    out << "Vertex{name=" << v.getName();
    out << ", cost=" << v.getCost();
    out << ", visited=" << (v.getVisited() ? "true" : "false");
    out << ", previous=" << (v.getPreviousVertex() == NULL ? std::string("NULL") : v.getPreviousVertex()->getName());

    out << ", neighbors={";
    int i = 0;

    edges = v.getEdges();

    for(itEdges = edges.begin(); itEdges != edges.end(); itEdges++) {

        if (i > 0) {
            out << ", ";
        }
        i++;

        if ( (*itEdges)->getFinishVertex() != NULL) {
            out << (*itEdges)->getFinishVertex()->getName();
        } else {
            out << "NULL";
        }
    }
    out << "}";
    out << "}";
    return out;
}

bool sortByDegree(PAA::Vertex* v1, PAA::Vertex* v2) {

	return v1->getEdges().size() < v2->getEdges().size();
}

bool sortByName(PAA::Vertex* v1, PAA::Vertex* v2){

	return v1->getName() < v2->getName();
}



const std::string& Vertex::getName(void)const{

	return this->name;

}

void Vertex::setName(const std::string& aName){

	this->name = aName;

}

double Vertex::getCost(void)const{

	return this->cost;
}

void Vertex::setCost(double aCost){

	this->cost = aCost;
}


bool Vertex::getVisited(void)const{

	return this->visited;

}

void Vertex::setVisited(bool aVisited){

	this->visited = aVisited;

}

//Métodos para acesso e alteração do atributo 'isSybil'
void Vertex::setIsSybil(bool sybilFlag){

	this->isSybil = sybilFlag;
}

bool Vertex::getIsSybil(void) const{

	return this->isSybil;

}

//Métodos para acesso e alteração do atributo 'Color'
PAA::Color Vertex::getColor(void) const{

	return this->color;
}
void Vertex::setColor(PAA::Color newColor){

	this->color = newColor;

}

std::set<PAA::Edge*>& Vertex::getEdges(void) const{

	return this->edges;

}

void Vertex::setEdges(std::set<PAA::Edge*>& aEdgeSet){

	this->arcs = aEdgeSet;
}

//Métodos para acesso e alteração do atributo 'previous'
Vertex* Vertex::getPreviousVertex(void) const{

	return this->previous;

}

void Vertex::setPreviousVertex(Vertex* aVertice){

	this->previous = aVertice;
}

//Adiciona um um aresta para um vértice
PAA::Edge* Vertex::addEdges(PAA::Edge* edge){
	std::stringstream ss;
	try {

		this->arcs.insert(edge);

	} catch (const std::exception& e) {

		ss << "Erro ao inserir a aresta " << edge->toString() << ". Detalhes:  "<< e.what() << std::endl;

		throw PAA::PAAException(ss.str());

	}
	this->arcs.insert(edge);

	return edge;

}

//Remove uma aresta de vértice
PAA::Edge* Vertex::removeEdge(PAA::Edge* edge){

}

//Número de aresta para vizinhos que são honesto
int Vertex::getNumberEdgesAA(void){

	std::set<PAA::Edge*>::iterator itArcs;
	int numberEdgesAA = 0;


	if(!this->getIsSybil()){
		//Se o vértice não é o honesto o valor de numberEdgesAA podera ser maior do que 0 (zero)

		for(itArcs = this->arcs.begin(); itArcs != this->arcs.end(); itArcs++){

			if(  !(*itArcs)->getFinishVertex()->getIsSybil()){
				//Se o vértice é honsto soma-se 1
				numberEdgesAA++;
			}


		}

	}else{
		//Para um vértice não honesto o valor será igual a 0 (zero)

		numberEdgesAA = 0;
	}

	return numberEdgesAA;

}

//Número de aresta para vértices não honesto (Sybil)
int Vertex::getNumberEdgesAB(void){

	std::set<PAA::Edge*>::iterator itArcs;
	int numberEdgesAB = 0;


	if(!this->getIsSybil()){
		//Se o vértice não é o honesto o valor de numberEdgesAB podera ser maior do que 0 (zero)

		for(itArcs = this->arcs.begin(); itArcs != this->arcs.end(); itArcs++){

			if(  (*itArcs)->getFinishVertex()->getIsSybil()){
				//Se o vértice é honsto soma-se 1
				numberEdgesAB++;
			}


		}

	}else{
		//Para um vértice não honesto o valor será igual a 0 (zero)

		numberEdgesAB = 0;
	}

	return numberEdgesAB;

}

//Número de aresta para vértices não honesto (Sybil)
int Vertex::getNumberEdgesBB(void){

	std::set<PAA::Edge*>::iterator itArcs;
	int numberEdgesBB = 0;

	if (this->getIsSybil()) {
		//Se o vértice não é o honesto o valor de numberEdgesAB podera ser maior do que 0 (zero)

		for (itArcs = this->arcs.begin(); itArcs != this->arcs.end();
				itArcs++) {

			if ((*itArcs)->getFinishVertex()->getIsSybil()) {
				//Se o vértice NÃO é honsto soma-se 1
				numberEdgesBB++;
			}

		}

	} else {
		//Para um vértice não honesto o valor será igual a 0 (zero)

		numberEdgesBB = 0;
	}

	return numberEdgesBB;
}

int Vertex::getNumberEdgesBA(void){

	std::set<PAA::Edge*>::iterator itArcs;
	int numberEdgesBA = 0;

	if (this->getIsSybil()) {
		//Se o vértice não é o honesto o valor de numberEdgesAB podera ser maior do que 0 (zero)

		for (itArcs = this->arcs.begin(); itArcs != this->arcs.end();
				itArcs++) {

			if ( ! (*itArcs)->getFinishVertex()->getIsSybil()) {
				//Se o vértice é honesto soma-se 1
				numberEdgesBA++;
			}

		}

	} else {
		//Para um vértice não honesto o valor será igual a 0 (zero)

		numberEdgesBA = 0;
	}

	return numberEdgesBA;
}

bool Vertex::operator <(const PAA::Vertex* other) const{


	return (this->getEdges().size() < other->getEdges().size());


}

int Vertex::getDegree(void){

	return this->getEdges().size();

}

int Vertex::getNeighbourhoodLength(void){

	int neighbourhoodLengt = 0;
	std::set<PAA::Edge*> edges;
	std::set<PAA::Edge*>::iterator itEdges;
	std::set<PAA::Edge*>::iterator itEdgesNeighbour;

	edges = this->getEdges();
	for(itEdges = edges.begin(); itEdges != edges.end(); itEdges++) {

		for(itEdgesNeighbour = (*itEdges)->getFinishVertex()->getEdges().begin(); itEdgesNeighbour != (*itEdges)->getFinishVertex()->getEdges().end(); itEdgesNeighbour++){

			if( (*itEdgesNeighbour)->getFinishVertex()->getName() == this->getName() ){
				 neighbourhoodLengt++;
			}
		}

	}

	return neighbourhoodLengt;
}

float Vertex::getCusteringCoefficient(void){
	float custeringCoefficient = 0.0;
	int neighbourhoodLengt = 0;
	int degree;

	neighbourhoodLengt = this->getNeighbourhoodLength();
	degree  = this->getDegree();

	if(neighbourhoodLengt == 0 || neighbourhoodLengt == 1 ){
		custeringCoefficient =  0.0;
	}else{

		custeringCoefficient = float ( float(degree) /  float ( (neighbourhoodLengt) * (neighbourhoodLengt-1)) );
	}
	return custeringCoefficient;
}


} /* namespace PAA */
