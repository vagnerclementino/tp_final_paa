/*
 * PAAException.h
 *
 *  Created on: 02/02/2015
 *      Author: Vagner Clementino
 *      Objetivo: Classe de lança as exceções
 *      		  ocorridas no programas
 *      		  do trabalho prático da
 *      		  disciplina PAA.
 */

#ifndef PAAEXCEPTION_H_
#define PAAEXCEPTION_H_

#include <exception>
#include <string>

namespace PAA {

class PAAException: public std::exception {
private:
	std::string errorMessage;
	std::exception raisedException;


	/***************************************************************
	 *
	 *  	Toda exceção lançada deverá informar os motivos do
	 *  	lançamento da mesma, portanto, o construtor sem
	 *  	argumento não poderá ser chamado. *
	 *
	 * *************************************************************/
	PAAException();

public:

	PAAException (const std::string&, const std::exception&);
	PAAException (const std::string&);
	PAAException (const std::string&, const std::string&);
	void printDebugMessage(void) const ;
	std::string getDebugMessage(void) const;
	~PAAException() throw();
};

} /* namespace PAA */

#endif /* PAAEXCEPTION_H_ */
