#ifndef CLAMMPS_H
#define CLAMMPS_H

#include "individual.h"

#include <string>

class CLammps
{
   public:
      static void fileTersoffParameters(const CIndividual &, const std::string &);
      static double getTersoffPotential(const CIndividual &, const std::string &, int);
};

#endif
