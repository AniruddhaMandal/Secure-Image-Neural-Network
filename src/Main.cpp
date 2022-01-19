#include<iostream>
#include<Matrix.h>
#include<ImRead.h>
#include<NeuralNetworks.h>
#include<MathCal.h>
#include<Tests.h>
#include<Data.h>

int main(){
    TestNeuralNet();
    TestAccuracy();
    TestFeedforward();
    TestMatrix();
    TestRandomNumber();
    TestLoadMatrix();
    TestMNISTloader();
}
