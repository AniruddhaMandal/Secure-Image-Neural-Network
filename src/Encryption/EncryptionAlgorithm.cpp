#include<stdint.h>
#include<EncryptionAlgorithm.h>
#include<MathCal.h>
#include<stdlib.h>

uint8_t* PermuteBWImage(uint8_t* GrayImage, int pixelSize) {
    uint8_t* permutedImage = (uint8_t *)malloc(sizeof(uint8_t)*pixelSize);
    for(int i=0; i<pixelSize; i++) {
        permutedImage[i] = GrayImage[i];
    }

    int rand;
    uint8_t swap; 
    for(int i=0; i<pixelSize; i++) {
        rand = randomInt(0,pixelSize);
        swap = permutedImage[i];
        permutedImage[i] = permutedImage[rand];
        permutedImage[rand] = swap;
    }
    return permutedImage;
}