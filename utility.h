#ifndef UTILITY
#define UTILITY

#include "individual.h"
#include <random>
#include <vector>

class CRandom{
   public:
   double random0to(double);
   int randomIndex(int);
   CRandom();

   private:
   std::mt19937 m_generator;
};

class Utility{
  public:
   static CIndividual findBestInArray(const std::vector<CIndividual>,int);
   static CRandom randomer;
};



#endif
