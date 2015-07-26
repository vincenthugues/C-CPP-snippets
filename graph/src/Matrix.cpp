#include <iostream>
#include "Matrix.hpp"

Matrix::Matrix(uint const rows, uint const columns)
	: _matrixTab(NULL),
	_nbRows(rows),
	_nbColumns(columns)
{
	createMatrixTab(0);
}

Matrix::Matrix(Matrix const & other)
	: _matrixTab(NULL),
	_nbRows(other._nbRows),
	_nbColumns(other._nbColumns)
{
	_matrixTab = new int* [_nbRows];
	for (uint i = 0; i < _nbRows; ++i)
	{
		_matrixTab[i] = new int [_nbColumns];
		
		for (uint j = 0; j < _nbColumns; ++j)
			_matrixTab[i][j] = other._matrixTab[i][j];
	}
}

Matrix::Matrix(Graph const & graph)
	: _matrixTab(NULL),
	  _nbRows(graph.getNbVertices()),
	  _nbColumns(graph.getNbVertices())
{
	createMatrixTab(0);
}

Matrix::~Matrix()
{
	delete _matrixTab;
}

Matrix const & Matrix::operator=(Matrix const & other)
{
	if (&other != this)
	{
		if (_nbRows != other.getNbRows()
			|| _nbColumns != other.getNbColumns() )
		{
			std::cerr << "Error: unable to set matrix." << std::endl;
			throw new std::exception;
		}
		
		for (uint i = 0; i < _nbRows; ++i)
			for (uint j = 0; j < _nbColumns; ++j)
				_matrixTab[i][j] = other._matrixTab[i][j];
	}
	return *this;
}

int *Matrix::operator[](int i)
{
	return _matrixTab[i];
}

uint Matrix::getNbRows(void) const
{
	return _nbRows;
}

uint Matrix::getNbColumns(void) const
{
	return _nbColumns;
}

void Matrix::createMatrixTab(uint value)
{
	// Create rows
	_matrixTab = new int* [_nbRows];
	for (uint i = 0; i < _nbRows; ++i)
	{
		// Create columns
		_matrixTab[i] = new int [_nbColumns];
		for (uint j = 0; j < _nbColumns; ++j)
			_matrixTab[i][j] = value;
	}
}

bool Matrix::adjacency(Graph const & graph)
{
	vtcNamesVect const &	vtcNames = graph.getVtcNames();
	arcsVect const & arcs = graph.getArcs();
	uint posA, posB;

	for (arcsVect::const_iterator it = arcs.begin(); it != arcs.end(); ++it)
	{
		// Gets the position of the vertices in the matrix by finding the positions in the vertices' vector
		posA = std::find(vtcNames.begin(), vtcNames.end(), it->first) - vtcNames.begin();
		posB = std::find(vtcNames.begin(), vtcNames.end(), it->second) - vtcNames.begin();

		// If a vertex was not found
		if (posA == vtcNames.size() || posB == vtcNames.size())
			return false;

		++_matrixTab[posA][posB];
		
		if (graph.getDirection() == Graph::UNDIRECTED)
			++_matrixTab[posB][posA];
	}
	
	return true;
}

bool Matrix::accessibility(Graph const & graph)
{
	Matrix prev(graph);

	this->adjacency(graph);
	for (uint row = 0; row < _nbRows; ++row)
		for (uint column = 0; column < _nbColumns; ++column)
			if (row == column || _matrixTab[row][column] > 0)
				_matrixTab[row][column] = 1;

	for (uint n = 1; n <= graph.getNbEdges() && n <= _nbColumns; ++n)
	{
		prev = *this;
		for (uint row = 0; row < _nbRows; ++row)
			for (uint column = 0; column < _nbColumns; ++column)
				if (_matrixTab[row][column]
				|| (_matrixTab[row][n-1] && _matrixTab[n-1][column]))
					_matrixTab[row][column] = 1;
	}
	
	return true;
}

bool Matrix::shortestEdgePaths(Graph const & graph)
{
	Matrix prev(graph);

	this->adjacency(graph);
	for (uint row = 0; row < _nbRows; ++row)
		for (uint column = 0; column < _nbColumns; ++column)
		{
			if (row == column)
				_matrixTab[row][column] = 0;
			else if (_matrixTab[row][column] == 0)
				_matrixTab[row][column] = INFINITE;
			else
				_matrixTab[row][column] = 1;
		}

	for (uint n = 1; n <= graph.getNbEdges() && n <= _nbColumns; ++n)
	{
		prev = *this;
		for (uint row = 0; row < _nbRows; ++row)
			for (uint column = 0; column < _nbColumns; ++column)
				_matrixTab[row][column] = MIN(_matrixTab[row][column], _matrixTab[row][n-1] + _matrixTab[n-1][column]);
	}
	
	return true;
}

Matrix const Matrix::multiplication(Matrix const & other)
{
	if (_nbColumns != other.getNbRows())
	{
		std::cerr << "Error: unable to multiply matrix." << std::endl;
		throw new std::exception;
	}

	Matrix resMtx(_nbRows, other.getNbColumns());

	for (uint row = 0; row < _nbRows; ++row)
		for (uint column = 0; column < _nbColumns; ++column)
			for (uint i = 0; i < _nbRows; ++i)
				resMtx._matrixTab[row][column] += _matrixTab[row][i] * other._matrixTab[i][column];
	return resMtx;
}

void Matrix::print() const
{
	for (uint row = 0; row < _nbRows; ++row)
	{
		for (uint column = 0; column < _nbColumns; ++column)
		{
			if (_matrixTab[row][column] != INFINITE)
				std::cout << _matrixTab[row][column];
			else
				std::cout << "x";
			std::cout << ((column + 1 < _nbColumns) ? " " : "");
		}
		std::cout << std::endl;
	}
}

void Matrix::display() const
{
	for (uint row = 0; row < _nbRows; ++row)
	{
		if (_nbRows == 1)
			std::cout << "(\t";
		else if (row == 0)
			std::cout << "/\t";
		else if (row + 1 >= _nbRows)
			std::cout << "\\\t";
		else
			std::cout << "|\t";
		
		for (uint column = 0; column < _nbColumns; ++column)
			std::cout << _matrixTab[row][column] << "\t";
		
		if (_nbRows == 1)
			std::cout << ")";
		else if (row == 0)
			std::cout << "\\";
		else if (row + 1 >= _nbRows)
			std::cout << "/";
		else
			std::cout << "|";
		
		std::cout << std::endl;
	}
}
