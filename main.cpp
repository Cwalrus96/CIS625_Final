#include "individual.h"
#include "constants.h"
#include "cga.h"
#include "utility.h"
#include <iostream>
#include <ctime>

int main()
{
   //GAGAGA GAGAG AGAGAGAG
   /*
   double model[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};
   CGA cga(model, 0.1);
   const double res = cga.run();
   */
   srand(time(NULL));

   double model[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};

   CIndividual xModel(model, 0.2);
   CIndividual x1(xModel, true);
   CIndividual x2(xModel, true);
   CIndividual x3(x1);
   CIndividual x4(x2);

   x3.crossover(x2);
   x4.crossover(x1);

   x1.debugPrint();
   x2.debugPrint();
   std::cout << "After crossover:" << std::endl;
   x3.debugPrint();
   x4.debugPrint();

   x3.mutation(xModel);
   x4.mutation(xModel);
   std::cout << "After mutation:" << std::endl;
   x3.debugPrint();
   x4.debugPrint();

   return 0;
}
