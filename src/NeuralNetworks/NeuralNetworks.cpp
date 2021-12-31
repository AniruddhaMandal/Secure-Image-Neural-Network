#include<NeuralNetworks.h>
#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>

NeuralNetwork::NeuralNetwork(int* _Layers, int _Length) {
    this->Layers = _Layers;
    this->Length = _Length;
    this->Weights = new Matrix*[_Length-1];
    this->Biases = new Matrix*[_Length-1];
    for(int i=0; i<_Length-1; i++) {
        this->Weights[i] = randomMatrix(_Layers[i+1],_Layers[i]);
        this->Biases[i] = randomMatrix(_Layers[i+1],1);
    }
}


NeuralNetwork::~NeuralNetwork() {
    for(int i=0; i<this->Length-1;i++) {
        delete this->Weights[i];
        delete this->Biases[i];
    }
    delete[] this->Weights;
    delete[] this->Biases;
}


Matrix NeuralNetwork::FeedForward(Matrix &X) {
    if(X.row != this->Layers[0]) {
        printf("ERROR: Input Data is not compatable with this NN.\nInput data shape(%d,%d) != NN input layer shape(%d,%d)",
        X.row,X.col,this->Layers[0],1);
    }
    Matrix A; 
    A = X;
    for(int i=0; i<this->Length-1; i++) {
        A = *this->Weights[i]*A;
        A = A+*this->Biases[i];
        A = A.Sigmoid();
    }
    return A;

}


NeuralNetwork* NeuralNetwork::BackPropagation(Matrix &X, Matrix &Y) {
    Matrix InputVectors[this->Length-1]; //a
    Matrix ActivationVectors[this->Length-1]; //z
    Matrix A;
    A = X;
    for(int i=0;i<this->Length-1;i++) {
        InputVectors[i] = A;
        A = (*this->Weights[i])*A + *this->Biases[i];
        ActivationVectors[i] = A;
        A = A.Sigmoid();
    }

    NeuralNetwork* GradNet = new NeuralNetwork(this->Layers,this->Length);
    Matrix A_grad = 0.5*(A - Y);
    Matrix Z_grad;
    for(int i=this->Length-2; i>=0; i--) {
        Z_grad = HadamardProduct(A_grad,(ActivationVectors[i].SigmoidPrime())); 
        *GradNet->Biases[i] = Z_grad;
        *GradNet->Weights[i] = Z_grad*InputVectors[i].T();
        A_grad = (*this->Weights[i]).T()*Z_grad;
    }
    return GradNet;
}

void NeuralNetwork::UpdateMiniBatch(Matrix** ImagePointer, Matrix** LabelPointer, int BatchSize, long double LearningRate){
    NeuralNetwork* BatchGradient = ZeroNeuralNetwork(this->Layers,this->Length); 
    NeuralNetwork* PointGradient;
    long double P = LearningRate/BatchSize;
    for(int i=0; i<BatchSize; i++) {
        PointGradient = this->BackPropagation(*ImagePointer[i],*LabelPointer[i]);
        BatchGradient->_Subtract(PointGradient, P);
        delete PointGradient;
    }
    this->_Subtract(BatchGradient,-1);
    delete BatchGradient;
}

/**
 * Breaks data into chunks and applies `UpdateMiniBatch`.
 * This process is repeted `N_cycle` times. Before `UpdateMiniBatch`
 * Label and images are broken separately.
*/
void NeuralNetwork::StochasticGradientDescent(const Data &Dataset,const Data &TestData, long double LearningRate, int BatchSize, int N_cycle) {
    int N_Batch = Dataset.N_Data/BatchSize;
    Matrix** ImagePointer;
    Matrix** LabelPointer; 

    for(int cy=0; cy<N_cycle; cy++){
    for(int i=0; i<N_Batch; i++) {
            ImagePointer = Dataset.M_Images+(i*BatchSize);
            LabelPointer = Dataset.M_Labels+(i*BatchSize);
            this->UpdateMiniBatch(ImagePointer, LabelPointer, BatchSize,LearningRate);
            this->Accuracy(TestData);
    }
    }
}


void NeuralNetwork::_Subtract(NeuralNetwork* Net, long double p) {
    for(int i=0; i<this->Length-1; i++) {
        *this->Weights[i] = *this->Weights[i] - p*(*Net->Weights[i]);
        *this->Biases[i] = *this->Biases[i] - p*(*Net->Biases[i]);
    }
}


void NeuralNetwork::Accuracy(const Data &Data) {
    Matrix prediction;
    int Sum = 0;
    for(int i=0;i<Data.N_Data;i++) {
        prediction = this->FeedForward(*Data.M_Images[i]);
        Sum += Compare(&prediction,Data.M_Labels[i]);
    }
    long double acc = (long double) Sum/Data.N_Data;
    printf("[%d]: %.10Lf\n",GLOBAL_COUNTER,acc);
    GLOBAL_COUNTER++;
}

void NeuralNetwork::NetToCsv(const char* dir) {
    printf("Writing to: %s\n",dir);
    mkdir(dir,0777);
    char fileName[100];
    for(int l=0; l<this->Length-1;l++) {
        sprintf(fileName,"%s/weight_%d.csv",dir,l);
        this->Weights[l]->MatrixToCsv(fileName);
        sprintf(fileName,"%s/biases_%d.csv",dir,l);
        this->Biases[l]->MatrixToCsv(fileName);
    }
}


NeuralNetwork* ZeroNeuralNetwork(int* _layers, int _length) {
        NeuralNetwork* zeroNet = new NeuralNetwork(_layers, _length);
        for(int i=0; i<_length-1;i++) {
            ZeroMatrix(zeroNet->Weights[i]);
            ZeroMatrix(zeroNet->Biases[i]);
        } 
        return zeroNet;
}
