#pragma once

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
 * Random integer generator from a given range.
 * Generates number from uniform distribution.
*/
int randomInt(int min, int max);