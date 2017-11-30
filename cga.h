#include "individual.h"

class CGA
{
   private:
      CIndividual m_population[POPULATION_SIZE];
      CIndividual m_model;
      void tournamentSelection(CIndividual *);
      // Tmp array, Model individual
      void crossoverAndMutation(const CIndividual *);
   public:
      CGA(const double *, const double);
      const double run();
      void evaluateFitness();
      int getPopulationSize();
};
