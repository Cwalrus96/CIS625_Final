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
	rangeOffset = rand() / (RAND_MAX / rangeWidth + 1);
	return rangeLowBound + rangeOffset;
}

int main()
{
	int i;
	srand(time(NULL));
	for(i=0; i<20; i++)
		printf("%f\n", randomInDeltaNeighbourhood(10.0, 0.1));
	return 1;
}