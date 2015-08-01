#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <math.h>
#include "Graph.hpp"
#include "FileParser.hpp"
#include "Vertex.hpp"

Graph::Graph(Graph::Direction direction, std::string const & filePath)
	: _direction(direction),
	_nbVertices(0),
	_nbEdges(0)
{
	aStarData data;

	FileParser::getAStarData(filePath, data);
	for (vtxDataVect::iterator it = data.vtc.begin(); it != data.vtc.end(); ++it)
		addVertex(it->name, it->x, it->y);
	
	for (edgeDataVect::iterator it = data.edges.begin(); it != data.edges.end(); ++it)
	{
		addEdge(it->src, it->dst, it->wt);
		_arcs.push_back(std::pair< std::string, std::string >(it->src, it->dst));
		_costs.push_back(it->wt);
	}

	std::sort(_vtcNames.begin(), _vtcNames.end());
}

Graph::~Graph()
{
	for (verticesVect::iterator it = _vertices.begin(); it != _vertices.end(); ++it)
		delete *it;
	for (edgesVect::iterator it = _edges.begin(); it != _edges.end(); ++it)
		delete *it;
}

void Graph::dijkstra(void)
{
	Vertex *x = getVertex("a");
	Vertex *y;
	std::list< Vertex * > processing;

	// Initialization of the root node
	x->setDistance(0);
	x->setStatus(Vertex::VISITING);
	processing.push_back(x);

	while (!processing.empty())
	{
		x = getSmallestDist(processing);

		// Check for each edge
		for (edgesVect::const_iterator it = x->getEdges().begin(); it != x->getEdges().end(); ++it)
		{
			y = (*it)->getDestination();
			if (y->getStatus() == Vertex::VISITED)
				continue;
			if (y->getDistance() > (x->getDistance() + (*it)->getWeight()))
			{
				y->setDistance(x->getDistance() + (*it)->getWeight());
				y->setPrev(x);
				//std::cout << y->getName() << "(d=" << y->getDistance()
				//<< ", p=" << y->getPrev()->getName() << ")" << std::endl;
			}
			if (y->getStatus() == Vertex::NOT_VISITED)
			{
				y->setStatus(Vertex::VISITING);
				processing.push_back(y);
			}
		}

		x->setStatus(Vertex::VISITED);
		processing.remove(x);
	}

	std::cout << "Shortest paths:" << std::endl;
	// Smallest cost to reach each vertex
	printSmallestCosts();
	// Individual path to each vertex and corresponding cost
	printShortestPaths();
}

void Graph::aStar(std::string const & target)
{
	Vertex			*x = getVertex("a"), *y = NULL, *tgt = getVertex(target);
	std::list< Vertex * >		processing;

	// Initialization of the root node
	x->setDistance(0);
	x->setHeuristic(sqrt(pow((tgt->getX() - x->getX()), 2) + pow(tgt->getY() - x->getY(), 2)));
	x->setStatus(Vertex::VISITING);
	processing.push_back(x);

	while (!processing.empty())
	{
		x = getSmallestDist(processing);
		/*
		std::cout << "Path being checked: " << x->getName()
		<< " (d=" << x->getDistance
		<< ", p=" << (x->getPrev() != NULL ? x->getPrev()->getName() : "None") << ")" << std::endl;
		*/

		// Check for each edge
		for (edgesVect::const_iterator it = x->getEdges().begin(); it != x->getEdges().end(); ++it)
		{
			y = (*it)->getDestination();
			if (y->getStatus() == Vertex::VISITED)
				continue;
			if (y->getHeuristic() == INFINITE)
				y->setHeuristic(sqrt(pow((tgt->getX() - y->getX()), 2) + pow(tgt->getY() - y->getY(), 2)));
			if (y->getDistance() > (x->getDistance() + (*it)->getWeight()))
			{
				y->setDistance(x->getDistance() + (*it)->getWeight());
				y->setPrev(x);
				//std::cout << y->getName() << "(d=" << y->getDistance()
				//<< ", p=" << y->getPrev()->getName() << ")" << std::endl;//
			}
			if (y->getStatus() == Vertex::NOT_VISITED)
			{
				y->setStatus(Vertex::VISITING);
				processing.push_back(y);
			}
		}
		
		x->setStatus(Vertex::VISITED);
		processing.remove(x);
	}
	
	std::cout << "Shortest paths:" << std::endl;
	// Smallest cost to reach each vertex
	printSmallestCosts();
	// Individual path to each vertex and corresponding cost
	printShortestPaths();
}

void Graph::printSmallestCosts(void)
{
	for (vtcNamesVect::iterator it = _vtcNames.begin(); it != _vtcNames.end(); ++it)
		std::cout << ((it == _vtcNames.begin()) ? "" : " ") << *it;
	std::cout << std::endl;
	
	for (vtcNamesVect::iterator it = _vtcNames.begin(); it != _vtcNames.end(); ++it)
		std::cout << ((it == _vtcNames.begin()) ? "" : " ") << getVertex(*it)->getDistance();
	std::cout << std::endl;
}

void Graph::printShortestPaths(void)
{
	Vertex *vtx;
	std::stack< Vertex * > stack;

	for (vtcNamesVect::iterator it = (_vtcNames.begin())++; it != _vtcNames.end(); ++it)
	{
		for (vtx = getVertex(*it); vtx != NULL; vtx = vtx->getPrev())
			stack.push(vtx);
		
		while (!stack.empty())
		{
			vtx = stack.top();
			std::cout << vtx->getName() << " ";
			stack.pop();
		}
		std::cout << vtx->getDistance() << std::endl;
	}
}

bool Graph::addVertex(std::string const & name, int x, int y)
{
	// Make sure that the vertex has not already been added
	if (std::find(_vtcNames.begin(), _vtcNames.end(), name) != _vtcNames.end())
		return false;

	_vtcNames.push_back(name);
	_vertices.push_back(new Vertex(name, x, y));
	++_nbVertices;
	return true;
}

bool Graph::addEdge(std::string const & src, std::string const & dst, int wt)
{
	Vertex *v1 = getVertex(src), *v2 = getVertex(dst);
	Edge *edge = new Edge(v1, v2, wt);

	_edges.push_back(edge);
	v1->addEdge(edge);
	if (_direction == UNDIRECTED)
		v2->addEdge(edge);
	++_nbEdges;
	
	return true;
}

Vertex * Graph::getVertex(std::string const & name) const
{
	for (verticesVect::const_iterator it = _vertices.begin(); it != _vertices.end(); ++it)
		if ((*it)->getName() == name)
			return *it;
	return NULL;
}

Vertex * Graph::getSmallestDist(std::list< Vertex * > lst) const
{
	Vertex	*vtx = NULL;
	int min = INFINITE;

	for (std::list< Vertex * >::const_iterator it = lst.begin(); it != lst.end(); ++it)
	{
		if ((*it)->getHeuristic() != INFINITE)
		{ // A* algorithm
			if ((*it)->getDistance() + (*it)->getHeuristic() < min)
			{
				min = (*it)->getDistance() + (*it)->getHeuristic();
				vtx = *it;
			}
		}
		else
		{ // Dijkstra algorithm
			if ((*it)->getDistance() < min)
			{
				min = (*it)->getDistance();
				vtx = *it;
			}
		}
	}
	
	return vtx;
}
