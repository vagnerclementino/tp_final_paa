/*
 * InfluencerFind.h
 *
 *  Created on: 25/06/2015
 *      Author: vagner
 */

#ifndef INFLUENCERFIND_H_
#define INFLUENCERFIND_H_
#include "../lib/FileManager.h"
#include "Vertex.h"
#include "PAAGraph.h"


namespace PAA {

class InfluencerFind {
private://atributes
	PAA::FileManager fm;
	std::vector<PAA::Vertex*> influencers;
	std::vector<PAA::Vertex*> vertexCover;
	std::vector<PAA::Vertex*> activeVertex;
	std::vector<PAA::Vertex*> candidateInfluencers;
	int maxInfluencers; //número de máximo de influenciadores a serem localizados.
	int totalVertex; // numero de veŕtice do grafo a ser analisado

public:
	InfluencerFind();
	virtual ~InfluencerFind();
	void find(unsigned int);
	void analyze(PAA::PAAGraph&);
	void printInfluencers(void)const;
	void printVertexCover(void)const;
	void printActiveVertex(void)const;
	void writeToFile(const std::string&);
	int getMaxInfluencers() const;
	void setMaxInfluencers(const int maxInfluencers);
	const std::vector<PAA::Vertex*>& getVectorInfluencers() const;
	const std::vector<PAA::Vertex*>& getVectorVertexCover() const;
	unsigned int getVertexConverSize(void);
	unsigned int getNumberActiveVertex(void);
	const std::vector<PAA::Vertex*>& getActiveVertex() const;
	void setActiveVertex(const std::vector<PAA::Vertex*>& activeVertex);
	//Encontra a cobertura de vértice de vétice de um grafo. Algoritmo aproximando com R(n) = 2
	void getAproxVertexCover(PAA::PAAGraph&);

	//Calcula o degree acess para todos os vertice do Vertex Cover
	void calculeAllDegreeAccess(PAA::PAAGraph&);

	float calculeActiveFraction(unsigned int) const;
	int getTotalVertex() const;
	void setTotalVertex(int totalVertex);
	//Define um valor aleatório para cada vértice do grafo.
	void setRandomInclination(PAA::PAAGraph&);
private:
	//@methods
	void openFile(const std::string&, const char&);
	void closeFile(const std::string&);
	std::string generateStringToPrint(const std::vector<PAA::Vertex*>&) const;



	//Escolhe k vértice de um conjunto de vértices candidatos
	std::vector<PAA::Vertex*> chooseInfluencersVertex(unsigned int);

	//Remove de edgesSet toda aresta incidente para startVertex ou finishVertex
	int removeIncidentEdges(std::set<PAA::Edge*>&, PAA::Vertex*, PAA::Vertex*);

	//Retorna o número de vértices que podem ser acessados dado um vértice como raiz
	unsigned int calculeDegreeAccess(PAA::PAAGraph&, PAA::Vertex*);


	//Gera randomicamente um valor de inclination
	float generateRandomInclination(float);



	void addActiveVertex(PAA::Vertex*);

	void setVectorInfluencers(const std::vector<PAA::Vertex*>& vectorInfluencers);

	void setVectorVertexCover(const std::vector<PAA::Vertex*>& vectorVertexCover);


};

} /* namespace PAA */

#endif /* INFLUENCERFIND_H_ */
