#include<Data.h>
#include<MathCal.h>

Data::Data() {
    this->N_Data = 0;
}


Matrix** readMNISTfile(const char* fileName) {
    FILE* fpt = fopen(fileName,"rb");
    unsigned char magicNumberchar[4], imageCountchar[4], rowCountchar[4], colCountchar[4];
    fread(magicNumberchar,4,1,fpt);
    fread(imageCountchar,4,1,fpt);
    int magicNumber = littleToBig(magicNumberchar);
    int imageCount = littleToBig(imageCountchar);
    
    if(magicNumber == 2049) {
        Matrix** label = new Matrix*[imageCount];
        unsigned char buff;
        for(int i=0;i<imageCount;i++) {
            label[i] = new Matrix(10,1);
            fread(&buff,1,1,fpt);
            // 10 is the number of classes.
            for(int j=0;j<10;j++) {
                if(j == (int) buff) {
                    label[i]->values[j][0] = 1;
                }
                else{
                    label[i]->values[j][0] = 0;
                }
            }
        }
        fclose(fpt);
        return label;
    }
    
    fread(rowCountchar,4,1,fpt);
    fread(colCountchar,4,1,fpt);
    int rowCount= littleToBig(rowCountchar);
    int colCount= littleToBig(colCountchar);
    int pixelSize = rowCount*colCount;
    
    unsigned char imageBuff[pixelSize];
    Matrix** image = new Matrix*[imageCount];
    for(int i=0; i<imageCount;i++) {
        image[i] = new Matrix(pixelSize,1);
        fread(imageBuff,pixelSize,1,fpt);
        for(int j=0;j<pixelSize;j++) {
            image[i]->values[j][0] = (long double) imageBuff[j];
        }
    }
    fclose(fpt);
    return image;
} 


Data* loadMINIST() {
    const char* trainImages = "../MNIST/train-images-idx3-ubyte";
    const char* trainLabels ="../MNIST/train-labels-idx1-ubyte";
    const char* testImages = "../MNIST/t10k-images-idx3-ubyte";
    const char* testLabels = "../MNIST/t10k-labels-idx1-ubyte";

    Data* MNISTData = new Data[2];
    MNISTData[0].M_Images = readMNISTfile(trainImages);
    MNISTData[0].M_Labels = readMNISTfile(trainLabels);
    MNISTData[0].N_Data = 60000;

    MNISTData[1].M_Images = readMNISTfile(testImages);
    MNISTData[1].M_Labels = readMNISTfile(testLabels);
    MNISTData[1].N_Data = 10000;
    
    return MNISTData;
}


Data ImageToData(const Image* ImageObjs, int startNumber, int N_image) {
    //Enter number of image class as a variable insted of hard coding 10.
    Data _newData(N_image);
    
    _newData.M_Labels = new Matrix*[N_image];
    for(int i=0; i<N_image; i++) {
        _newData.M_Labels[i] = new Matrix(10,1);
        for(int j=0; j<10; j++) {
            if(j == ImageObjs[i+startNumber].label) _newData.M_Labels[i]->values[j][0] = 1;
            else _newData.M_Labels[i]->values[j][0] = 0;
        }
    }

    _newData.M_Images = new Matrix*[N_image];
    for(int i=0; i<N_image; i++) {
        _newData.M_Images[i] = new Matrix(ImageObjs[i+startNumber]);
    }
    return _newData;
}

