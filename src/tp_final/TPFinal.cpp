/*
 * TPFinal.cpp
 *
 *  Created on: 25/06/2015
 *      Author: vagner
 */

#include "TPFinal.h"
#include <sstream>
#include <stdexcept>      // std::out_of_range
#include "../lib/PAAException.h"
#include "PAAGraph.h"
#include "InfluencerFind.h"
#include <stdlib.h>

namespace PAA {

TPFinal::TPFinal(int numArgs, char** args):TrabalhoPratico(numArgs, args) {
	std::stringstream ss;
	if(numArgs == this->NUMBER_OF_ARGUMENTS) {

		this->pProgArgs = new std::vector<std::string> (args, args + numArgs);

	} else {
		ss << "O numero de argumentos informado: "<< numArgs << " não é valido!" << std::endl;
		throw PAA::PAAException("TPFinal::TPFinal( )", ss.str());
	}
}

TPFinal::~TPFinal() {

	if(this->pProgArgs != NULL){

		delete this->pProgArgs;
	}
}

void TPFinal::showUserMessage(const std::string& message){
	PAA::TrabalhoPratico::showUserMessage(message);
}

void TPFinal::showStatistics(void){
	PAA::TrabalhoPratico::showStatistics();
}

void TPFinal::run(void){

	try {
		PAA::PAAGraph graph;
		std::stringstream ss;
		PAA::InfluencerFind finder;

		this->showUserMessage("Iniciando a carga do grafo atraves do arquivo " + this->getInputFileName());
		graph.load(this->getInputFileName());
		this->showUserMessage("Finalizando a carga do grafo.");

		ss << "Número de vértices adicionados: " <<  graph.getNumberOfVertex() << std::endl;
		this->showUserMessage(ss.str());

		finder.find(graph,this->getValueK());

		finder.printInfluencers();

		finder.writeToFile(this->getOutputFileName());

		this->setFinalTime();

	} catch (const PAA::PAAException& e) {

		throw PAAException(e.getDebugMessage());
	}


}

void TPFinal::setFinalTime(void){

	PAA::TrabalhoPratico::setFinalTime();

}

const std::string& TPFinal::getProgramName(void)const{
	try{
		return this->pProgArgs->at(this->PROGRAM_NAME_POSITION);
	}catch (const std::out_of_range& oor) {

		throw PAA::PAAException("TPFinal::getProgramName", "O indice informado não é válido: " + this->PROGRAM_NAME_POSITION);

	}
}

const std::string& TPFinal::getInputFileName(void)const{

	try{
		return this->pProgArgs->at(this->INPUT_FILE_POS);
	}catch (const std::out_of_range& oor) {

		throw PAA::PAAException("TPFinal::getInputFileName", "Erro em recuperar a string de localização do arquivo de entrada. O indice informado não é válido: " + this->INPUT_FILE_POS);

	}

}
const std::string& TPFinal::getOutputFileName(void)const{

	try {
		return this->pProgArgs->at(this->OUTPUT_FILE_POS);
	} catch (const std::out_of_range& oor) {

		throw PAA::PAAException("TPFinal::getOutputFileName",
				"Erro em recuperar a string de localização do arquivo de entrada. O indice informado não é válido: "
						+ this->OUTPUT_FILE_POS);

	}

}

int TPFinal::getValueK(void) const{

		try {

			return atoi(this->pProgArgs->at(this->K_VALUE_POS).c_str());

		} catch (const std::out_of_range& oor) {

			throw PAA::PAAException("TPFinal::getValueK",
					"Erro em recuperar o tamanho k de influenciadores. O indice informado não é válido: "
							+ this->K_VALUE_POS);

		}


}

} /* namespace PAA */
