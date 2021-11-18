#include<iostream>
#include<Matrix.h>
#include<ImRead.h>
#include<NeuralNetworks.h>


int main() {
    const char* file_name = "../CIFAR/data_batch_1.bin";
    FILE* fpt;
    fpt = fopen(file_name,"rb");
    if(fpt == NULL) { 
        printf("ERROR:file doesn't exists!");
        exit(-1);
    }


    Image* images = ImRead(fpt,10000);
    Matrix* X = new Matrix(images[0]);


    int layers[] = {1024,30,40,10};
    NeuralNetwork testNet(layers,4);
    X = testNet.FeedForward(X);
    X->Display();
    
    fclose(fpt);
    delete X;
    delete[] images;

}