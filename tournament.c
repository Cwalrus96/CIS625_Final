#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/** @param upperBound Upper bound is excluded, so it can be used as random index generator
*/
double random0to(double upperBound)
{
    return (double)rand() / ((double)RAND_MAX + 1) * upperBound;
}

int GA_binaryTournament(Individual * populationArray, int arraySize, double probability)
{
	int randomIndex, randomIndex2, tmp;
	randomIndex = (int)random0to(arraySize);
	randomIndex2 = (int)random0to(arraySize);
	if(populationArray[randomIndex2].fitness > populationArray[randomIndex].fitness)
	{
		tmp = randomIndex;
		randomIndex = randomIndex2;
		randomIndex2 = tmp;
	}
	// randomIndex now contains individual with better fitness than randomIndex2

	// 
	if(random0to(1) < probability)
	{
		return randomIndex;
	}
	else
	{
		return randomIndex2;
	}
}

int main()
{
	int i, index;
	for(i = 0; i < (POPULATION_SIZE / 2); i++)
	{
		index = GA_binaryTournament(populationArray, POPULATION_SIZE, 0.8);

	}
	return 1;
}