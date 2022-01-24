#include<iostream>
#include<Matrix.h>
#include<ImRead.h>
#include<NeuralNetworks.h>
#include<MathCal.h>
#include<Tests.h>
#include<Data.h>

int main(){
    int layers[4] = {784,40,30,10};
    NeuralNetwork testNet(layers, 3);
    Data* mnist = loadMINIST();
    printf("Data reading finished..\n");
    Data trainData = mnist[0];
    Data testData = mnist[1];
    testNet.StochasticGradientDescent(trainData,testData,0.1,10,30);
    testNet.NetToCsv("../DEBUG/TrainedModel");
}
