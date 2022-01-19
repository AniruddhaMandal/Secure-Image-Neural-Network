#pragma once

/**
 * Initializes the seed for random number generator
*/
void randInit();

/**
 * Geneters a random number (long double) with in
 * the interval of [min, max]. Generates the number
 * from a uniform distribution. Uses time as seed. 
*/
long double randomNumber(long double min, long double max);

/**
 * Sigmoid fuction. f(x) = 1/(exp(-x)+1)
*/
long double _Sigmoid(long double Z);

/**
 * Random integer generator from a given range(both inclusive).
 * Generates number from uniform distribution.
*/
long int randomInt(long int min, long int max);

/**
 * Converts little endian int into big endian int.
 * MNIST data is supposed to be read in big endian 
 * form. Intel processors read files in little 
 * endian form. So for Intel processors one must 
 * use the function in MNIST data set.
*/
int littleToBig(unsigned char* num);