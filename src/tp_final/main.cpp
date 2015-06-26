/*
 * main.cpp
 *
 *  Created on: 24/01/2015
 *      Author: vagner
 */
#include "../lib/PAAException.h"
#include "TPFinal.h"
#include <cstdlib>


using namespace std;



int main(int argc, char **argv) {


    try {

       	PAA::TPFinal tpFinal(argc,argv);
    	tpFinal.run();

    	//Exibindo os dados da execução
    	tpFinal.showStatistics();
    	exit(EXIT_SUCCESS);
	} catch (const PAA::PAAException& e) {
			e.printDebugMessage();
			exit(EXIT_FAILURE);
	}

}
