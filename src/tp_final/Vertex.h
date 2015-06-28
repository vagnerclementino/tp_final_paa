/*
 * Vertex.h
 *
 *  Created on: 14/06/2015
 *      Author: Vagner Clementino
 */

#ifndef VERTEX_H_
#define VERTEX_H_
#include <set>
#include <string>
#include "Edge.h"



namespace PAA {

class Edge;

enum Color{
		WHITE = 0,
		GREY = 1,
		BLACK = 2
	};



class Vertex {

private:
	std::string name;    		  // Nome ou label do vértice
	std::set<PAA::Edge*> arcs;    // Lista de aresta que deixam o vértice
	std::set<PAA::Edge*>& edges;  // Definindo um alias para o arcs
	double cost;        		  // Custo para alcançar este vértices, valor padrão igual a 0 (zero)
	bool visited;       		 // Define se o vértice já foi visitado; valor padrão igual false
	PAA::Color color;			// Define a cor de vértice; valor padrão BRANCO
	Vertex* previous;   		// Vértice que vem antes deste, valor padrão igual a NULL
	bool isSybil;				// Define se o um vértice é Sybil - Default TRUE
	unsigned int  degreeAccess;  //Define o número de vertice que podem ser acessados a partir deste
	float inclination;			 //Determina o quanto um vértice (pessoa) deseja comprar um produto, deve ser no máximo 1
	bool active;				 //Se true o vertice (pessoa) comprou o produto, do contrário, ela não o adquiriu
public:
	Vertex(const std::string& name = "");
	//Construtor para construçaõ de uma cópia
	Vertex(const Vertex& other);
	virtual ~Vertex();

	//Métodos para acesso e alteração do atributo 'Name'
	const std::string& getName(void)const;
	void setName(const std::string&);

	//Métodos para acesso e alteração do atributo 'Cost'
	double getCost(void)const;
	void setCost(double);

	//Métodos para acesso e alteração do atributo 'Visited'
	bool getVisited(void)const;
	void setVisited(bool);

	//Métodos para acesso e alteração do atributo 'Color'
	PAA::Color getColor(void) const;
	void setColor(PAA::Color newColor);

	//Métodos para acesso e alteração do atributo 'Edges'
	std::set<Edge*>& getEdges(void) const;
	void setEdges(std::set<Edge*>&);

	//Métodos para acesso e alteração do atributo 'previous'
	Vertex* getPreviousVertex(void) const;
	void setPreviousVertex(Vertex*);

	//Métodos para acesso e alteração do atributo 'isSybil'
	bool getIsSybil(void) const;
	void setIsSybil(bool);

	//Retorna os valores dos atributos para seu valor padrão
	void resetData(void);

	//Retorna uma string represetando o vértice
	std::string toString() const;

	//Atributo de cópia de veŕtice para outro
	Vertex& operator =(const Vertex& other);

	//Adiciona um um aresta para um vértice
	PAA::Edge* addEdges(PAA::Edge*);

	//Remove uma aresta de vértice
	PAA::Edge* removeEdge(PAA::Edge*);

	//Número de aresta para vizinhos que são honesto
	int getNumberEdgesAA(void);

	//Número de aresta para vértices não honesto (Sybil)
	int getNumberEdgesAB(void);

	//Número de aresta para vértices não honesto (Sybil)
	int getNumberEdgesBB(void);

	//Número de aresta para vértices não honesto (Sybil) para vértices honestos
	int getNumberEdgesBA(void);

	//Verifica se um vértice é maior do que o outro
	bool operator <(const PAA::Vertex*)const ;

	//Retorna o grau de um vértice
	int getDegree(void);

	//Retorna o número de vértice vizinhos que atendem a regra N_i = { v_j: e_ij in E AND  e_ji in E}
	int getNeighbourhoodLength(void);

	//Calcula o coeficiente de agrupamento de um vértice
	float getCusteringCoefficient(void);

	std::set<PAA::Vertex*> getAdjList(void) const;
	unsigned int getDegreeAccess() const;
	void setDegreeAccess(unsigned int degreeAccess);
	float getInclination() const;
	void setInclination(float inclination);
};

	//Método para permitir que o vértice seja impresso em stream de saída
	std::ostream& operator<<(std::ostream& out, const Vertex& v);

	bool sortByDegree(PAA::Vertex* v1, PAA::Vertex* v2);

	bool sortByName(PAA::Vertex* v1, PAA::Vertex* v2);

	bool sortByDegreeAcces(PAA::Vertex* v1, PAA::Vertex* v2);


} /* namespace PAA */

#endif /* VERTEX_H_ */
