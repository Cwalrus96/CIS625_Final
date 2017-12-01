#ifndef CLAMMPS_H
#define CLAMMPS_H

#include "lammps.h"
#include "individual.h"

#include <string>

class CLammps
{
   public:
      static LAMMPS_NS::LAMMPS * m_lmp;
      static void initialize();
      static void fileTersoffParameters(const CIndividual &, const std::string &);
      static double getTersoffPotential(const CIndividual &, const std::string &, int);
};

#endif
