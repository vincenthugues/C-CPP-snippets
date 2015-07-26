#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <string>
#include <list>
#include <limits>
// #include "Edge.hpp"

#define MAX(a, b)		((a) > (b) ? (a) : (b))
#define MIN(a, b)		((a) < (b) ? (a) : (b))
#define INFINITE		std::numeric_limits<int>::max()

class Edge;
class Vertex;

typedef struct vtxData
{
	std::string	name;
	int		x;
	int		y;
} vtxData;

typedef struct edgeData
{
	std::string	src;
	std::string	dst;
	int		wt;
} edgeData;

typedef std::vector< vtxData >					vtxDataVect;
typedef std::vector< edgeData >				edgeDataVect;
typedef std::vector< std::pair< std::string, std::string > >	arcsVect;
typedef std::vector< int >					costsVect;
typedef std::vector< Vertex * >					verticesVect;
typedef std::vector< Edge * >					edgesVect;
typedef std::vector< std::string >				vtcNamesVect;
typedef std::pair< uint, uint >					BFSVtx;
typedef std::list< BFSVtx >					BFSVtxList;
typedef std::vector< std::list< std::string > >			adjListVect;

typedef struct dijArcs
{
	arcsVect	arcs;
	costsVect	costs;
} dijArcs;

typedef struct aStarData
{
	vtxDataVect	vtc;
	edgeDataVect	edges;
} aStarEdges;

#endif
