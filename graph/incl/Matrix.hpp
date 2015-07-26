#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include "Graph.hpp"

class Matrix
{
public:
	Matrix(uint const rows, uint const columns);
	Matrix(Matrix const & other);
	Matrix(Graph const & graph);
	~Matrix();

	Matrix const &	operator=(Matrix const & other);
	int		*operator[](int i);

	uint		getNbRows(void) const;
	uint		getNbColumns(void) const;

	void		createMatrixTab(uint value);
	bool		adjacency(Graph const & graph);
	bool		accessibility(Graph const & graph);
	bool		shortestEdgePaths(Graph const & graph);
	Matrix const	multiplication(Matrix const & other);
	void		print() const;
	void		display() const;

protected:
	int		**_matrixTab;
	uint		_nbRows;
	uint		_nbColumns;
};

#endif
