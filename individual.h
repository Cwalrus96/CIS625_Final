#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"

class CIndividual{

  private:
	static double randomInDeltaNeighborhood(double, double);
	void calculateFitness(const CIndividual & model);

	double m_params[PARAMETERS_COUNT];

  public:
	double m_fitness;

	CIndividual(){};
	CIndividual (const double *);
	CIndividual (const double *, double);
	CIndividual (const CIndividual &, double);
        CIndividual & operator= (const CIndividual &);
        CIndividual(const CIndividual &);

	void debugPrint();

};

#endif
