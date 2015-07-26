#include <iostream>
#include <fstream>
#include "FileParser.hpp"

const arcsVect FileParser::getArcs(const std::string & path)
{
	std::ifstream file(path.c_str(), std::ifstream::out);
	std::string f, s;
	arcsVect Arcs;

	if (!file.good())
	{
		std::cerr << "Error while opening " << path << "." << std::endl;
		throw new std::exception;
	}
	
	std::getline(file, f);
	while (file.good())
	{
		std::getline(file, f, ' ');
		if (!file.eof())
		{
			std::getline(file, s);
			Arcs.push_back(std::pair<std::string, std::string>(f, s));
		}
	}
	
	return Arcs;
}

const dijArcs FileParser::getDijArcs(const std::string & path)
{
	std::ifstream file(path.c_str(), std::ifstream::out);
	std::string f, s, t;
	arcsVect Arcs;
	costsVect Costs;
	dijArcs dij;

	if (!file.good())
	{
		std::cerr << "Error while opening " << path << "." << std::endl;
		throw new std::exception;
	}
	
	std::getline(file, f);
	while (file.good())
	{
		std::getline(file, f, ' ');
		if (!file.eof())
		{
			std::getline(file, s, ' ');
			std::getline(file, t);
			Arcs.push_back(std::pair<std::string, std::string>(f, s));
			Costs.push_back(atoi(t.c_str()));
		}
	}
	
	dij.arcs = Arcs;
	dij.costs = Costs;

	return dij;
}

bool FileParser::getAStarData(const std::string & path, aStarData & data)
{
	std::ifstream file(path.c_str(), std::ifstream::out);
	std::string items[4];
	vtxData vtx;
	edgeData edge;

	if (!file.good())
	{
		std::cerr << "Error while opening " << path << "." << std::endl;
		throw new std::exception;
	}
	while (file.good())
	{
		std::getline(file, items[0], ' ');
		if (file.eof())
			break;
		if (items[0].empty())
			continue;
		if (items[0] != "vertex" && items[0] != "edge")
		{
			std::cout << "[IGNORED] " << items[0] << " ";
			std::getline(file, items[0]);
			std::cout << items[0] << std::endl;
			continue;
		}
		
		std::getline(file, items[1], ' ');
		if (file.eof())
			break;
		std::getline(file, items[2], ' ');
		if (file.eof())
			break;
		std::getline(file, items[3]);
		if (file.eof())
			break;
		
		if (items[0].empty() || items[1].empty() || items[2].empty() || items[0][0] == '#')
		{
			//std::cout << "[ERROR] -> " << items[0] << " " << items[1] << " " << items[2];
			std::getline(file, items[0]);
			std::cout << " " << items[0] << std::endl;
			continue;
		}

		if (items[0] == "vertex")
		{
			vtx.name = items[1];
			vtx.x = atoi(items[2].c_str());
			vtx.y = atoi(items[3].c_str());
			data.vtc.push_back(vtx);
			//std::cout << "Vertex " << vtx.name << "(" << vtx.x << ", " << vtx.y << ")" << " added." << std::endl;
		}
		else if (items[0] == "edge")
		{
			edge.src = items[1];
			edge.dst = items[2];
			edge.wt = atoi(items[3].c_str());
			data.edges.push_back(edge);
			//std::cout << "Edge " << edge.src << "->" << edge.dst << " (" << edge.wt << ")" << " added." << std::endl;
		}
		else
		{
			//std::cout << "[FAILURE] -> " << items[0] << std::endl;
			//std::getline(file, items[0]);
			//std::cout << " " << items[0] << std::endl;
		}
	}
	
	return true;
}
