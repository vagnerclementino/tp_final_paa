/*
 * Edge.h
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#ifndef EDGE_H_
#define EDGE_H_
#include <string>
#include "Vertex.h"
#include <sstream>

namespace PAA {

class Vertex;

class Edge {
private:
	PAA::Vertex* start;    // Vértice no início de uma aresta
	PAA::Vertex* finish;   // Vértice do fim de uma aresta
	double cost;      	   // O custo/peso de uma aresta
	double& weight;   	  // alias para custo; ambos serão os mesmo atributo
	bool visited;         // Define se uma aresta foi visitada


public:

	Edge(PAA::Vertex* start = NULL, PAA::Vertex* finish = NULL, double cost = 0.0);
	virtual ~Edge();

	//Métodos para acesso e manipulação do atributo start
	PAA::Vertex* getStartVertex(void)const;
	void setStartVertex(PAA::Vertex*);

	//Métodos para acesso e manipulação do atributo finish
	PAA::Vertex* getFinishVertex(void)const;
	void setFinishVertex(PAA::Vertex*);

	//Métodos para acesso e manipulação do atributo cost/weight
	double& getWeight(void) const;
	void setWeight(double);

	//Métodos para acesso e manipulação do atributo visited
	bool getVisited(void) const;
	void setVisited(bool);

	//Retorna os valores de uma aresta para seu valor padrão
	 void resetData();

	 //Retorna uma string que representa uma string
	 std::string toString() const;

	 //Define o operador de cópia entre duas arestas;
     Edge& operator =(const Edge&);

     //Operador que permite a impressão de uma aresta diretamente em uma stream

};

	std::ostream& operator<<(std::ostream& out, const PAA::Edge& edge);
} /* namespace PAA */

#endif /* EDGE_H_ */
