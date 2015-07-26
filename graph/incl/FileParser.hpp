#ifndef FILEPARSER_HPP__
#define FILEPARSER_HPP__

#include <string>
#include <vector>
#include "Graph.hpp"

class FileParser
{
public:
	FileParser();
	~FileParser();

	static const arcsVect getArcs(const std::string & path);
	static const dijArcs getDijArcs(const std::string & path);
	static bool getAStarData(const std::string & path, aStarData & data);
};

#endif
