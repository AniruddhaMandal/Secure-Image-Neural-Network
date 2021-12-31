#include<Matrix.h>
#pragma once


/**
 * Deep Neural Network. It generates fully connected 
 * Neurla Network of `Lenth` number of layers. Number
 * of nodes per layers are provided in the `Layers`
 * array. Number of nodesin first layer of the network
 * and dimesion of each data point (in this case number
 * of pixels in each image) should be same. Initial
 * weights and biases are generated randomly with in
 * the range [0,1]. 
*/
class NeuralNetwork {
    
    public:
    int* Layers;
    int Length;
    Matrix** Weights;
    Matrix** Biases;
    
    /**
     * `_Layers` is the array of number of nodes in 
     * each layer. `_Length` is the number of layers
     * in the NeurlNetwork.  
    */
    NeuralNetwork(int* _Layers, int _Length);
    
    ~NeuralNetwork();

    Matrix FeedForward(Matrix &X);

    NeuralNetwork* BackPropagation(Matrix &X, Matrix &Y);
    
    void StochasticGradientDescent(
        const Data &Datset,
        const Data &TestData,
        long double LearningRate, 
        int BatchSize, 
        int N_Cycle
    );

    void UpdateMiniBatch(Matrix** ImagePointer, Matrix** LabelPointer, int BatchSize, long double LearningRate);

    /**
     * Saves Neural Network into a csv files. Provide a 
     * folder to save weights into in.
    */
   void NetToCsv(const char* dir);

    private:
    /**
     * Substracts scaler(long double `p`) multiple of
     * NeuralNetwork `Net` from the current NeurlaNetwork. 
    */
    void _Subtract(NeuralNetwork* Net, long double p);

    /**
     * Measurs the amount (in fraction) of correct predictions
     * for the provided `Dataset`.
    */
    void Accuracy(const Data &Dataset);
};

/**
 * Generates a NerualNetwork with weights and biases as 0.
*/
NeuralNetwork* ZeroNeuralNetwork(int* _layers, int _length);
