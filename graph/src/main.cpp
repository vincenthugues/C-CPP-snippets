#include <iostream>
#include "Edge.hpp"
#include "Matrix.hpp"
#include "Graph.hpp"

void run(std::string const & filePath)
{
	Graph graph(Graph::DIRECTED, filePath);

	std::cout << "Input file: " << filePath << std::endl
		<< "Vertices :" << graph.getNbVertices() << std::endl
		<< "Edges: " << graph.getNbEdges() << std::endl;

	// Edges
	arcsVect::const_iterator itArcs = graph.getArcs().begin();
	costsVect::const_iterator itCosts = graph.getCosts().begin();
	for (; itArcs != graph.getArcs().end(); ++itArcs, ++itCosts)
		std::cout << itArcs->first << " "
			<< itArcs->second << " "
			<< *itCosts << std::endl;

	graph.aStar("c");
}

int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
	{
		std::cout << "Usage: " << argv[0] << " file" << std::endl;
		return EXIT_SUCCESS;
	}
	try
	{
		srand(time(NULL));
		run(argv[1]);
	}
	catch (std::exception&)
	{
		std::cerr << "Exception: exiting program." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
