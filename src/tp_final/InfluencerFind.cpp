/*
 * InfluencerFind.cpp
 *
 *  Created on: 25/06/2015
 *      Author: vagner
 */

#include "InfluencerFind.h"
#include "../lib/PAAException.h"
#include <iostream>

namespace PAA {

InfluencerFind::InfluencerFind() {

	this->maxInfluencers = 0;
	this->fm= PAA::FileManager();
	this->influencers = std::vector<PAA::Vertex*>();
	this->vertexCover = std::vector<PAA::Vertex*>();
}

int InfluencerFind::getMaxInfluencers() const {
	return maxInfluencers;
}

void InfluencerFind::setMaxInfluencers(int maxInfluencers) {
	this->maxInfluencers = maxInfluencers;
}

InfluencerFind::~InfluencerFind() {
	//Não houve alocação dinamica
}

void InfluencerFind::find(PAA::PAAGraph& graph, int k){

	std::vector<PAA::Vertex*> influencers;
	std::vector<PAA::Vertex*> vertexCover;


	vertexCover = this->getAproxVertexCover(graph);


	this->setVectorVertexCover(vertexCover);

	if (int(vertexCover.size()) <= k){

		this->setVectorVertexCover(vertexCover);

	}else{

		influencers = this->chooseInfluencersVertex(vertexCover,k);

	}



}
void InfluencerFind::printInfluencers(void) const{
	try{

		std::cout << this->generateStringToPrint(this->getVectorInfluencers()) << std::endl;


	}catch (const PAAException& e) {

		throw e;

	}
}

void InfluencerFind::printVertexCover(void)const{

	try {

		std::cout << this->generateStringToPrint(this->getVectorVertexCover())
				<< std::endl;

	} catch (const PAAException& e) {

		throw e;

	}

}
void InfluencerFind::writeToFile(const std::string& fileName){
	try{
		this->openFile(fileName,'W');

		this->fm.writeToFile(this->generateStringToPrint(this->influencers));

		this->closeFile(fileName);

	}catch (const PAA::PAAException& e) {

	throw PAA::PAAException("InfluencerFind::writeToFile", "Erro ao escrever no arquivo " + fileName);


	}


}

void InfluencerFind::openFile(const std::string& fileName, const char& mode){

	try {

		this->fm.openFile(fileName, mode);

	} catch (const PAAException& e) {

		throw PAAException("InfluencerFind::openFile", "Erro ao abrir o arquivo " + fileName + "no modo " + mode);
	}

}
void InfluencerFind::closeFile(const std::string& fileName){

	try {

		this->fm.closeFile();

	} catch (const PAA::PAAException& e) {

		throw PAAException("InfluencerFind::closeFile", "Erro ao abrir o arquivo " + fileName);
	}

}

std::string InfluencerFind::generateStringToPrint(const std::vector<PAA::Vertex*>& influencers)const{


	std::stringstream ss;
	int i = 0;


	if ( influencers.empty()) {

		ss << "{ }" << std::endl;
	} else {

		ss << "{";

		for (unsigned int index = 0;index <= (influencers.size()-1); index++) {
			if (i > 0) {
				ss << ", ";
			}
			i++;

			ss << influencers.at(index)->getName();

		}
		ss << "}";
	}

	return ss.str();

}

std::vector<PAA::Vertex*> InfluencerFind::getAproxVertexCover(PAA::PAAGraph& graph){

	std::vector<PAA::Vertex*> aproxVertexCover;
	std::set<PAA::Edge*> edgesSet;
	std::set<PAA::Edge*>::iterator itEdges;
	PAA::Edge* edgeAux;
	PAA::Vertex* startVertex; //Start Vertex
	PAA::Vertex* finishVertex;// End Vertex
	int edgesRemoved = 0;



	edgesSet = graph.getEdgeSet();

	while(!edgesSet.empty()){

		itEdges = edgesSet.begin();

		edgeAux = (*itEdges);
		edgesSet.erase(edgeAux);

		//std::cout << edgeAux->toString() << std::endl;
		startVertex = edgeAux->getStartVertex();

		aproxVertexCover.push_back(startVertex);
		//std::cout << "Adicionado o vértice " << startVertex->toString() << " para o Vertex Cover" << std::endl;

		finishVertex = edgeAux->getFinishVertex();
		aproxVertexCover.push_back(finishVertex);
		//std::cout << "Adicionado o vértice " << finishVertex->toString() << " para o Vertex Cover" << std::endl;

		//Remove de edgesSet toda aresta incidente para startVertex ou finishVertex
		edgesRemoved += this->removeIncidentEdges(edgesSet,startVertex,finishVertex);
		//std::cout << "Arestas removidos até o momento : " << edgesRemoved << std::endl;


	}
	//std::cout << edgesSet.size() << std::endl;
	//std::cout << graph.getEdgeSet().size() << std::endl;


	return aproxVertexCover;

}

std::vector<PAA::Vertex*> InfluencerFind::chooseInfluencersVertex(std::vector<PAA::Vertex*>& vertexCover, int k){
	std::vector<PAA::Vertex*> influencersVertex;


	return influencersVertex;
}

const std::vector<PAA::Vertex*>& InfluencerFind::getVectorInfluencers() const {
	return this->influencers;
}

void InfluencerFind::setVectorInfluencers(const std::vector<PAA::Vertex*>& vectorInfluencers) {
	influencers = vectorInfluencers;
}

const std::vector<PAA::Vertex*>& InfluencerFind::getVectorVertexCover() const {
	return this->vertexCover;
}

void InfluencerFind::setVectorVertexCover(const std::vector<PAA::Vertex*>& vectorVertexCover) {
	this->vertexCover = vectorVertexCover;
}

int InfluencerFind::removeIncidentEdges(std::set<PAA::Edge*>& edgeSet, PAA::Vertex* startVertex, PAA::Vertex* finishVertex){

	std::set<PAA::Edge*>::iterator it;
	int edgeRemoved = edgeSet.size();


	for(it = edgeSet.begin(); it != edgeSet.end(); it++){



		if( (*it)->getStartVertex() == startVertex || (*it)->getFinishVertex() == startVertex){

			edgeSet.erase((*it));
			//std::cout << "Removido a a aresta " << (*it) ->toString() << std::endl;

		}

		if( (*it)->getStartVertex() == finishVertex || (*it)->getFinishVertex() == finishVertex){

			edgeSet.erase((*it));
			//std::cout << "Removido a a aresta " << (*it) ->toString() << std::endl;


		}
	}
	edgeRemoved -= edgeSet.size();

	return edgeRemoved;


}

unsigned int InfluencerFind::getVertexConverSize(void){

	return this->vertexCover.size();

}

} /* namespace PAA */
