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
    
    NeuralNetwork* gradNet = testNet.BackPropagation(*(Dataset.M_Images[1]),*(Dataset.M_Labels[1]));
    const char *dir = "gradNet"; 
    gradNet->NetToCsv(dir);
    dir = "testNet";
    testNet.NetToCsv(dir);
    printf("Output of Net:");
    testNet.FeedForward(*(Dataset.M_Images[1])).Display();
    printf("Acctual Label:");
    Dataset.M_Labels[1]->Display();

    fclose(fpt);
    delete[] images;
    delete gradNet;
}
