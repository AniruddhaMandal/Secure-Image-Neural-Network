#include<ImRead.h>
#ifndef MATRIX_H_
#define MATRIX_H_

/**
 * Mathmatical object Matrix. Matrix stroes `long double` 
 * data type as its entries. It takes row and column dimension 
 * as arguments to its constructor.
 * 
 * mat = Matrix(5,7);
 * 
 * It can also construct from Image object:
 * 
 * image_to_matrix = Matrix(Image);
 * 
 * If the Matrix instance is created without any arg, 
 * then the default row and col dimensions are taken 1.
*/
class Matrix {

    public:
    int row;
    int col;
    long double **values;
    Matrix();
    Matrix(int _row, int _col);
    Matrix(const Image &ImageObj);
    ~Matrix();
  
   /**
    * Prints the entire matrix. If the matrix is 
    * huge it's better not to use it. Use it for 
    * debugging purpose.
    */
    void Display();
  
  /** Returns the Transpose of the target matrix.
    * May cause memory leak as, it does not delete
    * the original instance. 
    * Just Creates a new instance of the matrix object
    * with the values of the transposed matrix.
    */  
    Matrix T();

    /**
     * Returns a Matrix instancea, which is product
     * of two Matrix. This instance is allocated to
     * the stack, so the values of the matrix must
     * be copied. Otherwise the data would be lost.
    */
    Matrix operator *(const Matrix &mat);
    
    /**
     * Returns a Matrix instancea, which is sum of
     * two Matrix. This instance is allocated to
     * the stack, so the values of the matrix must
     * be copied. Otherwise the data would be lost.
    */    
    Matrix operator +(const Matrix &mat);
    /**
     * Returns a Matrix instancea, which is difference
     * of two Matrix. This instance is allocated to
     * the stack, so the values of the matrix must
     * be copied. Otherwise the data would be lost.
    */
    Matrix operator -(const Matrix &mat);

    /**
     * Returns a Matrix instancea, entries of which 
     * two Matrix. This instance is allocated to
     * the stack, so the values of the matrix must
     * be copied. Otherwise the data would be lost.
    */
    Matrix Sigmoid();
    
    /**
     * Returns a Matrix instance with entries as 
     * derivative of sigmoid function at the entries 
     * of the original matrix. Data should be copied
     * otherwise it would be lost. 
    */
    Matrix SigmoidPrime();

    /**
     * Copies the Matrix object. Doesn't delete the 
     * object it is copying from. Doesn't leak memory
     * while the original matrix is changed. 
    */
    void operator =(const Matrix &mat);
};

/**
 * Multiplies two Matrix object element wise
 * and returns a new Matrix instance(i.e.
 * (i,j)th element of the first matrix is 
 * multplied to (i,j)th element of the second
 * matrix). Returned value should be copied
 * as, it is alocated to the stack. 
*/
Matrix HadamardProduct(const Matrix &A, const Matrix &B);

// Returns product of a scaler(long double) with a Matrix.
Matrix operator *(long double I, const Matrix &M);

// Takes a Matrix pointer and converts it in to a zero matrix.
void ZeroMatrix(Matrix* mat);

/**
 * Creates a Matrix with random entries of
 * the dimension provided as arguments. 
 * Entries of the Matrix are in range [0,1].
 * The returned Matrix object is allocated
 * to heap, so it must be deleted after use,
 * to prevent any memory leak.
 * */ 
Matrix* randomMatrix(int row, int col);

/**
 * Convertes the Image objects into Matrices.
 * Arguments: Pointer to the array of image 
 * objects and number of images in the array.
 * Retruns the array of the Matrix pointers. 
 * Each image is converted into a Matrix and 
 * saved into the array with the same index.
*/
Matrix** ImageToMatrix(const Image* ImagesObjs, int N_image);

/**
 * Compare whether the index of maximum values
 * of two Matrice same or not. If same, returns
 * 1, otherwise it will return 0. 
 * 
 * It is created to compare output of a ML model
 * with the actule data, and decide whethere 
 * they indicate to same attribute. 
*/
int Compare(Matrix* A, Matrix* B);


/**
 * Input data type for NeuralNetwork object.
 * Data struct consists of N_Data number of 
 * Matrix of images and corresponding labels
 * which is in vectorized form (i.e. One-Hot-Encoded form).
*/
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

/**
 * Converts the array of image objects into a Data struct.
*/
Data ImageToData(const Image* ImageObjs, int N_image);
int GLOBAL_COUNTER;
#endif 