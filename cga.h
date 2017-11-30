#include "individual.h"

class CGA
{
   private:
      CIndividual m_population[POPULATION_SIZE];
      void tournamentSelection(CIndividual * newPopulation);
   public:
      CGA(const double *);
      const double run();

};
