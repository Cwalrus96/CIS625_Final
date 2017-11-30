#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"

class CIndividual
{

  private:
	static double randomInDeltaNeighborhood(double, double);
	void calculateFitness(const CIndividual & model);

	double m_params[PARAMETERS_COUNT];
	double m_fitness;

  public:

	CIndividual() {};
	CIndividual (const double *, double);
	CIndividual (const CIndividual &);
    
    CIndividual & operator= (const CIndividual &);
    CIndividual(const CIndividual &, bool);

	void crossover(const CIndividual &);

	void mutation(const CIndividual &, int);

    int getParamsCount();
    int getFitness();

	void debugPrint();

};

#endif
