#include<iostream>
#include<ImRead.h>
#include<Matrix.h>
#include<sys/stat.h>
#include<sys/types.h>

void TestFeedforward() {
    
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

void TestAccuracy() {
    const char* file_name = "../CIFAR/data_batch_1.bin";
    FILE* fpt = fopen(file_name,"rb");
    Image* testImage = ImRead(fpt,1);
    Data testData = ImageToData(testImage,1);
    testData.M_Labels[0]->Display();
    Matrix* A = testData.M_Labels[0];
    Matrix B = Matrix(10,1);
    ZeroMatrix(&B);

    if((Compare(A, A) == 1) && (Compare(A,&B) == 0)){
    std::cout<<"Compare function Passed Test."<<std::endl;
    }
    else {
        std::cout<<"Compare function Failed Test."<<std::endl;
    }
    
}

void TestNeuralNet() {
        
    const char* test_file_name = "../CIFAR/data_batch_2.bin";
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
    if(fpt==NULL) {
        printf("[ERROR]: Cannot open %s\nNo such file exists.", file_name);
        exit(EXIT_FAILURE);
    }

    Image* trainImages = ImRead(fpt, 10000);
    Data trainDataset = ImageToData(trainImages, 10);

    int layers[] = {1024,130,40,10};
    NeuralNetwork testNet = NeuralNetwork(layers,4);
    testNet.NetToCsv("../DEBUG/testNet");
    testNet.StochasticGradientDescent(trainDataset,TestDataset,0.5,10,3);

}

void TestRandomNumber() {
    const char* fileName = "testRandomNumber.csv";
    FILE* fpt = fopen(fileName,"w"); 
    if(fpt == NULL) {
        printf("Faild to write on: %s\n",fileName);
        exit(EXIT_FAILURE);
    }
    printf("Writing to: %s\n",fileName);
    for(int i=0;i<40000;i++) {
        fprintf(fpt,"%Lf, ",randomNumber(-1,1));
    }
    fseek(fpt,-2L,SEEK_CUR);
    fprintf(fpt,"\n");
    fclose(fpt);
}

void TestLoadMatrix() {
    Matrix* M = randomMatrix(21,23);
    M->MatrixToCsv("../DEBUG/loadMatrix.csv");
    Matrix* N = LoadMatrix("../DEBUG/loadMatrix.csv");
    if(M->row != N->row) {
        printf("[FAILED]: LoadMatrix function. (Dimension not equal)");
        return;
    }
    if(M->col != N->col) {
        printf("[FAILED]: LoadMatrix function. (Dimension not equal)");
        return;
    }
    for(int i=0;i<M->row;i++) {
        for(int j=0;j<M->row;j++) {
            if((M->values[i][j] - N->values[i][j])>0.00000000000000000001) {
                printf("%.20Lf != %.20Lf\n",M->values[i][j],N->values[i][j]);
                printf("[FAILED]: LoadMatrix function.\n");
                return;
            }
        }
    }
    printf("[PASSED]: LoadMatrix function.\n");
}