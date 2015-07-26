#include <iostream>
#include <algorithm>
#include "Vertex.hpp"

Vertex::Vertex(std::string const & name, int x, int y)
	: _name(name),
	_x(x),
	_y(y),
	_status(NOT_VISITED),
	_distance(INFINITE),
	_heuristic(INFINITE),
	_prev(NULL)
{
	/*
	std::cout << "New vertex: " << name
		<< "(" << x << ", " << y << ")" << std::endl;
	*/
}

Vertex::~Vertex()
{
}

void Vertex::addEdge(Edge *edge)
{
	_edges.push_back(edge);
	/*
	std::cout << "Added edge from " << _name
		<< " to " << edge->getDestination()->getName()
		<< " (weight: " << edge->getWeight() << ")" << std::endl;
	*/
}

bool Vertex::removeEdge(Edge *edge)
{
	edgesVect::iterator it;

	// If the vertex has no such edge
	if ((it = std::find(_edges.begin(), _edges.end(), edge)) == _edges.end())
		return false;
	
	_edges.erase(it);
	
	return true;
}
