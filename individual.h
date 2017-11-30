#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"

class CIndividual
{

  private:
	static double randomInDeltaNeighborhood(double, double);

	double m_params[PARAMETERS_COUNT];
	double m_fitness;

  public:
  	// Ctors
	CIndividual() {};
	CIndividual (const double *, double);
	CIndividual (const CIndividual &);
    
    // Copying
    CIndividual & operator= (const CIndividual &);
    CIndividual(const CIndividual &, bool);

    // Genetic
    void calculateFitness(const CIndividual & model);
	void crossover(const CIndividual &);
	void mutation(const CIndividual &, int);

    int getParamsCount();
    int getFitness();

	void debugPrint();
};

#endif
