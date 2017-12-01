#include <cstdlib>
#include "utility.h"
#include <ctime>

/*double Utility::random0to(double max){
   return (double)rand() / ((double)RAND_MAX) * max;
}

int Utility::randomIndex(int max){
   return (double)rand() / ((double)RAND_MAX + 1) * max;
}*/

CRandom Utility::randomer;

CRandom::CRandom(){ 
   std::random_device rd;  
   m_generator.seed(rd());
}

double CRandom::random0to(double max){    
   std::uniform_real_distribution<double> dis(0, max);
   return dis(m_generator);
}

int CRandom::randomIndex(int max){
   std::uniform_int_distribution<int> dis(0, max-1);
   return dis(m_generator);
}

CIndividual Utility::findBestInArray(const std::vector<CIndividual> array,int size){

   if(size == 0)
      return CIndividual();

   double fitness = array[0].getFitness();
   int ind = 0;

   for(int i=1;i<size;++i){
      if(fitness < array[i].getFitness()){
         ind = i;
         fitness = array[i].getFitness();
      }
   }

   return array[ind];
}