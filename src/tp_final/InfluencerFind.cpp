/*
 * InfluencerFind.cpp
 *
 *  Created on: 25/06/2015
 *      Author: vagner
 */

#include "InfluencerFind.h"
#include "../lib/PAAException.h"
#include <iostream>
#include <queue>
#include <algorithm>

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

		influencers = this->chooseInfluencersVertex(graph,vertexCover,k);

		this->setVectorInfluencers(influencers);

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

			ss << "Name: " << influencers.at(index)->getName() << ",";
			ss << "Degree Access: " << influencers.at(index)->getDegreeAccess();
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

std::vector<PAA::Vertex*> InfluencerFind::chooseInfluencersVertex(PAA::PAAGraph& graph, std::vector<PAA::Vertex*>& vertexCover, int k){

	std::vector<PAA::Vertex*> influencersVertex;
	std::vector<PAA::Vertex*>::iterator it;
	unsigned int degreeAcess = 0;

	for(it = vertexCover.begin(); it != vertexCover.end(); it++){

		degreeAcess = calculeDegreeAccess(graph, (*it));
		(*it)->setDegreeAccess(degreeAcess);
		std::cout << "Grau de acesso do vertice " << (*it)->getName() << ": " << degreeAcess << std::endl;
		influencersVertex.push_back((*it));
		//std::cout << "Resetando o grafo." << std::endl;

		graph.resetData();

	}

	std::sort(influencersVertex.begin(),influencersVertex.end(),sortByDegreeAcces);


	std::vector<PAA::Vertex*> returnVector(influencersVertex.begin(),influencersVertex.begin()+k);

	return returnVector;
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

unsigned int InfluencerFind::calculeDegreeAccess(PAA::PAAGraph& graph, PAA::Vertex* root){

	unsigned int degreeAccess = 0;
	std::queue<PAA::Vertex*> vertexQueue;
	std::set<PAA::Vertex*> adjList;
	PAA::Vertex* auxVertex;
	std::set<PAA::Vertex*>::iterator it;

	std::cout << "Calculando DegreeAccess: " << root->getName() << std::endl;
	vertexQueue.push(root);



	while (!vertexQueue.empty()){

		auxVertex = vertexQueue.front();
		vertexQueue.pop();

		std::cout << "Vertic em analise : " << auxVertex->getName() << std::endl;

		adjList = auxVertex->getAdjList();

		for(it = adjList.begin(); it != adjList.end(); it++){



			if((*it) == NULL){
				throw PAA::PAAException("InfluencerFind::calculeDegreeAccess", "Encontrado um vizinho no nulo no vértide " + root->getName());
			}

			std::cout << "Vertice vizinho avaliado: " << (*it)->getName() << std::endl;
			if((*it)->getColor() == WHITE){
				(*it)->setColor(GREY);
				degreeAccess++;
				vertexQueue.push((*it));
			}

		}
		adjList.clear();
		auxVertex->setColor(BLACK);

	}
	return degreeAccess;
}


float InfluencerFind::generateRandomInclination(void){

	float randomInclination;

	randomInclination = float ( (rand() % 100) + 1 ) / 100;

	return randomInclination;


}


void InfluencerFind::setRandomInclination(PAA::PAAGraph& graph){



	float randomInclination;
	float inclinatinoCumulative = 0.0;


	std::queue<PAA::Vertex*> vertexQueue;
	std::set<PAA::Vertex*> adjList;
	PAA::Vertex* auxVertex;
	std::set<PAA::Vertex*>::iterator it;
	std::set<PAA::Vertex*>::iterator itAdj;
	//Atribuindo uma semente aleatória
	srand(time(0));

	for(it = graph.getVertexSet().begin(); it != graph.getVertexSet().end(); it++){

		randomInclination = this->generateRandomInclination();

		(*it)->setInclination(randomInclination);

		std::cout << "Atrubuida a inclination " << (*it)->getInclination()
				<< " para o vértice " << (*it)->getName() << std::endl;


		vertexQueue.push((*it));

		while (!vertexQueue.empty()) {

			auxVertex = vertexQueue.front();
			vertexQueue.pop();
			inclinatinoCumulative = 0.0;

			std::cout << "Vertice em analise : " << auxVertex->getName()<< std::endl;

			if(auxVertex->getInclination() == 0){
				auxVertex->setInclination(this->generateRandomInclination());
			}

			adjList = auxVertex->getAdjList();

			for (itAdj = adjList.begin(); itAdj != adjList.end(); itAdj++) {

				if ((*itAdj) == NULL) {
					throw PAA::PAAException(
							"InfluencerFind::setRandomInclination","Encontrado um vizinho no nulo no vértide " + auxVertex->getName());
				}

				std::cout << "Vertice vizinho avaliado: " << (*itAdj)->getName() << std::endl;
				if ((*itAdj)->getColor() == WHITE) {
					(*itAdj)->setColor(GREY);

					inclinatinoCumulative += (*itAdj)->getInclination();

					if(inclinatinoCumulative < 1.0){
						while(true){

							randomInclination = this->generateRandomInclination();

							std::cout << (randomInclination + inclinatinoCumulative ) << std::endl;

							if(float(randomInclination + inclinatinoCumulative ) <= 1.0){
								break;

							}

						};

						(*itAdj)->setInclination(randomInclination);

						inclinatinoCumulative+=randomInclination;

					}else{

						(*itAdj)->setInclination(0);
					}

					vertexQueue.push((*itAdj));
				}

			}
			adjList.clear();
			auxVertex->setColor(BLACK);

		}

	}

}

void InfluencerFind::analyze(PAA::PAAGraph& graph){
	try {
		this->setRandomInclination(graph);


	} catch (const PAA::PAAException& e) {

		throw e;
	}

}

} /* namespace PAA */
