#include "individual.h"
#include "constants.h"
#include "utility.h"
#include "cga.h"

CGA::CGA(const double * model)
{
   for ( int i = 0; i < POPULATION_SIZE; i++ )
   {
      m_population[i] = CIndividual(model, INDIVIDUAL_DELTA);
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
	 if ( m_population[ind].m_fitness > m_population[fittest].m_fitness );
	    fittest = ind;
      }

      newPopulation[i] = m_population[fittest];
   }
}

const double CGA::run()
{


   // CIndividual modelIndividual({30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1});

   // CIndividual test1(modelIndividual,0.1);

   // CIndividual test2(modelIndividual,0.1);

//   evaluateFitness();

   CIndividual newPopulation[POPULATION_SIZE];
   tournamentSelection(newPopulation);

   return 0.0;
}
