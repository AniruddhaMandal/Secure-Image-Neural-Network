#include<Matrix.h>
#include<ImRead.h>

#pragma once


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
    
    // Default constructor
    Data();

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
 * Converts the array of image objects into a Data struct. (It's for CIFAR)
*/
Data ImageToData(const Image* ImageObjs,int startNumber, int N_image);

/**
 * Reads a single MNIST file and converts it into a array of Matrices.
 * For labels file each labels are transformed using one-hot-encoding.
*/
Matrix** readMNISTfile(const char* fileName);

/**
 * Outputs two datasets. First one is training data with 60000 datapoints,
 * and socond one is test dataset with 10000 datapoints. Returned pointer 
 * is pointer to a array of two `Data`.
*/
Data* loadMINIST();