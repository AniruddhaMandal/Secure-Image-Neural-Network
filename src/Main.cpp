#include<iostream>
#include<Matrix.h>
#include<ImRead.h>
#include<NeuralNetworks.h>


int main() {
    
    const char* test_file_name = "../CIFAR/data_batch_1.bin";
    FILE* Tfpt;
    Tfpt = fopen(test_file_name,"rb");
    if(Tfpt == NULL) { 
        printf("ERROR:file doesn't exists!");
        exit(-1);
    }


    Image* Timages = ImRead(Tfpt,10000);
    Data TestDataset = ImageToData(Timages, 1000);
    
    
    
    
    const char* file_name = "../CIFAR/data_batch_1.bin";
    FILE* fpt;
    fpt = fopen(file_name,"rb");
    if(fpt == NULL) { 
        printf("ERROR:file doesn't exists!");
        exit(-1);
    }


    Image* images = ImRead(fpt,10000);
    Data Dataset = ImageToData(images, 10000);

    int layers[] = {1024,130,40,10};
    NeuralNetwork testNet(layers,4);
    long double b = testNet.Weights[0]->values[1][1];
    testNet.StochasticGradientDescent(Dataset,TestDataset,0.01,100,30);
    long double a = testNet.Weights[0]->values[1][1];
    printf("%0.20Lf  %0.20Lf\n",a,b);

    fclose(fpt);
    delete[] images;

}
