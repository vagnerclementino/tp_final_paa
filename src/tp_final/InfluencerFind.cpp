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
	this->pFM = new PAA::FileManager();
	this->pVectorInfluencers = new std::vector<PAA::Vertex*>();
}

int InfluencerFind::getMaxInfluencers() const {
	return maxInfluencers;
}

void InfluencerFind::setMaxInfluencers(int maxInfluencers) {
	this->maxInfluencers = maxInfluencers;
}

InfluencerFind::~InfluencerFind() {
	if(this->pFM != NULL){
		delete pFM;
	}

	if(this->pVectorInfluencers != NULL){

		delete pVectorInfluencers;

	}
}

void InfluencerFind::find(PAA::PAAGraph& graph, int k){

	std::vector<PAA::Vertex*> influencers;
	std::vector<PAA::Vertex*> vertexCover;


	vertexCover = this->getVertexCover(graph);

	if(int(vertexCover.size()) <= k){

		influencers = vertexCover;

	}else{

		influencers = this->chooseInfluencersVertex(vertexCover,k);


	}

	if(this->pVectorInfluencers != NULL){

		*(this->pVectorInfluencers) = influencers;
	}

}
void InfluencerFind::printInfluencers(void) const{

	std::cout << this->generateStringToPrint(this->pVectorInfluencers) << std::endl;


}
void InfluencerFind::writeToFile(const std::string& fileName){
	try{
		this->openFile(fileName,'W');

		this->pFM->writeToFile(this->generateStringToPrint(this->pVectorInfluencers));

		this->closeFile(fileName);

	}catch (const PAA::PAAException& e) {

	throw PAA::PAAException("InfluencerFind::writeToFile", "Erro ao escrever no arquivo " + fileName);


	}


}

void InfluencerFind::openFile(const std::string& fileName, const char& mode){

	try {

		this->pFM->openFile(fileName, mode);

	} catch (const PAAException& e) {

		throw PAAException("InfluencerFind::openFile", "Erro ao abrir o arquivo " + fileName + "no modo " + mode);
	}

}
void InfluencerFind::closeFile(const std::string& fileName){

	try {

		this->pFM->closeFile();

	} catch (const PAA::PAAException& e) {

		throw PAAException("InfluencerFind::closeFile", "Erro ao abrir o arquivo " + fileName);
	}

}

std::string InfluencerFind::generateStringToPrint(std::vector<PAA::Vertex*>* influencers)const{
	std::vector<PAA::Vertex*>::iterator it;
	std::stringstream ss;
	int i = 0;

	if ( influencers!= NULL && influencers->empty()) {

		ss << "{ }" << std::endl;
	} else {

		ss << "{";

		for (it = influencers->begin();
				it != influencers->end(); it++) {
			if (i > 0) {
				ss << ", ";
			}
			i++;

			ss << (*it)->getName();

		}
		ss << "}";
	}

	return ss.str();

}

std::vector<PAA::Vertex*> InfluencerFind::getVertexCover(PAA::PAAGraph& graph){

	std::vector<PAA::Vertex*> vertexCover;



	return vertexCover;

}

std::vector<PAA::Vertex*> InfluencerFind::chooseInfluencersVertex(std::vector<PAA::Vertex*>& vertexCover, int k){
	std::vector<PAA::Vertex*> influencersVertex;


	return influencersVertex;
}

} /* namespace PAA */
