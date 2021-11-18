#include<stdio.h>
#include<ImRead.h>
#include<stdint.h>

#define CHANNEL_SIZE 1024
Image* ImRead(FILE* fpt, int N_Image) {
    Image* images = new Image[N_Image];
    for(int i=0; i<N_Image; i++) {
        fread(&(images[i].label),1,1,fpt);
        fread(images[i].Red,CHANNEL_SIZE,1,fpt);
        fread(images[i].Green,CHANNEL_SIZE,1,fpt);
        fread(images[i].Blue,CHANNEL_SIZE,1,fpt);
    }
    return images;
}

uint8_t** ImProcess(Image* ImageObjs, int N_Image) {
    uint8_t** GrayScale = new uint8_t*[N_Image];
    for(int i=0; i<N_Image;i++) {
        GrayScale[i] = new uint8_t[CHANNEL_SIZE];
        for(int j=0; j<CHANNEL_SIZE;j++){
            GrayScale[i][j] = (ImageObjs[i].Blue[j]/3 + ImageObjs[i].Green[j]/3 + ImageObjs[i].Red[j]/3);
        }
    }
    return GrayScale;
}