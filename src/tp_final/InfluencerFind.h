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
	int maxInfluencers; //número de máximo de influenciadores a serem localizados.

public:
	InfluencerFind();
	virtual ~InfluencerFind();
	void find(PAA::PAAGraph&,int);
	void analyze(PAA::PAAGraph&);
	void printInfluencers(void)const;
	void printVertexCover(void)const;
	void writeToFile(const std::string&);
	int getMaxInfluencers() const;
	void setMaxInfluencers(const int maxInfluencers);
	const std::vector<PAA::Vertex*>& getVectorInfluencers() const;
	const std::vector<PAA::Vertex*>& getVectorVertexCover() const;
	unsigned int getVertexConverSize(void);


private:
	//@methods
	void openFile(const std::string&, const char&);
	void closeFile(const std::string&);
	std::string generateStringToPrint(const std::vector<PAA::Vertex*>&) const;

	//Encontra a cobertura de vértice de vétice de um grafo. Algoritmo aproximando com R(n) = 2
	std::vector<PAA::Vertex*> getAproxVertexCover(PAA::PAAGraph&);

	//Escolhe k vértice de um conjunto de vértices candidatos
	std::vector<PAA::Vertex*> chooseInfluencersVertex(PAA::PAAGraph&, std::vector<PAA::Vertex*>&, int);

	//Remove de edgesSet toda aresta incidente para startVertex ou finishVertex
	int removeIncidentEdges(std::set<PAA::Edge*>&, PAA::Vertex*, PAA::Vertex*);

	//Retorna o número de vértices que podem ser acessados dado um vértice como raiz
	unsigned int calculeDegreeAccess(PAA::PAAGraph&, PAA::Vertex*);


	//Gera randomicamente um valor de inclination
	float generateRandomInclination(void);

	//Define um valor aleatório para cada vértice do grafo.
	void setRandomInclination(PAA::PAAGraph&);

	void setVectorInfluencers(const std::vector<PAA::Vertex*>& vectorInfluencers);

	void setVectorVertexCover(const std::vector<PAA::Vertex*>& vectorVertexCover);


};

} /* namespace PAA */

#endif /* INFLUENCERFIND_H_ */
