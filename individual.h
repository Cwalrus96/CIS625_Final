#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"
#include <utility>

class CIndividual
{

  private:
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
	void mutation(const double, const double);

  int getParamsCount() const;
  double getFitness() const;

	void debugPrint() const;
};

#endif
