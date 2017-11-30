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

void CIndividual::calculateFitness()
{
  double default_parameters[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};
	double fitness = 0.0;
	for(int i=0; i<PARAMETERS_COUNT; ++i){
		// Squared error - just dummy calculation
		fitness += ((default_parameters[i] - m_params[i]) * (default_parameters[i] - m_params[i]));
	}
	m_fitness = fitness;
}

CIndividual::CIndividual(const double * params, double delta)
{
	memcpy(m_params, params, sizeof(double) * PARAMETERS_COUNT);
	do{
		for(int i=0; i<PARAMETERS_COUNT; ++i){
			m_params[i] = (randomInDeltaNeighborhood(m_params[i],delta));
		}
	}while(checkNotPass());
}

/*CIndividual & CIndividual::operator= (const CIndividual & o)
{
   memcpy(this, &o, sizeof(CIndividual));
   return *this;
}

CIndividual::CIndividual(const CIndividual & o)
{
   memcpy(this, &o, sizeof(CIndividual));
}
*/
void CIndividual::debugPrint(){
	std::cout<<m_params[0];
	for(int i=1; i<PARAMETERS_COUNT; ++i){
		std::cout<<", "<<m_params[i];
	}
	std::cout<<std::endl;
}

int CIndividual::getParamsCount() const{
	return PARAMETERS_COUNT;
}

double CIndividual::getFitness() const{
	return m_fitness;
}

void CIndividual::crossover(const CIndividual & other)
{
   for(int i=1; i<getParamsCount(); i+=2){
      m_params[i] = other.m_params[i];
   }
}

void CIndividual::mutation()
{
	for(int i=0;i<getParamsCount();++i){
		if(Utility::random0to(1) < s_mutationProbability)
		{
			do {
				m_params[i] = randomInDeltaNeighborhood(m_params[i], s_mutationParameterProbability);
   		} while(checkNotPass());
		}
	}
}

bool CIndividual::checkNotPass()
{
	return m_params[8] > m_params[7];
}