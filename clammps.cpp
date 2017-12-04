#include "mpi.h"
#include "individual.h"
#include "clammps.h"

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <array>
#include <memory>
#include <iostream>
#include <cstdio>
#include <stdexcept>

void CLammps::fileTersoffParameters(const CIndividual & individual, const std::string & fileName)
{
   std::ofstream file;
   file.open(fileName);

   std::string params = "Pt Pt Pt 3.0 1.0 0.0";

   params += individual.printParameters();

   file << params << std::endl;
   file.close();
}

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    //if (!pipe) return NULL;
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
}

double CLammps::getTersoffPotential(const CIndividual & individual, const std::string & structName, int id)
{
   char buf[2848];

   std::string fileName = "Pt" + std::to_string(id) + ".tersoff";
   fileTersoffParameters(individual, fileName);

   std::string commands = "dimension\t3\n";
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
   commands += "run\t5\n";

   std::ofstream file;
   file.open("in.pt");
   file << commands << std::endl;
   file.close();

   std::string out = exec("../../lammps-11Aug17/src/lmp_mpi -partition 2x1 -in in.pt");

   std::cout << out << std::endl;

   return 1.0;
}

