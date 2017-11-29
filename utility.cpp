#include <cstdlib>
#include "utility.h"

double Utility::random0to(double max){
	return (double)rand() / ((double)RAND_MAX) * max;
}

int Utility::randomIndex(int max){
	return (double)rand() / ((double)RAND_MAX + 1) * max;
}