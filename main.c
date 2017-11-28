#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PARAMETERS_COUNT 14
#define POPULATION_SIZE  32


typedef struct Individual
{
	double fitness;
	double params[PARAMETERS_COUNT];
}

void Individual_RandomCtor(Individual * self, Individual * example, double delta)
{
	int i;
	for(i=0; i<PARAMETERS_COUNT; i++)
	{
		self->params[i] = randomInDeltaNeighbourhood(example->params[i], delta);
	}
	randomInDeltaNeighbourhood()
}

void Individual_CalculateFitness(Individual * self, Individual * example)
{
	double fitness = 0.0;
	for(i=0; i<PARAMETERS_COUNT; i++)
	{
		// Squared error - just dummy calculation
		fitness += ((example->params[i] - self->params[i]) * (example->params[i] - self->params[i]));
	}
	self->fitness = fitness;
}



int main()
{
	int i;
	Individual example;

	// Set parameters of example form which we'll generate population individuals
	for(i=0; i<PARAMETERS_COUNT; i++)
	{
		example.params[i] = 1.0;
	}

	// Generate random population within delta bounds
	Individual populationArray[POPULATION_SIZE];
	for(i=0; i<POPULATION_SIZE; i++)
	{
		Individual_RandomCtor(&populationArray[i], &example, 0.2);
	}

	return 1;
}