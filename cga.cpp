#include "individual.h"
#include "constants.h"
#include "utility.h"
#include "cga.h"

CGA::CGA(const double * array, const double delta) : m_model(array, delta)
{
   for ( int i = 0; i < POPULATION_SIZE; i++ )
   {
      m_population[i] = CIndividual(m_model, true);
   }
}

void CGA::tournamentSelection(CIndividual * newPopulation)
{
   for ( int i = 0; i < POPULATION_SIZE; i++ )
   {

      int fittest = Utility::randomIndex(100);
      for ( int j = 0; j < TOURNAMENT_SIZE-1; j++ )
      {
         int ind = Utility::randomIndex(100);
         if ( m_population[ind].getFitness() > m_population[fittest].getFitness());
         fittest = ind;
      }

      newPopulation[i] = m_population[fittest];
   }
}

void CGA::crossoverAndMutation(const CIndividual * inArray)
{
   int tmpIndex;

   // Copy tmp population to member array HERE
   for(int i=0; i<getPopulationSize(); i++)
   {
      m_population[i] = inArray[i];
   }

   for(int i=0; i<getPopulationSize(); i+=2) {
      // Crossover
      if(Utility::random0to(1)<0.9) {
         m_population[i].crossover(inArray[i+1]);
         m_population[i+1].crossover(inArray[i]);
      }

      // Mutation
      if(Utility::random0to(1)<0.1)
      {
         tmpIndex = Utility::randomIndex(PARAMETERS_COUNT);
         m_population[i].mutation(m_model, tmpIndex);
      }
      if(Utility::random0to(1)<0.1)
      {
         tmpIndex = Utility::randomIndex(PARAMETERS_COUNT);
         m_population[i].mutation(m_model, tmpIndex);
      }
   }
}

const double CGA::run()
{


   // CIndividual modelIndividual({30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1});

   // CIndividual test1(modelIndividual,0.1);

   // CIndividual test2(modelIndividual,0.1);

//   evaluateFitness();

   CIndividual newPopulation[POPULATION_SIZE];

   evaluateFitness();
   tournamentSelection(newPopulation);

   return 0.0;
}

int CGA::getPopulationSize()
{
   return POPULATION_SIZE;
}

void CGA::evaluateFitness()
{
   for(int i=0; i<getPopulationSize(); i++)
   {
      m_population[i].calculateFitness(m_model);
   }
}
