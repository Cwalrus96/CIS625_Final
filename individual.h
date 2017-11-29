#ifndef INDIVIDUAL
#define INDIVIDUAL

#include <vector>

class CIndividual{

  private:

	const static int parameters_count;
	static double randomInDeltaNeighborhood(double, double);
	void calculateFitness(const CIndividual & model);

	double m_fitness;
	std::vector<double> m_params;

  public:

  CIndividual (const std::vector<double> &);

	CIndividual (const CIndividual &, double);

	void debugPrint();

};

#endif