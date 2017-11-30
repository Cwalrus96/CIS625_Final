#include "individual.h"
#include "constants.h"
#include "cga.h"
#include "utility.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{

   srand(time(NULL));

   //GAGAGA GAGAG AGAGAGAG

   double default_parameters[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};
   
   CGA cga(default_parameters, 0.1);
   
   /*std::cout<<"defaultni parametry:"<<std::endl;
   CIndividual a(default_parameters, 0);
   a.debugPrint();
   std::cout<<std::endl;
*/
   CIndividual nejlepsi_typek (cga.run());

   std::cout<<"nejlepsi typek:"<<std::endl;
   std::cout<<nejlepsi_typek.getFitness()<<std::endl;
   //std::cout<<"nejlepsi typek:"<<std::endl;
   //nejlepsi_typek.debugPrint();
   //std::cout<<std::endl;
   /*

   CIndividual x1(default_parameters, 0.2);
   CIndividual x2(default_parameters, 0.2);

   x1.calculateFitness();
   x2.calculateFitness();

   std::cout<<"fitness x1:"<<std::endl;
   std::cout<<x1.getFitness()<<std::endl;
   x1.debugPrint();
   std::cout<<std::endl;


   std::cout<<"fitness x2:"<<std::endl;
   std::cout<<x2.getFitness()<<std::endl;
   x2.debugPrint();
   std::cout<<std::endl;

*/
   /*CIndividual x3(x1);
   CIndividual x4(x2);

   x3.crossover(x2);
   x4.crossover(x1);

   x1.debugPrint();
   x2.debugPrint();
   std::cout << "After crossover:" << std::endl;
   x3.debugPrint();
   x4.debugPrint();

   x3.mutation();
   x4.mutation();
   std::cout << "After mutation:" << std::endl;
   x3.debugPrint();
   x4.debugPrint();
*/
   return 0;
}
