#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include <string>
#include <algorithm>
#include "Edge.hpp"

class Graph
{
public:
	enum Direction { DIRECTED, UNDIRECTED };

public:
	Graph(Direction direction, std::string const & filePath);
	~Graph();

public: // Algorithm functions
	void			dijkstra(void);
	void			aStar(std::string const & target);
	void			printSmallestCosts(void);
	void			printShortestPaths(void);

public: // Utility functions
	bool			addVertex(std::string const & name, int x, int y);
	bool			addEdge(std::string const & src, std::string const & dst, int wt = 0);

public: // Getters
	arcsVect const & 	getArcs(void) const { return _arcs; }
	vtcNamesVect const &	getVtcNames(void) const { return _vtcNames; }
	costsVect const &	getCosts(void) const { return _costs; }
	adjListVect const &	getAdjList(void) const { return _adjList; }

	verticesVect const &	getVertices(void) const { return _vertices; }
	edgesVect const &	getEdges(void) const { return _edges; }

	Direction		getDirection(void) const { return _direction; }
	uint			getNbVertices(void) const { return _nbVertices; }
	uint			getNbEdges(void) const { return _nbEdges; }

protected: // Internal utility functions
	Vertex *		getVertex(std::string const & name) const;
	Vertex *		getSmallestDist(std::list< Vertex * > lst) const;

protected:
	arcsVect	_arcs;		// Vector of arcs (pairs of strings)
	vtcNamesVect	_vtcNames;	// Vector of vertices names (strings)
	costsVect	_costs;		// Vector of arcs costs (ints)
	adjListVect	_adjList;	// Vector of lists of vertices (strings)

	verticesVect	_vertices;	// Vector of vertices (Vertex *)
	edgesVect	_edges;	// Vector of edges (Edge *)

	Direction	_direction;	// Directed or undirected graph
	uint		_nbVertices;	// Number of vertices/nodes/points
	uint		_nbEdges;	// Number of edges/lines
};

#endif
