/*
 * TPFinal.h
 *
 *  Created on: 25/06/2015
 *      Author: vagner
 */

#ifndef TPFINAL_H_
#define TPFINAL_H_
#include <vector>
#include "../lib/TrabalhoPratico.h"

namespace PAA {

class TPFinal: public TrabalhoPratico {
private:
	//@atributes
	//Definindo o número de argumentos do programa
	static const int NUMBER_OF_ARGUMENTS = 5;

	//Definindo a posição do nome do programa
	static const int PROGRAM_NAME_POSITION = 0;

	//Definindo a posição do arquivo de entrada
	static const int INPUT_FILE_POS = 2;

	//Definindo a posição do arquivo de saida
	static const int OUTPUT_FILE_POS = 4;

	//Armazena os argumentos do programa
	std::vector<std::string>* pProgArgs;


private:
		//@methods
		//@override Define o tempo final de execução
		void setFinalTime(void);





public:
	TPFinal(int,char**);
	virtual ~TPFinal();

	//@override
	void run(void);

	//@override
	void showUserMessage(const std::string&);

	//@override
	void showStatistics(void);

	//Retorna o nome do programa
	const std::string& getProgramName(void)const;

	const std::string& getInputFileName(void)const;
};


} /* namespace PAA */

#endif /* TPFINAL_H_ */
