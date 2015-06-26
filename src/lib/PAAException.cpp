/*
 * PAAException.cpp
 *
 *  Created on: 02/02/2015
 *      Author: Vagner Clementino
 */

#include "PAAException.h"
#include <iostream>
#include <sstream>

namespace PAA {

PAAException::PAAException():exception() {
	//Do nothing. Construtor privado.

}

PAAException::PAAException (const std::string& eMessage)

 {

	this->errorMessage = eMessage;

}

PAAException::PAAException (const std::string& moduloName="NAO INFORMADO", const std::string& eMessage="Não informada"){
	std::string errorMessage = "Erro no módulo/método: << " + moduloName + " >> Detalhes: " + eMessage;
	this->errorMessage = errorMessage;

}

void PAAException::printDebugMessage(void)const{



	std::cerr << this->errorMessage << std::endl;



}

std::string PAAException::getDebugMessage(void) const{
	return this->errorMessage;
}

PAAException::~PAAException() throw(){


}

} /* namespace PAA */
