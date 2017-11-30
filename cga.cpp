#include "individual.h"
#include "constants.h"
#include "utility.h"
#include "cga.h"
#include <iostream>

CGA::CGA(const double * array, const double delta)
{


   for ( int i = 0; i < population_size; i++ )
   {
      m_population[i] = CIndividual(array, delta);
   }
}

void CGA::tournamentSelection(CIndividual * newPopulation)
{
   for ( int i = 0; i < population_size; i++ )
   {

      int fittest = Utility::randomIndex(population_size);
      for ( int j = 1; j < m_tournamentSize; j++ )
      {
         int ind = Utility::randomIndex(population_size);
         if ( m_population[ind].getFitness() > m_population[fittest].getFitness());
         fittest = ind;
      }

      newPopulation[i] = m_population[fittest];
   }
}

void CGA::crossoverAndMutation(const CIndividual * inArray)
{

   for(int i=0; i<getPopulationSize(); i+=2) {
      // Crossover
      if(Utility::random0to(1)<m_crossoverProbability) {
         std::pair<CIndividual,CIndividual> children = CIndividual::crossover(inArray[i],inArray[i+1]);
/*
         inArray[i].debugPrint();
         inArray[i+1].debugPrint();
         children.first.debugPrint();
         children.second.debugPrint();

         std::cout<<std::endl;
*/
         m_population[i] = children.first;
         m_population[i+1] = children.second;
      }


      if(Utility::random0to(1)<m_mutationProbability)
      {
         m_population[i].mutation();
      }
      if(Utility::random0to(1)<m_mutationProbability)
      {
         m_population[i+1].mutation();
      }
   }
}

CIndividual CGA::run(int iter, int torunament, double cross, double mutate)
{
   m_tournamentSize = torunament;
   m_crossoverProbability = cross;
   m_mutationProbability  = mutate;


   // CIndividual modelIndividual({30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1});

   // CIndividual test1(modelIndividual,0.1);

   // CIndividual test2(modelIndividual,0.1);

//   evaluateFitness();

   evaluateFitness();

   for(int i=0;i<iter;++i){
      CIndividual newPopulation[population_size];
      tournamentSelection(newPopulation);
      crossoverAndMutation(newPopulation);
      evaluateFitness();
   }
   
   return findBest();

}

CIndividual CGA::findBest(){
   int fittest = m_population[0].getFitness();//fuj
   int index = 0;
   for(int i=1;i<population_size;++i){
      if(fittest < m_population[i].getFitness()){
         fittest = m_population[i].getFitness();
         index = i;
      }
   }
   return m_population[index];
}

int CGA::getPopulationSize()
{
   return population_size;
}

void CGA::evaluateFitness()
{
   for(int i=0; i<getPopulationSize(); i++)
   {
      m_population[i].calculateFitness();
   }
}
