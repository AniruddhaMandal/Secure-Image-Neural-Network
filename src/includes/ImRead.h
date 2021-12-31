#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#pragma once

/**
 * Image class consists of 4 elements.
 * The label of the object and R,G,B
 * pixeles of the image.
*/
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

/**
 * Reads the images and converts into image object.
*/
Image* ImRead(FILE* fpt, int N_Image);

/**
 * Converts image object into a grayscale object.
 * Labels are lost in this process.
*/
uint8_t** ImProcess(Image* ImageObjs, int N_Image);