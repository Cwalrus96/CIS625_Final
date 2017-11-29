#include "constants.h"

typedef struct Individual
{
	double fitness;
	double params[PARAMETERS_COUNT];
};

void Individual_CalculateFitness(Individual * self, Individual * example);

void Individual_RandomCtor(Individual * self, Individual * example, double delta);

void Individual_Copy(Individual * source, Individual * destination);