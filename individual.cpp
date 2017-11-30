#include "individual.h"
#include <cstring>
#include "utility.h"
#include "constants.h"
#include <stdio.h>
#include <iostream>
#include <utility>

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
	m_fitness = fitness*(-1);
}

CIndividual::CIndividual(const double * params, double delta)
{
	do{
		for(int i=0; i<PARAMETERS_COUNT; ++i){
			m_params[i] = (randomInDeltaNeighborhood(params[i],delta));
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
void CIndividual::debugPrint() const{
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

std::pair<CIndividual,CIndividual> CIndividual::crossover(const CIndividual & parent1, const CIndividual & parent2)
{

	int mid = Utility::randomIndex(4)+4;
	CIndividual child1,child2;

	for(int i=0; i<mid; i+=1){
		child1.m_params[i] = parent1.m_params[i];
		child2.m_params[i] = parent2.m_params[i];
	}

	for(int i=mid; i< parent1.getParamsCount(); i+=1){
		child1.m_params[i] = parent2.m_params[i];
		child2.m_params[i] = parent1.m_params[i];
	}   

  return std::make_pair(child1,child2);
}

void CIndividual::mutation()
{
	for(int i=0;i<getParamsCount();++i){
		if(Utility::random0to(1) < s_mutationProbability)
		{
			double tmp = m_params[i];
			do {
				m_params[i] = randomInDeltaNeighborhood(tmp, s_mutationParameterDelta);
 				//std::cout<<"index: "<<i<<" "<<m_params[i]<<std::endl;
   		} while((i == 7 || i == 8) && checkNotPass());
		}
	}
}

bool CIndividual::checkNotPass()
{
	//std::cout<<m_params[8]<<" < "<<m_params[7]<<std::endl;
	return m_params[8] > m_params[7];
}