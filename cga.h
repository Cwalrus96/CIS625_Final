#ifndef CGA_H
#define CGA_H

#include "mpi.h"
#include "individual.h"
#include "clammps.h"
#include "cga.h"

#include <string>

class CGA
{
   private:
      int m_iterationsCount, m_tournamentSize;
      double m_crossoverProbability, m_mutationProbability;
   public:
      int m_id;
      const static int population_size = 100;

      CGA(const double *, const double, const double, const double, int);
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

#endif
