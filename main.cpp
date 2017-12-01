#include "individual.h"
#include "constants.h"
#include "cga.h"
#include "utility.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <mpi.h>
#include <vector>

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

   //time measurement
   double tstart, ttotal;
   tstart = getTimeStamp();

   //goal,initialDelta,cross prob,mutate prob
   CGA geneticRun(default_parameters, 50, 1, 0.2);
   const int number_of_iterations = 3;
   const int number_of_island_migrations = 3;
   CIndividual myBestIndividual;

   for(int a=0;a<number_of_island_migrations;++a){
      //geneticRun.run(number_of_iterations,tournament_size)
      myBestIndividual = geneticRun.run(number_of_iterations, CGA::population_size/5);
               
      int neighbor = mpi_id;
      if (++neighbor == n_threads) neighbor = 0;

      MPI_Status status;
      MPI_Send((void*)&myBestIndividual, sizeof(CIndividual), MPI_UNSIGNED_CHAR, neighbor, 0, MPI_COMM_WORLD );
      MPI_Recv((void*)&myBestIndividual, sizeof(CIndividual), MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );
      
      geneticRun.replaceWorst(myBestIndividual);
   }

   myBestIndividual = geneticRun.findBest();

   if(mpi_id != root_id){         
      MPI_Send((void*)&myBestIndividual, sizeof(CIndividual), MPI_UNSIGNED_CHAR, root_id, 0, MPI_COMM_WORLD );
   }else{
      std::vector<CIndividual> bestIndividual;
      bestIndividual.push_back(myBestIndividual);

      int i = 0;
      while(++i<n_threads){
         MPI_Status status;
         MPI_Recv((void*)&myBestIndividual, sizeof(CIndividual), MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );
         std::cout<<"received individual, his fitness is "<<myBestIndividual.getFitness()<<std::endl;
         std::cout<<"parameters: ";
         myBestIndividual.debugPrint();
         bestIndividual.push_back(myBestIndividual);
      }

      CIndividual bestFromBest = Utility::findBestInArray(bestIndividual,n_threads);  
      ttotal = getTimeStamp()-tstart;
      std::cout<<"Number of cores/islands: "<<n_threads<<std::endl;
      std::cout<<"Total time spent: "<<ttotal<<std::endl;
      std::cout<<"Fitness after " << number_of_iterations << " iterations: " << bestFromBest.getFitness()<<std::endl;
      std::cout<<"Best individual: " << std::endl;    
      bestFromBest.debugPrint();
   }

   MPI_Finalize(); 

   return 0;
}


