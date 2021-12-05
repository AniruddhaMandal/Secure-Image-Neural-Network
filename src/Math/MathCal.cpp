#include<MathCal.h>
#include<time.h>
#include<math.h>


long double Seed = 42.3423l;
int SeedInt = 2342;
long double randomNumber(long double min, long double max) {
    time_t timer;
    time(&timer);
    long double integer;
    Seed = pow(-1,timer%2)*modf(Seed*timer+234.234324945l, &integer)*(max-min) + min;
    return Seed;
}

long double _Sigmoid(long double Z) {
    Z = exp(-Z); 
    Z = 1/(1+Z);
    return Z;   
}

int randomInt(int min, int max){ 
    time_t timer;
    time(&timer);
    SeedInt = timer*SeedInt;
    SeedInt = (SeedInt%(max-min))+min;
    return SeedInt;
}