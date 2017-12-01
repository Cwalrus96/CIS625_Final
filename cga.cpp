#include "mpi.h"
#include "input.h"
#include "library.h"
#include "lammps.h"
#include "individual.h"
#include "clammps.h"
#include "cga.h"
#include "utility.h"

#include <string>
#include <fstream>

using namespace std;

CGA::CGA(const double * array, const double initialDelta, double cross, double mutate, int id)
{
   m_id = id;
   m_crossoverProbability = cross;
   m_mutationProbability  = mutate;

   for ( int i = 0; i < population_size; i++ )
   {
      m_population[i] = CIndividual(array, initialDelta);
   }
}

void CGA::tournamentSelection(CIndividual * newPopulation)
{
   for ( int i = 0; i < population_size; i++ )
   {

      int fittest = Utility::randomer.randomIndex(population_size);
      for ( int j = 1; j < m_tournamentSize; j++ )
      {
         int ind = Utility::randomer.randomIndex(population_size);
         if ( m_population[ind].getFitness() > m_population[fittest].getFitness()){
            fittest = ind;
         }
      }

      newPopulation[i] = m_population[fittest];
   }
}

void CGA::crossoverAndMutation(const CIndividual * inArray)
{

   for(int i=0; i<getPopulationSize(); i+=2) {
      // Crossover
      if(Utility::randomer.random0to(1)<m_crossoverProbability) {
         pair<CIndividual,CIndividual> children = CIndividual::crossover(inArray[i],inArray[i+1]);
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


      if(Utility::randomer.random0to(1)<m_mutationProbability)
      {
         m_population[i].mutation(0.1,0.2);
      }
      if(Utility::randomer.random0to(1)<m_mutationProbability)
      {
         m_population[i+1].mutation(0.1,0.2);
      }
   }
}

CIndividual CGA::run(int iter, int torunament)
{
   m_tournamentSize = torunament;


   // CIndividual modelIndividual({30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1});

   // CIndividual test1(modelIndividual,0.1);

   // CIndividual test2(modelIndividual,0.1);

//   evaluateFitness();


   evaluateFitness();
   cout<<"Fitness pred prvni iteraci: " << findBest().getFitness() << endl;

   for(int i=0;i<iter;++i){
      CIndividual newPopulation[population_size];
      tournamentSelection(newPopulation);
      crossoverAndMutation(newPopulation);

      evaluateFitness();

      std::cout<< "Iterace: " << i << ", best fitness: " << findBest().getFitness() << std::endl;
   }

   return findBest();

}

void CGA::replaceWorst(CIndividual newIndividual){
   int worstIndex = findWorstIndex();
   m_population[worstIndex] = newIndividual;
}

int CGA::findWorstIndex(){
   int worst = m_population[0].getFitness();//fuj
   int index = 0;
   for(int i=1;i<population_size;++i){
      if(worst > m_population[i].getFitness()){
         worst = m_population[i].getFitness();
         index = i;
      }
   }
   return index;
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
      m_population[i].calculateFitness(m_id);
   }
}
