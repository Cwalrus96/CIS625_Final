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

// Making a model
CIndividual::CIndividual(const double * params, double delta)
{
	m_fitness = delta;
	memcpy(m_params, params, sizeof(double) * PARAMETERS_COUNT);
}

// Making random individual based on model
CIndividual::CIndividual (const CIndividual & model, bool generateRandom)
{
	double delta = model.getFitness();
	do{
		for(int i=0; i<PARAMETERS_COUNT; ++i){
			m_params[i] = (randomInDeltaNeighborhood(model.m_params[i],delta));
		}
	}while(checkNotPass());
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

int CIndividual::getParamsCount() const
{
	return PARAMETERS_COUNT;
}

double CIndividual::getFitness() const
{
	return m_fitness;
}

void CIndividual::crossover(const CIndividual & other)
{
   for(int i=1; i<getParamsCount(); i+=2)
   {
      m_params[i] = other.m_params[i];
   }
}

/*void CIndividual::mutation(const CIndividual & model, int changeIndex)
{
   do {
      CIndividual tmp(model, true);
      m_params[changeIndex] = tmp.m_params[changeIndex];
   } while(m_params[8] > m_params[7]);
}*/

void CIndividual::mutation(const CIndividual & model)
{
	double delta = model.getFitness();
	for(int i=0;i<getParamsCount();i++)
	{
		if(Utility::random0to(1) < 0.1)
		{
			do {
				m_params[i] = randomInDeltaNeighborhood(m_params[i], delta);
   			} while(checkNotPass());
   			//std::cout << "I'm mutating" << std::endl;
		}
	}
}

bool CIndividual::checkNotPass()
{
	return m_params[8] > m_params[7];
}