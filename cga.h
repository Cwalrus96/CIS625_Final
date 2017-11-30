#include "individual.h"

class CGA
{
   public:
   
      const static int population_size = 100;

      CGA(const double *, const double);
      CIndividual run();
      void evaluateFitness();
      int getPopulationSize();

      CIndividual m_population[population_size];
      CIndividual m_model;
      void tournamentSelection(CIndividual *);
      CIndividual findBest();
      // Tmp array, Model individual
      void crossoverAndMutation(const CIndividual *);

};
