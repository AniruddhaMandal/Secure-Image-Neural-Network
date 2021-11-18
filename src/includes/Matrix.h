#include<ImRead.h>
#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {

    public:
    int row;
    int col;
    long double **values;
    Matrix(int _row, int _col);
    Matrix(const Image &ImageObj);
    ~Matrix();
    void Display();
    Matrix T();
    Matrix* operator *(const Matrix &mat);
    Matrix* operator +(const Matrix &mat);
    Matrix* operator -(const Matrix &mat);
    Matrix* Sigmoid();
};


Matrix operator *(long double I, const Matrix &M);

Matrix* randomMatrix(int row, int col);


#endif 