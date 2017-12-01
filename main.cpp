#include "mpi.h"
#include "individual.h"
#include "constants.h"
#include "cga.h"
#include "clammps.h"
#include "utility.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <mpi.h>
#include <vector>

std::vector<CIndividual> getBest(CIndividual myBestIndividual, int mpi_id, int n_threads)
{
   std::vector<CIndividual> bestIndividual;

   if(mpi_id != 0)
   {        
      MPI_Send((void*)&myBestIndividual, sizeof(CIndividual), MPI_BYTE, 0, 1, MPI_COMM_WORLD );
   }
   else
   {
      bestIndividual.push_back(myBestIndividual);

      int i = 0;
      while(++i<n_threads){
         MPI_Status status;
         MPI_Recv((void*)&myBestIndividual, sizeof(CIndividual), MPI_BYTE, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status );
         //std::cout << "Received individual, his fitness is "<<myBestIndividual.getFitness()<<std::endl;
         bestIndividual.push_back(myBestIndividual);
      }
   }
   return bestIndividual;
}

double getTimeStamp() {
   static time_t t_start = 0;

   struct timespec ts;
   clock_gettime(CLOCK_REALTIME, &ts);
   if( t_start == 0 ) t_start = ts.tv_sec;

   return (double) (ts.tv_sec - t_start) + ts.tv_nsec * 1.0e-9;
}

int main(int argc, char * argv[])
{
   double default_parameters[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};
   const int root_id = 0;
   int mpi_id,n_threads,init_threads = 4;

   //init MPI
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&mpi_id);
   MPI_Comm_size(MPI_COMM_WORLD,&n_threads);

   CLammps::initialize();

   //time measurement
   double tstart, ttotal;
   tstart = getTimeStamp();

    //goal,initialDelta,cross prob,mutate prob
   CGA geneticRun(default_parameters, 0.2, 1, 0.2);
   const int number_of_iterations = 5;
   const int number_of_island_migrations = 200;
   
   CIndividual myBestIndividual;
   std::vector<CIndividual> bestIndividual;

   double average;
   double lastAverage = std::numeric_limits<double>::lowest();
   int converged = 0;

   geneticRun.evaluateFitness();

   // Maximum number of migration loops
   for(int a=0;a<number_of_island_migrations;++a)
   {
      
      myBestIndividual = geneticRun.findBest();
      //std::cout << "Some individuum, his fitness is "<<myBestIndividual.getFitness()<<std::endl; 

      // Check convergence
      bestIndividual = getBest(myBestIndividual, mpi_id, n_threads);

      if(mpi_id == 0)
      {
         average = 0.0;
         for(int i=0; i<bestIndividual.size(); i++)
         {
            average += bestIndividual[i].getFitness();
         }
         average /= bestIndividual.size();

         if(average <= lastAverage)
         {
            std::cout << "Converged after " << a << " migration loops" << std::endl;
            converged = 1;
         }
         else
         {
            converged = 0;
            lastAverage = average;
         }

         std::cout << "Migration loop: " << a << ", average: " << average << std::endl;

         for(int j=1; j<n_threads; j++)
         {
            MPI_Send(&converged, 1, MPI_INT, j, 3, MPI_COMM_WORLD );
         }
      } else {
         MPI_Recv(&converged, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status );
      }

      if(converged)
      {
         break;
      }      
      // End of check convegence

      //geneticRun.run(number_of_iterations,tournament_size)
      myBestIndividual = geneticRun.run(number_of_iterations, CGA::population_size/5);

      MPI_Send(&myBestIndividual, sizeof(CIndividual), MPI_BYTE, (mpi_id+1) % n_threads, 7, MPI_COMM_WORLD );
      MPI_Recv(&myBestIndividual, sizeof(CIndividual), MPI_BYTE, (mpi_id-1) % n_threads, 7, MPI_COMM_WORLD, &status );
      
      geneticRun.replaceWorst(myBestIndividual);
   }
   
   if(mpi_id == 0)
   {
      CIndividual bestFromBest = Utility::findBestInArray(bestIndividual,n_threads);
      std::cout << "Best - fitness: " << bestFromBest.getFitness() << std::endl;
      bestFromBest.debugPrint();
   }

   MPI_Finalize(); 

   return 0;
}


