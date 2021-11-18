#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#pragma once

class Image {
    public:
    uint8_t label;
    uint8_t* Red = (uint8_t*) malloc(1024);
    uint8_t* Green = (uint8_t*) malloc(1024);
    uint8_t* Blue = (uint8_t*) malloc(1024);
    
    Image(){

    }
    
    ~Image(){
        free(this->Red);
        free(this->Green);
        free(this->Blue);
    } 
};

Image* ImRead(FILE* fpt, int N_Image);
uint8_t** ImProcess(Image* ImageObjs, int N_Image);