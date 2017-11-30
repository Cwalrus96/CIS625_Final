#include "individual.h"
#include <cstring>
#include "utility.h"
#include "constants.h"
#include <stdio.h>
#include <iostream>

double CIndividual::randomInDeltaNeighborhood(double number, double delta)
{
	double rangeWidth, rangeOffset, rangeLowBound;

	rangeWidth = (delta * 2) * number;
	rangeLowBound = number - (delta * number);
	rangeOffset = Utility::random0to(rangeWidth);

	return rangeLowBound + rangeOffset;
}

void CIndividual::calculateFitness(const CIndividual & model)
{
	double fitness = 0.0;
	for(int i=0; i<PARAMETERS_COUNT; ++i){
		// Squared error - just dummy calculation
		fitness += ((model.m_params[i] - m_params[i]) * (model.m_params[i] - m_params[i]));
	}
	m_fitness = fitness;
}

CIndividual::CIndividual(const double * params)
{
  memcpy(m_params, params, PARAMETERS_COUNT);
}

CIndividual::CIndividual (const double * params, double delta)
{
	do{
		for(int i=0; i<PARAMETERS_COUNT; ++i){
			m_params[i] = (randomInDeltaNeighborhood(params[i],delta));
		}
	}while(m_params[8] < m_params[7]);
}

CIndividual::CIndividual (const CIndividual & model, double delta)
{
	do{
		for(int i=0; i<PARAMETERS_COUNT; ++i){
			m_params[i] = (randomInDeltaNeighborhood(model.m_params[i],delta));
		}
	}while(m_params[8] < m_params[7]);
}

CIndividual & CIndividual::operator= (const CIndividual & o)
{
   memcpy(this, &o, sizeof(CIndividual));

   return *this;
}

CIndividual::CIndividual(const CIndividual & o)
{
   memcpy(this, &o, sizeof(CIndividual));
}

void CIndividual::debugPrint(){
	std::cout<<m_params[0];
	for(int i=1; i<PARAMETERS_COUNT; ++i){
		std::cout<<", "<<m_params[i];
	}
	std::cout<<std::endl;
}
