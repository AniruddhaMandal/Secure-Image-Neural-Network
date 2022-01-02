#include<iostream>
#include<ImRead.h>
#include<Matrix.h>
#include<sys/stat.h>
#include<sys/types.h>

void TestFeedforward() {
    
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
    mkdir("../DEBUG",0777);
    const char *dir = "../DEBUG/testNet";
    testNet.NetToCsv(dir);
    printf("Output of Net:");
    testNet.FeedForward(*(Dataset.M_Images[1])).Display();
    printf("Acctual Label:");
    Dataset.M_Labels[1]->Display();

    char file[100];
    Matrix A;
    A = *(Dataset.M_Images[1]);
    for(int i=0; i<testNet.Length-1;i++) {
        A = *(testNet.Weights[i])*A + *(testNet.Biases[i]);
        sprintf(file,"../DEBUG/junk_%d.csv",i);
        A.MatrixToCsv(file);
        A = A.Sigmoid();
        sprintf(file,"../DEBUG/output_%d.csv",i);
        A.MatrixToCsv(file);
    }
    
    fclose(fpt);
    delete[] images;
}

void TestMatrix() 
{
    mkdir("../DEBUG",0777);
    
    Matrix* A = randomMatrix(100,34);
    A->MatrixToCsv("../DEBUG/A.csv");
    
    Matrix* B = randomMatrix(34,100);
    B->MatrixToCsv("../DEBUG/B.csv");
    
    Matrix product = (*A)*(*B);
    product.MatrixToCsv("../DEBUG/product.csv");
    
    Matrix* C = randomMatrix(100,100);
    C->MatrixToCsv("../DEBUG/C.csv");
    
    Matrix sum = product+(*C);
    sum.MatrixToCsv("../DEBUG/sum.csv");
    
    Matrix* D = randomMatrix(32,1);
    D->MatrixToCsv("../DEBUG/D.csv");

    Matrix sig = D->Sigmoid();
    sig.MatrixToCsv("../DEBUG/sig.csv");


    
    delete A;
    delete B;
    delete C;
    delete D;
}