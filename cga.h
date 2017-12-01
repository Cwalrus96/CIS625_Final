#include "individual.h"

class CGA
{
   private:
      int m_iterationsCount, m_tournamentSize;
      double m_crossoverProbability, m_mutationProbability;
   public:
   
      const static int population_size = 10000;

      CGA(const double *, const double, const double, const double);
      CIndividual run(int, int);
      void evaluateFitness();
      int getPopulationSize();

      CIndividual m_population[population_size];
      CIndividual m_model;
      void tournamentSelection(CIndividual *);
      CIndividual findBest();
      int findWorstIndex();
      void replaceWorst(CIndividual);
      // Tmp array, Model individual
      void crossoverAndMutation(const CIndividual *);

};
