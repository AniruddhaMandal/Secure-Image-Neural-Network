#include<NeuralNetworks.h>
#include<iostream>

NeuralNetwork::NeuralNetwork(int* _Layers, int _Length) {
    this->Layers = _Layers;
    this->Length = _Length;
    this->Weights = new Matrix*[_Length-1];
    this->Biases = new Matrix*[_Length-1];
    for(int i=0; i<_Length-1; i++) {
        this->Weights[i] = randomMatrix(_Layers[i+1],_Layers[i]);
        this->Biases[i] = randomMatrix(_Layers[i+1],1);
    }
}


NeuralNetwork::~NeuralNetwork() {
    for(int i=0; i<this->Length-1;i++) {
        delete this->Weights[i];
        delete this->Biases[i];
    }
    delete[] this->Weights;
    delete[] this->Biases;
}


Matrix* NeuralNetwork::FeedForward(Matrix* X) {
    if(X->row != this->Layers[0]) {
        printf("ERROR: Input Data is not compatable with this NN.\nInput data shape(%d,%d) != NN input layer shape(%d,%d)",
        X->row,X->col,this->Layers[0],1);
    }
    Matrix* temp;
    for(int i=0; i<this->Length-1; i++) {
        temp = X;
        X = *this->Weights[i]*(*X);
        delete temp;
        temp = X;
        X = *X+*this->Biases[i];
        delete temp;
        temp = X;
        X = X->Sigmoid();
        delete temp;
    }
    return X;

}

