#include "mpi.h"
#include "individual.h"
#include "constants.h"
#include "cga.h"
#include "clammps.h"
#include "utility.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char ** argv)
{

   srand(time(NULL));

   double default_parameters[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};

   int rank, numtasks;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

   CGA cga1(default_parameters, 0.1, rank);
   CLammps::initialize();

   int pocetIteraci;
   pocetIteraci = 100;
   CIndividual nejlepsi_typek1(cga1.run(pocetIteraci, 10, 0.9, 0.1));
   std::cout<<"Fitness po " << pocetIteraci << " iteracich: " << nejlepsi_typek1.getFitness()<<std::endl;

   MPI_Finalize();

   return 0;
}
