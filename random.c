#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/** @param number Number in which surrounding we generate the random number.
	@param delta Delta surrounding in percent. E.g. 0.1 = number +/- 10%
*/
double randomInDeltaNeighbourhood(double number, double delta)
{
	double rangeWidth, rangeOffset, rangeLowBound;
	rangeWidth = delta * 2 * number;
	rangeLowBound = number - (delta * number);
	rangeOffset = (double)rand() / (double)((unsigned)RAND_MAX / rangeWidth + 1);
	return rangeLowBound + rangeOffset;
}

double random0to1()
{
    return (double)rand() / (double)((unsigned)RAND_MAX + 1);
}

int main()
{
	int i, sum;
	sum = 0;
	srand(time(NULL));
	for(i=0; i<20; i++)
		printf("%f\n", randomInDeltaNeighbourhood(10.0, 0.1));
	for(i=0; i<10000000; i++)
		if(random0to1() < 0.1)
			sum++;
	printf("Probabilty: %f, should be 0.1\n", sum/10000000.0);
	return 1;
}