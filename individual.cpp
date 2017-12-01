#include "mpi.h"
#include "input.h"
#include "individual.h"
#include "clammps.h"
#include "utility.h"

#include <string>
#include <sstream>

using namespace std;

double CIndividual::randomInDeltaNeighborhood(double number, double delta)
{
	double rangeWidth, rangeOffset, rangeLowBound;

	rangeWidth = (delta * 2) * number;
	rangeLowBound = number - (delta * number);
	rangeOffset = Utility::random0to(rangeWidth);

	return rangeLowBound + rangeOffset;
}

void CIndividual::calculateFitness(int gaID)
{
   double tersoffDif = CLammps::getTersoffPotential(*this, "Ptbcc", gaID) - CLammps::getTersoffPotential(*this, "97xPtbcc", gaID);
   m_fitness = (DFT - tersoffDif)*(DFT - tersoffDif)*(-1);
}

CIndividual::CIndividual(const double * params, double delta)
{
	do{
		for(int i=0; i<PARAMETERS_COUNT; ++i){
			m_params[i] = (randomInDeltaNeighborhood(params[i],delta));
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

string CIndividual::printParameters() const
{
   string params;
	for(int i=0; i<PARAMETERS_COUNT; ++i){
		params += " " + to_string(m_params[i]);
	}
   return params;
}

int CIndividual::getParamsCount() const
{
	return PARAMETERS_COUNT;
}

double CIndividual::getFitness() const
{
	return m_fitness;
}

pair<CIndividual,CIndividual> CIndividual::crossover(const CIndividual & parent1, const CIndividual & parent2)
{

	int mid = Utility::randomIndex(4)+4;
	CIndividual child1,child2;

	const int uniformCross[] = {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0};

	for(int i=0; i<parent1.getParamsCount(); i++)
	{
		if(uniformCross[i])
		{
			child1.m_params[i] = parent2.m_params[i];
			child2.m_params[i] = parent1.m_params[i];
		}
		else
		{
			child1.m_params[i] = parent1.m_params[i];
			child2.m_params[i] = parent2.m_params[i];
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
	return make_pair(child1,child2);
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
