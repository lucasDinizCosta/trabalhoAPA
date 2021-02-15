#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

class Matrix
{
    private:
        int rows = 0;
        int columns = 0;
    public:
        Matrix(r, c);
        ~Matrix();
        int getRows();
        int getColumns();
        void setRows();
        void setColumns();
};

#endif //MATRIX_H_INCLUDED