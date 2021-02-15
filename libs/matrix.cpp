#include "matrix.h"

// Construtor
Matrix::Matrix(r, c)
{
    rows = r;
    columns = c;
}
// destrutor
Matrix::~Matrix()
{

}

int Matrix::getRows()
{
    return rows;
}

int Matrix::getColumns()
{
    return columns;
}

void Matrix::setRows(r)
{
    rows = r;
}

void Matrix::setColumns(c)
{
    columns = c;
}