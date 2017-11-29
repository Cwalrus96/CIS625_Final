// Headers to functions etc.

/** @param upperBound Upper bound is excluded, so it can be used as random index generator
*/
double random0to(double upperBound);


/** @param number Number in which surrounding we generate the random number.
	@param delta Delta surrounding in percent. E.g. 0.1 = number +/- 10%
*/
double randomInDeltaNeighbourhood(double number, double delta);