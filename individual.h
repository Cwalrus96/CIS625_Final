#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"

class CIndividual
{

  private:
  const static double s_mutationParameterProbability = 0.1;
  const static double s_mutationProbability = 0.1;

	static double randomInDeltaNeighborhood(double, double);

	double m_params[PARAMETERS_COUNT];
	double m_fitness;
	bool checkNotPass();

  public:
  // Ctors
	CIndividual() {};
	CIndividual (const double *, double);
	//CIndividual (const CIndividual &);
    
	// Copying
  //CIndividual & operator= (const CIndividual &);

  // Genetic
  void calculateFitness();
	void crossover(const CIndividual &);
	void mutation();

  int getParamsCount() const;
  double getFitness() const;

	void debugPrint();
};

#endif
