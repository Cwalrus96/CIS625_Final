#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"
#include <utility>

class CIndividual
{

  private:
  const static double s_mutationParameterDelta = 0.1;
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
	static std::pair<CIndividual,CIndividual> crossover(const CIndividual &,const CIndividual &);
	void mutation();

  int getParamsCount() const;
  double getFitness() const;

	void debugPrint() const;
};

#endif
