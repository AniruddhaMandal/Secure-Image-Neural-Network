#include<MathCal.h>
#include<time.h>
#include<math.h>
#include<iostream>

long int SEED = 0;
long int randomCoA = 23423;
long int randomCoB = 7673;


void randInit() {
    time(&SEED);
}

long double randomNumber(long double min, long double max) {
    long double range = max-min;
    long int big = 99999999999999;
    return min + range*((long double) randomInt(0,big)/big);
}

long double _Sigmoid(long double Z) {
    Z = exp(-Z);
    Z = 1/(1+Z);
    return Z;
}

long int randomInt(long int min, long int max){
    if(SEED == 0) {
        randInit();
    }
    long int range = max-min+1;
    SEED = randomCoA*SEED + randomCoB;   
    long int rand = SEED%range;
    if(rand<0) {
        rand = -1*rand;
    }
    return rand + min;
}

int littleToBig(unsigned char* num) {
    int big = 0;
    int coeff = 1;
    for(int i=0;i<4;i++) {
        big += num[3-i]*coeff;
        coeff *= 256; 
    }
    return big;

}