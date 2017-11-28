#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/** @param upperBound Upper bound is excluded, so it can be used as random index generator
*/
double random0to(double upperBound)
{
    return (double)rand() / ((double)RAND_MAX + 1) * upperBound;
}

/** @param number Number in which surrounding we generate the random number.
	@param delta Delta surrounding in percent. E.g. 0.1 = number +/- 10%
*/
double randomInDeltaNeighbourhood(double number, double delta)
{
	double rangeWidth, rangeOffset, rangeLowBound;
	rangeWidth = (delta * 2) * number;
	rangeLowBound = number - (delta * number);
	rangeOffset = random0to(rangeWidth);
	return rangeLowBound + rangeOffset;
}

int main()
{
	int i, sum;
	sum = 0;
	srand(time(NULL));
	for(i=0; i<20; i++)
		printf("%f\n", randomInDeltaNeighbourhood(10.0, 0.1));
	for(i=0; i<10000000; i++)
		if(random0to(1) < 0.1)
			sum++;
	printf("Probabilty: %f, should be 0.1\n", sum/10000000.0);
	return 1;
}