#ifndef INDIVIDUAL
#define INDIVIDUAL

#include "constants.h"

#include <string>

using namespace std;

class CIndividual
{

  private:
	static double randomInDeltaNeighborhood(double, double);

	double m_fitness;
	bool checkNotPass();

  public:
	double m_params[PARAMETERS_COUNT];
  // Ctors
	CIndividual() {};
	CIndividual (const double *, double);
	//CIndividual (const CIndividual &);

	// Copying
  //CIndividual & operator= (const CIndividual &);

  // Genetic
  void calculateFitness(int);
	static std::pair<CIndividual,CIndividual> crossover(const CIndividual &,const CIndividual &);
	void mutation(const double, const double);

  int getParamsCount() const;
  double getFitness() const;
  string printParameters() const;
};

#endif
