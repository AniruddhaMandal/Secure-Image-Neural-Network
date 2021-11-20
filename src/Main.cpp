#include<iostream>
#include<Matrix.h>
#include<ImRead.h>
#include<NeuralNetworks.h>


int main() {
    Matrix Y = Matrix(10,1);
    for(int i=0; i<10; i++) {
        Y.values[i][0] = 0;
    }
    Y.values[6][0] = 1;
    
    
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
    Matrix A = Matrix(1,1); 
    A = testNet.FeedForward(*X);
    A.Display();
    NeuralNetwork* GradNet = testNet.BackPropagation(*X, Y);
    GradNet->Weights[1]->Display();
    
    fclose(fpt);
    delete X;
    delete[] images;


}