#include<ImRead.h>
#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {

    public:
    int row;
    int col;
    long double **values;
    Matrix();
    Matrix(int _row, int _col);
    Matrix(const Image &ImageObj);
    ~Matrix();
    void Display();
    Matrix T();
    Matrix operator *(const Matrix &mat);
    Matrix operator +(const Matrix &mat);
    Matrix operator -(const Matrix &mat);
    Matrix Sigmoid();
    Matrix SigmoidPrime();
    void operator =(const Matrix &mat);
};

Matrix HadamardProduct(const Matrix &A, const Matrix &B);

Matrix operator *(long double I, const Matrix &M);

void ZeroMatrix(Matrix* mat);

Matrix* randomMatrix(int row, int col);

Matrix** ImageToMatrix(const Image* ImagesObjs, int N_image);

int Compare(Matrix* A, Matrix* B);

struct Data {
    int N_Data;
    Matrix** M_Images;
    Matrix** M_Labels;
    
    Data(int _N_Data) {
        this->N_Data = _N_Data;
    }

    ~Data(){
        for(int i=0; i<this->N_Data;i++) {
            delete this->M_Images[i];
            delete this->M_Labels[i];
        }
        delete[] this->M_Images;
        delete[] this->M_Labels;
        
    }
};

Data ImageToData(const Image* ImageObjs, int N_image);
int GLOBAL_COUNTER;
#endif 