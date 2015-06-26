/*
 * FileManager.h
 *
 *  Created on: 04/02/2015
 *      Author: Vagner Clementino
 *      Objetivo: A classe visa abstrair toda operação relacionada
 *      		  com arquivos, tais como:
 *      		  -Abrir um arquivo
 *      		  -Fechar um arquivo
 *      		  -Ler um arquivo
 *      		  -Escrever em um arquivo
 *
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#define MAXPATHLEN 200 		//Tamanho máximo do caminho caminho de um arquivo
#define PATHSEPARATOR '/'   //O seperador de de arquivos e diretórios no linux
#define WRITE_MODE	'W'
#define READ_MODE	'R'
#define APPEND_MODE	'A'
#define NONE_MODE	'N' 	//Modo para quando nenhum arquivo foi aberto.

#include <string>
#include <fstream>
#include <vector>

namespace PAA {

class FileManager {

private:
	std::string fileName;

	std::fstream *pFile;

	char fileMode;

	std::string lastRead; //Armazena a última leitura realizada em um arquivo.

	bool isEOF; //Define se o arquivo chegou em EOF

	/*******************************************************************
	 *
	 *  	Nome: getCurrentDirectory
	 * 		Função: retornar o diretório de execução da aplicação.
	 * 		Parâmetros: N/A
	 * 		Retorno: Uma string com o diretório de execução da
	 * 				 aplicação.
	 *
	 * ***************************************************************/
	std::string getCurrentDirectory(void) const;

	/*****************************************************************
	 *
	 * 		Nome: isfullPath
	 * 		Função: Verificar se a string passada representa um
	 * 				caminho do sistema
	 * 	    Parametro: Uma string qualquer
	 *		Retorno:   TRUE se a string for um caminho do sistema
	 *				   FALSE, caso contrario
	 *
	 * **************************************************************/
	bool isfullPath(const std::string&)const;


public:
	FileManager();
	FileManager(std::string&, char);
	/****************************************************************
	 *
	 * 		Nome: getFileName
	 * 		Função: obter o nome do arquivo
	 * 		Parametro: N/A
	 * 		Retorno: uma string com o nome do arquivo.
	 *
	 * ***************************************************************/
	std::string getFileName(void)const;

	/****************************************************************
	 *
	 * 		Nome: openFile
	 * 		Função: abrir um arquivo com o nome informado
	 * 		Paramêtro: Uma string com o nome do arquivo;
	 * 				   Um caractere com o modo de abertura,
	 * 				   sendo os valores possíveis:
	 * 				     - W : modo de escrita, no qual
	 * 				     	   abertura de um novo arquivo
	 * 				     	   com o mesmo nome implica
	 * 				     	   em sobreescrever o arquivo
	 * 				     	   anterior.
	 * 				     -A:   modo de escrita, no qual
	 * 				     	   abertura de um novo arquivo
	 * 				     	   com o mesmo nome implica
	 * 				     	   na adição dos novos dados	 *
	 * 				     	   a partir do final da última
	 * 				     	   abertura do arquivo (append)
	 * 				      -R:  modo de leitura
	 * 		Retorno: N/A
	 *
	 * *************************************************************/
	void openFile(const std::string&, char);

	/*************************************************************
	 *
	 * 		Nome: closeFile
	 * 		Função: Fechar o arquivo gerenciado pela classe
	 * 		Parâmetros: N/A
	 * 		Retorno: N/A
	 *
	 * **********************************************************/
	void closeFile(void);

	/**********************************************************
	 *   	Nome: writeoFile
	 *   	Função:  Escreve a string informada no arquivo. O
	 *   		     arquivo deve ter sido aberto no modo de W ou
	 *   	     	 A.
	 *   	Parâmetro: Uma string a ser escrita
	 *   	Retorno: N/A
	 *
	 ******************************************************/
	void writeToFile(const std::string&);

	/********************************************************
	 * 		Nome:readLine
	 * 		Função: Ler uma linha de um arquivo. O arquivo
	 * 				deve estar aberto no modo de leitura
	 * 				'R'
	 * 	    Parâmetro: N/A
	 * 	    Retorno: Uma string com a linha lida do arquivo.
	 * 	    		 Tal linha pode estar NULA
	 *
	 * *****************************************************/
	std::string readLine(void);

	/********************************************************
	 *
	 * 		Nome: hasMore
	 * 		Função: Verifica se existem mais linha para ser lidas
	 * 				no arquivo.Na pratica verifica se o arquivo
	 * 			    chegou em EOF
	 * 	    Parâmetros: N/A
	 *		Retorno: TRUE, se existem mais linha para serem lidas
	 *				 FALSE, caso o arquivo esteja em EOF
	 *
	 ********************************************************/
	bool hasMore(void);

	std::vector<std::string> splitString (const char *str, char delimiter);

	virtual ~FileManager();
};

} /* namespace PAA */

#endif /* FILEMANAGER_H_ */
