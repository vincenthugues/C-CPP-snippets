#include <iostream>
#include "Edge.hpp"
#include "Vertex.hpp"

Edge::Edge(Vertex *org, Vertex *dst, int wt)
	: _origin(org), _destination(dst), _weight(wt)
{
	/*
	std::cout << "New edge: " << org->getName()
		<< "->" << dst->getName()
		<< " (" << wt << ")" << std::endl;
	*/
}

Edge::~Edge()
{
}

Vertex * Edge::getOrigin(void) const
{
	return _origin;
}

Vertex * Edge::getDestination(void) const
{
	return _destination;
}

int Edge::getWeight(void) const
{
	return _weight;
}

void Edge::setWeight(int weight)
{
	_weight = weight;
}
