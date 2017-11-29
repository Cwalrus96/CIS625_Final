#include <utility>
#include <iostream>
#include "utility.h"
#include "individual.h"


const int CIndividual::parameters_count = 11;

double CIndividual::randomInDeltaNeighborhood(double number, double delta){
	double rangeWidth, rangeOffset, rangeLowBound;

	rangeWidth = (delta * 2) * number;
	rangeLowBound = number - (delta * number);
	rangeOffset = Utility::random0to(rangeWidth);

	return rangeLowBound + rangeOffset;
}

void CIndividual::calculateFitness(const CIndividual & model){
	double fitness = 0.0;
	for(int i=0; i<parameters_count; ++i){
		// Squared error - just dummy calculation
		fitness += ((model.m_params[i] - m_params[i]) * (model.m_params[i] - m_params[i]));
	}
	m_fitness = fitness;
}

CIndividual::CIndividual(const std::vector<double> & params){
  m_params = params;
}

CIndividual::CIndividual (const CIndividual & model, double delta){
	do{
		m_params.clear();
		for(int i=0; i<parameters_count; ++i){
			m_params.push_back(randomInDeltaNeighborhood(model.m_params[i],delta));
		}
	}while(m_params[8] < m_params[7]);
}

void CIndividual::debugPrint(){
	std::cout<<m_params[0];
	for(int i=1; i<parameters_count; ++i){
		std::cout<<", "<<m_params[i];
	}
	std::cout<<std::endl;
}