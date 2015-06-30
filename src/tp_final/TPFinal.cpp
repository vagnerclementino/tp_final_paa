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



		ss << "Total de vértice no grafo: " <<  graph.getNumberOfVertex();
		this->showUserMessage(ss.str());

		finder.setTotalVertex(graph.getNumberOfVertex());

		//limpando o buffer string
		ss.str(std::string());


		this->showUserMessage("Buscando a cobertura de vertice aproximada para o grafo...");

		finder.getAproxVertexCover(graph);

		this->showUserMessage("Cobertura de vértice encontrada: ");
		finder.printVertexCover();

		this->showUserMessage("Calculando o Degree Access para os vértices no Cover Vertex...");
		finder.calculeAllDegreeAccess(graph);

		this->showUserMessage("Atribuindo valores aleatórios para a inclinação dos vértices...");
		//Atribuindo inclinações aleatórias para os vértices
		finder.setRandomInclination(graph);

		//Buscando o k maiores influenciadores
		ss << "Buscando os " << this->getValueK() << " maiores influenciadores...";
		this->showUserMessage(ss.str());
		//limpando o buffer string
		ss.str(std::string());
		finder.find(this->getValueK());

		graph.resetData();

		/*
		 * Realiza uma simulação para verificar quantas pessoas compraria um
		 * determinado produto caso os "influencers" iniciasse a recomendação do produto
		 */
		this->showUserMessage("Propagando a informação conforme o modelo de propagação Linear Threshold Model");
		finder.analyze(graph);

		//finder.printVertexCover();
		//finder.printInfluencers();
		//finder.printActiveVertex();



		finder.writeToFile(this->getOutputFileName());
		this->showUserMessage("Resultado escrito no arquivo " + this->getOutputFileName());

		this->setFinalTime();

	} catch (const PAA::PAAException& e) {

		throw e;
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
