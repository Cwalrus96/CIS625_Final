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
   
   CGA cga1(default_parameters, 0.1);
   CGA cga2(default_parameters, 0.1);
   CGA cga3(default_parameters, 0.1);
   
   /*std::cout<<"defaultni parametry:"<<std::endl;
   CIndividual a(default_parameters, 0);
   a.debugPrint();
   std::cout<<std::endl;
*/
   // cga.run(pocet iteraci, velikost turnaje, pravdepodobnost Xoveru, pravdepodobnost mutace)

   int pocetIteraci;
   pocetIteraci = 100;
   CIndividual nejlepsi_typek1(cga1.run(pocetIteraci, 10, 0.9, 0.1));
   std::cout<<"Fitness po " << pocetIteraci << " iteracich: " << nejlepsi_typek1.getFitness()<<std::endl;

   pocetIteraci = 1000;
   CIndividual nejlepsi_typek2(cga2.run(pocetIteraci, 10, 0.9, 0.1));
   std::cout<<"Fitness po " << pocetIteraci << " iteracich: " << nejlepsi_typek2.getFitness()<<std::endl;

   pocetIteraci = 10000;
   CIndividual nejlepsi_typek3(cga3.run(pocetIteraci, 10, 0.9, 0.1));
   std::cout<<"Fitness po " << pocetIteraci << " iteracich: " << nejlepsi_typek3.getFitness()<<std::endl;
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
