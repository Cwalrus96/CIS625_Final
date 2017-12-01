#include "mpi.h"
#include "input.h"
#include "library.h"
#include "lammps.h"
#include "individual.h"
#include "clammps.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace LAMMPS_NS;

LAMMPS * CLammps::m_lmp;

void CLammps::initialize()
{
//   char args[3][20] = {"-log none", "-echo none", "-screen none"};

   char * args = "-log none";
   CLammps::m_lmp = new LAMMPS(1, &args, MPI_COMM_WORLD);

}

void CLammps::fileTersoffParameters(const CIndividual & individual, const std::string & fileName)
{
   std::ofstream file;
   file.open(fileName);

   std::string params = "Pt Pt Pt 3.0 1.0 0.0";

   params += individual.printParameters();

   file << params << std::endl;
   file.close();
}

double CLammps::getTersoffPotential(const CIndividual & individual, const std::string & structName, int id)
{
   char buf[548];

   std::string fileName = "Pt" + std::to_string(id) + ".tersoff";
   fileTersoffParameters(individual, fileName);

   std::string commands = "dimension\t3\n";
   commands += "log\tnone\n";
   commands += "echo\tnone\n";
   commands += "boundary\tp p p\n";
   commands += "units\treal\n";
   commands += "atom_style\tcharge\n";
   commands += "read_data\tdata" + structName + ".in\n";
   commands += "pair_style\ttersoff\n";
   commands += "pair_coeff\t* * Pt" + to_string(id) + ".tersoff Pt\n";
   commands += "neighbor\t2 bin\n";
   commands += "neigh_modify\tevery 10 delay 0 check no\n";
   commands += "minimize\t1.0e-4 1.0e-6 100 1000\n";
   commands += "timestep\t0.25\n";

   lammps_commands_string(m_lmp, (char*) commands.c_str());

   int npipe[2];
   pipe(npipe);
   int saved_stdout = dup(STDOUT_FILENO);
   dup2(npipe[1], STDOUT_FILENO);
   close(npipe[1]);

   lammps_command(m_lmp, "run\t5\n");

   read(npipe[0], buf, sizeof(buf));

   dup2(saved_stdout, STDOUT_FILENO);

   lammps_command(m_lmp, "clear\n");

   std::stringstream ss;
   ss.str(buf);
   std::string line;
   double etotal;

   for ( int i = 0; i < 8; i++ )
   {
      std::getline( ss, line );
   }

   for ( int i = 0; i < 5; i++ )
   {
      ss >> etotal;
   }

   std::cout << "HE " << etotal << std::endl;

   return etotal;
}

