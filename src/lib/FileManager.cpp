/*
 * FileManager.cpp
 *
 *  Created on: 04/02/2015
 *      Author: vagner
 */

#include "FileManager.h"
#include "PAAException.h"
#include <sys/param.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <locale>
#include <sstream>
#include <vector>

namespace PAA {

FileManager::FileManager() {
	this->fileName = std::string();
	this->pFile = NULL;
	this->fileMode = NONE_MODE;
	this->lastRead = std::string();
	this->isEOF = false;

}

FileManager::FileManager(std::string& fileName, char fileMode){

	this->pFile = NULL;

	this->lastRead = std::string();

	this->isEOF = false;

	//Abrindo o arquivo e definindo o modo de abertura.
	this->openFile(fileName,fileMode);


}

FileManager::~FileManager() {
	if(this->pFile != NULL && this->pFile->is_open()){
		this->pFile->close();
		delete this->pFile;
	}
}

std::string FileManager::getCurrentDirectory(void) const {

	char *buffer = new char[MAXPATHLEN];

	getcwd(buffer, MAXPATHLEN);

	if (buffer != NULL) {
		std::string retString(buffer);
		delete[] buffer;
		return retString;
	} else {
		throw PAA::PAAException(
				"Erro no metodo getCurrentDirectory. Nao foi possivel recuperar o diretorio atual.");
	}

	}
std::string FileManager::getFileName(void)const{

	if (!this->fileName.empty()){

		return this->fileName;

	}else{
		throw PAA::PAAException("O nome do arquivo não foi definido.");
	}


}

bool FileManager::isfullPath(const std::string& path)const{

	std::size_t found;

	found = path.find_first_of(PATHSEPARATOR, 0);
	if (found == std::string::npos){
		return false;
	}else{
		return true;
	}
}

void FileManager::writeToFile(const std::string& str){

	if(this->pFile == NULL ){

		throw PAA::PAAException("Falha ao escrever no arquivo. O apontador do arquivo é NULL");

	}else if( ! this->pFile->good()){

		throw PAA::PAAException("Falha ao escrever no arquivo " + this->getFileName() + ". O arquivo não está aberto");

	} else{
		//Nenhum erro, a string pode ser escrita.

		*(this->pFile) << str << std::endl;

	 }
}

void FileManager::openFile(const std::string& fileName, char fileMode){

	std::string fileNameAux;

	if (this->isfullPath(fileName)) {

		fileNameAux = fileName;

	} else {

		fileNameAux = this->getCurrentDirectory() + PATHSEPARATOR + fileName;
	}





	if (this->pFile != NULL       && this->pFile->is_open() ) {

		if (this->fileName == fileNameAux && this->fileMode == fileMode)
		{
			throw PAA::PAAException("O arquivo " + this->fileName +
									" já esta aberto no modo " +
									this->fileMode + ". Nada a ser feito"
									);
		}
		else{

			this->closeFile();
			delete this->pFile;

		}

	}

	try{

		switch (std::toupper(fileMode)) {
			case APPEND_MODE:
				//Append mode
				this->pFile = new std::fstream(fileNameAux.c_str(),
						std::ios::out | std::ios::app);
				break;
			case WRITE_MODE:
				//Write mode
				this->pFile = new std::fstream(fileNameAux.c_str(), std::ios::out);
				break;
			case READ_MODE:
				//Read Mode
				this->pFile = new std::fstream(fileNameAux.c_str(), std::ios::in);
				break;
			default:
			throw PAAException(
					"O modo informado não existe. Os valores permitidos são A - append, W - write e R - read.");

		}

		if (this->pFile->good()) {

			this->fileName = fileNameAux;
			this->fileMode = fileMode;
			this->isEOF = false;

		} else {
			throw std::ios::failure("Erro na abertura do arquivo.");
		}

	} catch (const std::exception& e) {
		throw PAA::PAAException(
				"Erro ao tentar abrir o arquivo " + fileNameAux + ". Detalhes: "
						+ e.what());
	}


	}


void FileManager::closeFile(){
	if (this->pFile == NULL){
		throw PAA::PAAException("O arquivo não pode ser fechado. O apontador do arquivo é NULL");

	}else if (!this->pFile->is_open()){
		// O arquivo não está aberto
		throw PAA::PAAException("Falha em fechar o arquivo " + this->getFileName() + ". O arquivo não está aberto!");

	} else {
		try{
			this->pFile->close();
		} catch (const std::ios::failure& e){
			std::stringstream ss;
			ss << "Falha ao fechar o arquivo.  " <<  e.what() << std::endl;
			throw PAA::PAAException(ss.str());
		}
	}
}

bool FileManager::hasMore(void){

	bool hasMore = false;

	//Verificando se o apontador do arquivo é valido
	if(this->pFile == NULL){
		throw PAA::PAAException("Não foi possível ler linha do arquivo. O apontador  é NULL");

	};

	//Verificando se o arquivo foi aberto no modo de leitura
	if(this->fileMode != READ_MODE){

		throw PAA::PAAException("O arquivo " + this->getFileName() + " está no modo " + this->fileMode + ".Portanto o método FileManager::hasMore(void) não pode ser executado.");
	};

	//Verificando se o arquivo está aberto
	if(!this->pFile->is_open()) {

		throw PAA::PAAException("O arquivo " + this->getFileName() + " não está aberto.");

	};


	//Nenhum erro detectado. Leitura pode será ser realizada
	if (!this->isEOF && !this->pFile->eof()){

		//Realiza a leitura da linha do arquivo e armazena no "buffer" lastRead
		std::getline(*(this->pFile), this->lastRead);

		hasMore = true;

	} else{

		hasMore = false;
		this->isEOF = true;

	}

	return (hasMore);

}


std::string FileManager::readLine(void){

	std::string line;

	if (this->pFile == NULL){

		throw PAA::PAAException("Não foi possível ler linha do arquivo. O apontador  é NULL");

	} else 	if(this->pFile->is_open()){


		line = this->lastRead;

	} else{

		throw PAA::PAAException("O arquivo " + this->getFileName() + " não está aberto.");


	}

	return line;
}

std::vector<std::string> FileManager::splitString (const char *str, char delimiter){

	    std::vector<std::string> result;
	    std::string strValue;

	    do
	    {
	        const char *begin = str;

	        while(*str != delimiter && *str){
	            str++;
	        }
	        strValue = std::string(begin, str);
	        if(!strValue.empty()){



	        	if (!strValue.empty() && strValue.at(strValue.size() - 1) == '\r')
	        	    strValue.erase(strValue.size() - 1);

	        	result.push_back(strValue);
	        }

	    } while (0 != *str++);

	    return result;
}

}/* namespace PAA */
