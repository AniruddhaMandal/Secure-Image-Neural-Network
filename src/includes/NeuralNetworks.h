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
    
    void StochasticGradientDescent(
        const Data &Datset,
        long double LearningRate, 
        int BatchSize, 
        int N_Cycle
    );

    void UpdateMiniBatch(Matrix** ImagePointer, Matrix** LabelPointer, int BatchSize, long double LearningRate);

    private:
    void _Subtract(NeuralNetwork* Net, long double p);
};


NeuralNetwork* ZeroNeuralNetwork(int* _layers, int _length);
