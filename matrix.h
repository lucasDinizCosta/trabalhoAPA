#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED


class Matrix{

private:
    
    int num_lines;
    int num_columns;

public:

    ///Construtor
    Matrix::Matrix(int _num_lines, int _num_columns){

        num_lines = _num_lines;
        num_columns = _num_columns;

    }

    ///Destrutor
    Matrix::~Matrix(){

    }

    int Matrix::get_D(){

        return d;
    }


};


#endif MATRIX_INCLUDED