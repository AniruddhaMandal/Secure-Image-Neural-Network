#include<Matrix.h>
#pragma once



class NeuralNetwork {
    public:
    int* Layers;
    int Length;
    Matrix** Weights;
    Matrix** Biases;
    NeuralNetwork(int* _Layers, int _Length);
    ~NeuralNetwork();
    Matrix FeedForward(Matrix &X);
    NeuralNetwork* BackPropagation(Matrix &X, Matrix &Y);
};
