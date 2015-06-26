/*
 * TrabalhoPratico.cpp
 *
 *  Created on: 02/02/2015
 *      Author: vagner
 */

#include "TrabalhoPratico.h"
#include <ctime>
#include <iostream>
#include <exception>      // std::exception
#include <sstream>
#include "FileManager.h"
#include <iomanip>
#include <string>

using namespace std;
namespace PAA {

struct tm TrabalhoPratico::getSystemTime(void){
	time_t now = time(0);
	struct tm systemTime;

	systemTime = (*localtime(&now));


	return (systemTime);
}


TrabalhoPratico::TrabalhoPratico() {

	std::string logFileName("./paa.log");
	this->argc = 0;
	this->argv = NULL;

	this->startTime = new struct tm;

	*(this->startTime) = this->getSystemTime();

	this->finalTime = NULL;

	this->writeLog = true;

	this->logFile = new PAA::FileManager(logFileName, 'A');
}

TrabalhoPratico::TrabalhoPratico(int argc, char** argv){

	std::string logFileName("./paa.log");
	this->argc = argc;
	this->argv = argv;
	this->startTime = new struct tm;
	*(this->startTime) = this->getSystemTime();
	this->finalTime = NULL;
	this->writeLog = true;
	this->logFile = new FileManager(logFileName, 'A');
}

TrabalhoPratico::~TrabalhoPratico() {

	if (this->logFile != NULL){
		delete this->logFile;
	}

	if (this->startTime != NULL){
		delete this->startTime;
	}

	if (this->finalTime != NULL) {
		delete this->finalTime;
	}

}

void TrabalhoPratico::showUserMessage(const std::string& strMessage) {

	struct tm now;
	now =  this->getSystemTime();
	std::stringstream ss;

	ss << "[" << this->getFormatedTimeString(now) << "] : " << strMessage;


	if(this->writeLog){

		this->logFile->writeToFile(ss.str());

	}

	cout << ss.str() << std::endl;

}

void TrabalhoPratico::setFinalTime(void){

	if(this->finalTime == NULL){
		this->finalTime = new struct tm;
	}

	*(this->finalTime) =  this->getSystemTime();

}

std::string TrabalhoPratico::getFormatedTimeString(
		const struct tm& time) const {
	char timeString[MAX_TIME_STRING];
	if (strftime(timeString, sizeof(timeString), "%d/%m/%Y - %T", &time)) {
		return timeString;
	} else {
		throw std::exception();
	}
}

void TrabalhoPratico::showStatistics(void){

	time_t startTime, endTime, duration, timeLeft;
	int hours, minutes, seconds;

	startTime = mktime(this->startTime);
	endTime   = mktime(this->finalTime);
	duration = endTime - startTime;
	std::stringstream ss;
	std::string strOutput;

	timeLeft = duration;

	hours = int (timeLeft / SECONDS_IN_A_HOUR);

	timeLeft = timeLeft - (hours * SECONDS_IN_A_HOUR);

	minutes =  int(timeLeft / SECONDS_IN_A_MIN);

	seconds = timeLeft - (minutes * SECONDS_IN_A_MIN);

	this->showUserMessage("***** Dados da execucao *****");
	this->showUserMessage("Data/Hora de Inicio: " + this->getFormatedTimeString(*(this->startTime)));
	this->showUserMessage("Data/Hora de Termino: " + this->getFormatedTimeString(*(this->finalTime)));

	ss << "Duracao: " << std::setw(2) << std::setfill('0') <<hours << "h:"
			         << std::setw(2) << std::setfill('0') << minutes << "m:"
			         << std::setw(2) << std::setfill('0') << seconds << "s";

	this->showUserMessage(ss.str());

}

void TrabalhoPratico::setLogFile(const std::string& logFileName){

	this->logFile->openFile(logFileName,'A');

}

int TrabalhoPratico::getArgc(void){
	return this->argc;
}

char ** TrabalhoPratico::getArgv(void){

	return(this->argv);
}



} /* namespace PAA */
