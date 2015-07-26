#ifndef EDGE_HPP_
#define EDGE_HPP_

#include "utils.hpp"

class Vertex;

class Edge
{
public:
	Edge(Vertex *org, Vertex *dst, int weight = 0);
	~Edge();

	Vertex * getOrigin(void) const;
	Vertex * getDestination(void) const;
	int getWeight(void) const;

	void setWeight(int weight);

protected:
	Vertex *_origin;
	Vertex *_destination;
	int _weight;
};

#endif
