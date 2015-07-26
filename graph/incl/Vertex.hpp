#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <string>
#include "utils.hpp"

class Vertex
{
public:
	enum Status { NOT_VISITED, VISITING, VISITED };

public:
	Vertex(std::string const & name, int x, int y);
	~Vertex();

	void			addEdge(Edge *edge);
	bool			removeEdge(Edge *edge);

	std::string const &	getName(void) const { return _name; }
	long double		getX(void) const { return _x; }
	long double		getY(void) const { return _y; }
	Status			getStatus(void) const { return _status; }
	long double		getDistance(void) const { return _distance; }
	long double		getHeuristic(void) const { return _heuristic; }
	Vertex *		getPrev(void) const { return _prev; }
	edgesVect const &	getEdges(void) const { return _edges; }

	void			setX(long double x) { _x = x; }
	void			setY(long double y) { _y = y; }
	void			setStatus(Status status) { _status = status; }
	void			setDistance(int distance) { _distance = distance; }
	void			setHeuristic(int heuristic) { _heuristic = heuristic; }
	void			setPrev(Vertex *prev) { _prev = prev; }

protected:
	std::string	_name;	// Name of the vertex
	long double	_x;		// x coordinate
	long double	_y;		// y coordinate
	Status		_status;	// Status of the vertex (visited or not)
	long double	_distance;	// Distance from the root node
	long double	_heuristic;	// Optimistic prediction of the distance to the target node
	Vertex *	_prev;		// Preceding vertex
	edgesVect	_edges;	// Vector of edges starting from the vertex
};

#endif
