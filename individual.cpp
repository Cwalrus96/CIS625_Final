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
	rangeOffset = Utility::randomer.random0to(rangeWidth);

	return rangeLowBound + rangeOffset;
}

void CIndividual::calculateFitness()
{
   double default_parameters[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};
	double tmp, fitness;
	fitness = 0.0;
	for(int i=0; i<PARAMETERS_COUNT; ++i){
		// Squared error - just dummy calculation
		tmp = (default_parameters[i] - m_params[i]);
		fitness -= tmp*tmp;
		//fitness += ((default_parameters[i] - m_params[i]) * (default_parameters[i] - m_params[i]));
	}
	m_fitness = fitness;
	//std::cout<<fitness<<std::endl;
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
}*/

/*CIndividual::CIndividual(const CIndividual & o)
{
   memcpy(this, &o, sizeof(CIndividual));
}*/

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

	CIndividual child1,child2;

	double ran = Utility::randomer.random0to(1);
	int *uniformCross;

	int uniformCross1[] = {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0};
	int uniformCross2[] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1};	
	int uniformCross3[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
	int uniformCross4[] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

	if(ran < 0.25){
		uniformCross = uniformCross1;
	}else if(ran < 0.5){
		uniformCross = uniformCross2;

	}else if (ran < 0.75){
		uniformCross = uniformCross3;

	}else{
		uniformCross = uniformCross4;
	}

	for(int i=0; i<parent1.getParamsCount(); i++)
	{
		if(uniformCross[i])
		{
			child1.m_params[i] = parent1.m_params[i];
			child2.m_params[i] = parent2.m_params[i];
		}
		else
		{
			child1.m_params[i] = parent2.m_params[i];
			child2.m_params[i] = parent1.m_params[i];
		}
	}
	/*

	for(int i=0; i<mid; i+=1){
		child1.m_params[i] = parent1.m_params[i];
		child2.m_params[i] = parent2.m_params[i];
	}

	for(int i=mid; i< parent1.getParamsCount(); i+=1){
		child1.m_params[i] = parent2.m_params[i];
		child2.m_params[i] = parent1.m_params[i];
	}   
	*/
	return std::make_pair(child1,child2);
}

void CIndividual::mutation(double mutationParameterProbability,double mutationParameterDelta)
{
	for(int i=0;i<getParamsCount();++i){
		if(Utility::randomer.random0to(1) < mutationParameterProbability)
		{
			double tmp = m_params[i];
			do {
				m_params[i] = randomInDeltaNeighborhood(tmp, mutationParameterDelta);
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