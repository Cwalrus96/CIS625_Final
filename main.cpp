#include "individual.h"

//30611 113.064 0.5289 0.5916 0.0426 1.3484 80.5297 2.85 2.25 2.9699 1017.1

int main(){

	//double tmpArray[] = {}

	CIndividual modelIndividual({30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1});

	CIndividual test1(modelIndividual,0.1);

	CIndividual test2(modelIndividual,0.1);


	modelIndividual.debugPrint();
	test1.debugPrint();
	test2.debugPrint();

	return 0;
}