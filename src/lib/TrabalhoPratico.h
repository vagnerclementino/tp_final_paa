/*
 * TrabalhoPratico.h
 *
 *  Created on: 02/02/2015
 *      Author: Vagner Clementino
 *      Objetivo: Classe "abstrata" a fim de representar
 *      		  um trabalho prático (TP) genérico  com as
 *      		  funções e atributos comuns a todo trabalho
 *      		  prático.
 */

#ifndef TRABALHOPRATICO_H_
#define TRABALHOPRATICO_H_

#include <ctime>
#include <string>
#include "FileManager.h"
#define MAX_TIME_STRING 100			// Tamanho máximo que uma string representando a data/hora atual pode ter.
#define SECONDS_IN_A_DAY 864000		// Total de segundos em 1 dia
#define SECONDS_IN_A_HOUR 3600		// Total de segundos em 1 hora
#define SECONDS_IN_A_MIN 60			// Total de segundos em 1 minuto

namespace PAA {

class TrabalhoPratico {


private:
	struct tm* startTime; 		    // ponteiro para struct tm para o tempo de inicio de execução do Trabalho Prático
	struct tm* finalTime;		   //  ponteiro para struct tm para o tempo de finalização de execução do Trabalho Prático
	int argc;					  //   atributo para armazenar o atributo argc da função main
	char **argv;				 //    atributo para armazenar o atributo argv da função main
	bool writeLog;				//     Se TRUE, toda string passada para a função 'showUserMessage' será gravado no arquivo de log
	FileManager* logFile;	   //	   Ponteiro para classe FileManager para gerenciar o arquivo de log

protected:
	TrabalhoPratico();
	TrabalhoPratico(int , char**);
	virtual ~TrabalhoPratico();
	int getArgc(void);
	char** getArgv(void);

	/**********************************************************************
	 *
	 * 		Nome: run
	 * 		Função: Classe abstrata pura que deverá ser implementada
	 * 				com o corpo principal de execuçaõ do programa.
	 * 		Parâmetros: N/A
	 * 		Retorno: 	N/A
	 *
	 **********************************************************************/
	virtual void run(void)= 0;

	/*********************************************************************
	 *
	 * 		Nome: showUserMessage
	 * 		Função: Exibe mensagens ao usuário
	 * 		Parâmetros: uma string com a mensagem
	 * 					a ser passada ao usuário
	 *
	 * ******************************************************************/
	void showUserMessage(const std::string&);

	/*******************************************************************
	 *
	 * 		Nome: showStatistics
	 * 		Função: Exibe ao usuários as seguintes informações
	 *
	 * 					- Data/Hora de início da execução do programa
	 * 					- Data/Hora do final da execução do programa
	 * 					- Duração da execução do programa no formato "%H:%M:%S"
	 * 		Atributo: N/A
	 * 		Retorno:  N/A
	 *
	 * ********************************************************************/
	void showStatistics(void);

	/**********************************************************************
	 *
	 * 		Nome: 	  getSystemTime
	 * 		Função:   Retorna a data atual do sitema
	 * 		Atributo: N/A
	 * 		Retorno:  Struct do tipo tm com a data/hora
	 * 			      do sistema
	 *
	 * ********************************************************************/
	struct tm getSystemTime(void);

	/*********************************************************************
	 *
	 * 		Nome:	  setFinalTime
	 * 		Função:   define o tempo de finalização de execução
	 * 				  do trabalho prático
	 * 	    Atributo: N/A
	 * 	    Retorno:  N/A
	 *
	 * ******************************************************************/
	void setFinalTime(void);

	/******************************************************************
	 *
	 *	Nome:	   setLogFile
	 *	Função:  	Definir o nome do arquivo de log do programa
	 *	Atributo:  Uma string com o nome do arquivo
	 *	Retorno:   N/A
	 *
	 ******************************************************************/
	 void setLogFile(const std::string&);


	 /******************************************************************
	 *
	 * Nome: getFormatedTimeString
	 * Função: Retorna uma data/hora no formato
	 * DD/MM/YYYY - HH:MM:SS
	 * Atributo: struct do tipo tm
	 * Retorno: Uma string com a data/hora formatada
	 *
	 */
	 std::string getFormatedTimeString(const struct tm&) const;

};

} /* namespace PAA */

#endif /* TRABALHOPRATICO_H_ */
