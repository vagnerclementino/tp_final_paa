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
#include <math.h>

namespace PAA {

InfluencerFind::InfluencerFind() {

	this->maxInfluencers = 0;
	this->fm= PAA::FileManager();
	this->influencers = std::vector<PAA::Vertex*>();
	this->vertexCover = std::vector<PAA::Vertex*>();
	this->activeVertex = std::vector<PAA::Vertex*>();
	this->candidateInfluencers = std::vector<PAA::Vertex*>() ;
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

void InfluencerFind::find(unsigned int k){

	std::vector<PAA::Vertex*> influencers;


	this->setVectorVertexCover(vertexCover);

	if (this->getVectorVertexCover().size() <= k){

		this->setVectorInfluencers(this->getVectorVertexCover());

	}else{

		influencers = this->chooseInfluencersVertex(k);

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

void InfluencerFind::printActiveVertex(void)const{


	try {

		std::cout << this->generateStringToPrint(this->getActiveVertex()) << std::endl;

	} catch (const PAAException& e) {

		throw e;

	}

}
void InfluencerFind::writeToFile(const std::string& fileName){
	try{
		std::stringstream ss;
		this->openFile(fileName,'W');

		ss << "#Total de Vértices no grafo" << std::endl;
		ss << this->getTotalVertex() << std::endl;

		ss<< "#Tamanho do vertex cover encontrado" << std::endl;
		ss << this->getVectorVertexCover().size() << std::endl;
		ss << "#Vertex Cover Aproximado" << std::endl;
		ss << this->generateStringToPrint(this->getVectorVertexCover()) << std::endl;

	    ss << "#Total de influenciadores"<< std::endl;
	    ss << this->getVectorInfluencers().size() << std::endl;
	    ss << "#Influenciadores encontrados"  << std::endl;
	    ss << this->generateStringToPrint(this->getVectorInfluencers())  << std::endl;

	    ss<<"#Total de vértices ativos"  << std::endl;
	    ss<< this->activeVertex.size()  << std::endl;
	    ss<< "#Vértices ativos"  << std::endl;
	    ss << this->generateStringToPrint(this->getActiveVertex()) << std::endl;
	    ss <<"#Fração de vértices ativos (|ATIVOS| / |V|)"  << std::endl;
	    ss << this->calculeActiveFraction(this->getTotalVertex()) << std::endl;
	    ss << "#####################################################"  << std::endl;




		this->fm.writeToFile(ss.str());

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

void InfluencerFind::getAproxVertexCover(PAA::PAAGraph& graph){

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


	this->setVectorVertexCover(aproxVertexCover);

}

void InfluencerFind::calculeAllDegreeAccess(PAA::PAAGraph& graph){

	std::vector<PAA::Vertex*>::iterator it;
	unsigned int degreeAcess = 0;
	unsigned int currentVertex = 0;
	unsigned int totalVertex = 0;

	totalVertex = this->vertexCover.size();


	for (it = vertexCover.begin(); it != vertexCover.end(); it++) {
		currentVertex++;
		std::cout << "Calculando o Degree Acess do vértice " << currentVertex << "/" << totalVertex << std::endl;

		degreeAcess = calculeDegreeAccess(graph, (*it));
		(*it)->setDegreeAccess(degreeAcess);
		//std::cout << "Grau de acesso do vertice " << (*it)->getName() << ": " << degreeAcess << std::endl;
		this->candidateInfluencers.push_back((*it));
		//std::cout << "Resetando o grafo." << std::endl;

		graph.resetData();

	}

	std::sort(this->candidateInfluencers.begin(),this->candidateInfluencers.end(),sortByDegreeAcces);

}
std::vector<PAA::Vertex*> InfluencerFind::chooseInfluencersVertex(unsigned int k){

	std::vector<PAA::Vertex*> returnVector(this->candidateInfluencers.begin(),this->candidateInfluencers.begin()+k);

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

const std::vector<PAA::Vertex*>& InfluencerFind::getActiveVertex() const {
	return activeVertex;
}

void InfluencerFind::setActiveVertex(
		const std::vector<PAA::Vertex*>& activeVertex) {
	this->activeVertex = activeVertex;
}

int InfluencerFind::getTotalVertex() const {
	return totalVertex;
}

void InfluencerFind::setTotalVertex(int totalVertex) {
	this->totalVertex = totalVertex;
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

	//std::cout << "Calculando DegreeAccess: " << root->getName() << std::endl;
	vertexQueue.push(root);



	while (!vertexQueue.empty()){

		auxVertex = vertexQueue.front();
		vertexQueue.pop();

		//std::cout << "Vertic em analise : " << auxVertex->getName() << std::endl;

		adjList = auxVertex->getAdjList();

		for(it = adjList.begin(); it != adjList.end(); it++){



			if((*it) == NULL){
				throw PAA::PAAException("InfluencerFind::calculeDegreeAccess", "Encontrado um vizinho no nulo no vértide " + root->getName());
			}

			//std::cout << "Vertice vizinho avaliado: " << (*it)->getName() << std::endl;
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


float InfluencerFind::generateRandomInclination(float seed){

	float randomInclination;

	int maxValue = int (seed * 100);

	if (maxValue == 0){
		randomInclination = 0;
	}else{

		randomInclination = float ( (rand() % maxValue) + 1 ) / 100;
	}



	return randomInclination;


}


void InfluencerFind::setRandomInclination(PAA::PAAGraph& graph){



	float randomInclination;
	float inclinatinoCumulative = 0.0;
	unsigned int currentVertex = 0;
	unsigned int totalVertex = 0;


	std::queue<PAA::Vertex*> vertexQueue;
	std::set<PAA::Vertex*> adjList;
	PAA::Vertex* auxVertex;
	std::set<PAA::Vertex*>::iterator it;
	std::set<PAA::Vertex*>::iterator itAdj;
	//Atribuindo uma semente aleatória
	srand(time(0));

	totalVertex = graph.getNumberOfVertex();

	for(it = graph.getVertexSet().begin(); it != graph.getVertexSet().end(); it++){

		vertexQueue.push((*it));
		currentVertex++;
		std::cout << "Atribuindo inclinação para o vertice  " << (*it)->getName() << " - " <<currentVertex << "/"<< totalVertex << std::endl;

		while (!vertexQueue.empty()) {

			auxVertex = vertexQueue.front();
			vertexQueue.pop();
			inclinatinoCumulative = 0.0;

			//std::cout << "Vertice em analise : " << auxVertex->getName()<< std::endl;

			if (auxVertex->getInclination() == 0) {
				auxVertex->setInclination(this->generateRandomInclination(1.0));
			}

			adjList = auxVertex->getAdjList();

			for (itAdj = adjList.begin(); itAdj != adjList.end(); itAdj++) {

				if ((*itAdj) == NULL) {
					throw PAA::PAAException(
							"InfluencerFind::setRandomInclination","Encontrado um vizinho no nulo no vértide " + auxVertex->getName());
				}

				//std::cout << "Vertice vizinho avaliado: " << (*itAdj)->getName() << std::endl;
				if ((*itAdj)->getColor() == WHITE) {
					(*itAdj)->setColor(GREY);

					inclinatinoCumulative += (*itAdj)->getInclination();

						if((*itAdj)->getInclination() == 0){

						if(inclinatinoCumulative < 1.0){
							while(true){

								randomInclination = this->generateRandomInclination(1.0 - inclinatinoCumulative);

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
				}else if ((*itAdj)->getColor() == BLACK){

					inclinatinoCumulative += (*itAdj)->getInclination();

				}

			}
			adjList.clear();
			auxVertex->setColor(BLACK);

		}

	}

}

void InfluencerFind::analyze(PAA::PAAGraph& graph){
	try {

		std::queue<PAA::Vertex*> vertexQueue;
		std::set<PAA::Vertex*> adjList;
		PAA::Vertex* auxVertex;
		std::set<PAA::Vertex*>::iterator it;
		std::set<PAA::Vertex*>::iterator itAdj;
		std::string influenceVertex;

		unsigned int influencersSize = 0;
		float inclinatinoCumulative = 0.0;

		//Atribuindo inclinações aleatórias para os vértices
		this->setRandomInclination(graph);

		graph.resetData();

		influencersSize = this->getVectorInfluencers().size();

		//Definindo os vértices do conjunto de influenciadores como ativo
		for(unsigned int index = 0; index <= (influencersSize -1); index++){

			influenceVertex = this->getVectorInfluencers().at(index)->getName();

			auxVertex = graph.getVertex(influenceVertex);

			auxVertex->setActive(true);

			this->addActiveVertex(auxVertex);
		}

		for (it = graph.getVertexSet().begin();	it != graph.getVertexSet().end(); it++) {

			vertexQueue.push((*it));

			while (!vertexQueue.empty()) {

				auxVertex = vertexQueue.front();
				vertexQueue.pop();
				inclinatinoCumulative = 0;

				//std::cout << "Vertice em analise : " << auxVertex->getName() << std::endl;

				adjList = auxVertex->getAdjList();

				for (itAdj = adjList.begin(); itAdj != adjList.end(); itAdj++) {

					if ((*itAdj) == NULL) {
						throw PAA::PAAException("InfluencerFind::analyze","Encontrado um vizinho no nulo no vértide " + auxVertex->getName());
					}

					//std::cout << "Vertice vizinho avaliado: "<< (*itAdj)->getName() << std::endl;

					if ((*itAdj)->getColor() == WHITE) {
						(*itAdj)->setColor(GREY);

						if((*itAdj)->isActive()){

							inclinatinoCumulative += (*itAdj)->getInclination();

						}
						vertexQueue.push((*itAdj));

					}

				}
				adjList.clear();
				auxVertex->setColor(BLACK);

				if(inclinatinoCumulative >= auxVertex->getInclination()){

					auxVertex->setActive(true);

					this->addActiveVertex(auxVertex);

				}
			}

		}

	} catch (const PAA::PAAException& e) {

		throw e;
	}

}

void InfluencerFind::addActiveVertex(PAA::Vertex* activeVertex){

  if(std::find(this->activeVertex.begin(),this->activeVertex.end(),activeVertex) == this->activeVertex.end()){

	  this->activeVertex.push_back(activeVertex);

  }

}

unsigned int InfluencerFind::getNumberActiveVertex(void){

	return this->activeVertex.size();

}


float InfluencerFind::calculeActiveFraction(unsigned int totalVertex) const{

	if(totalVertex == 0){
		return 0;
	}

	float activeFraction =  ( float(this->activeVertex.size()) / float(totalVertex) );

	return floorf (activeFraction * 100 ) / 100;
}

} /* namespace PAA */
