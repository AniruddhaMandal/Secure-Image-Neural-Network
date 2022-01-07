#include<MathCal.h>
#include<iostream>
#include<random>


long double randomNumber(long double min, long double max) {
    long long L = 99999999999999;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dist(0,L);
    long double factor = (long double) dist(gen)/L;
    return (min + (max-min) * factor);
}

long double _Sigmoid(long double Z) {
    Z = exp(-Z); 
    Z = 1/(1+Z);
    return Z;   
}

int randomInt(int min, int max){ 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min,max);
    return dist(gen);
}