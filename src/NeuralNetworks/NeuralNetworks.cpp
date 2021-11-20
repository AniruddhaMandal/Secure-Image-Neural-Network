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


Matrix NeuralNetwork::FeedForward(Matrix &X) {
    if(X.row != this->Layers[0]) {
        printf("ERROR: Input Data is not compatable with this NN.\nInput data shape(%d,%d) != NN input layer shape(%d,%d)",
        X.row,X.col,this->Layers[0],1);
    }
    Matrix A; 
    A = X;
    for(int i=0; i<this->Length-1; i++) {
        A = *this->Weights[i]*A;
        A = A+*this->Biases[i];
        A = A.Sigmoid();
    }
    return A;

}


NeuralNetwork* NeuralNetwork::BackPropagation(Matrix &X, Matrix &Y) {
    Matrix InputVectors[this->Length-1]; //a
    Matrix ActivationVectors[this->Length-1]; //z
    Matrix A;
    A = X;
    for(int i=0;i<this->Length-1;i++) {
        InputVectors[i] = A;
        A = (*this->Weights[i])*A + *this->Biases[i];
        ActivationVectors[i] = A;
        A = A.Sigmoid();
    }

    NeuralNetwork* GradNet = new NeuralNetwork(this->Layers,this->Length);
    Matrix A_grad = (A - Y);
    Matrix Z_grad;
    for(int i=this->Length-2; i>=0; i--) {
        Z_grad = HadamardProduct(A_grad,(ActivationVectors[i].SigmoidPrime())); 
        *GradNet->Biases[i] = Z_grad;
        *GradNet->Weights[i] = Z_grad*InputVectors[i].T();
        A_grad = (*this->Weights[i]).T()*Z_grad;
    }
    return GradNet;
}
