#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "type.h"
#include "typeEvolvable.h"

//--------SELECTION METHOD----------
typedef enum {
    GA_SEL_ELITISM = 1,
    GA_SEL_2WAYTOURNAMENT = 2,
    GA_SEL_ROULETTEWHEEL = 3
} selection_method;
//----------------------------------

//---------GENOCIDE METHOD----------
typedef enum {
    GA_GENO_NONE = 0,
    GA_GENO_KEEPBEST = 1,
    GA_GENO_ALL = 2
} genocide_method;
//----------------------------------

//--------PREDATION METHOD----------
typedef enum {
    GA_PRED_NONE = 0,
    GA_PRED_RANDOM = 1,
    GA_PRED_SYNTHESIS = 2
} predation_method;
//----------------------------------


// -> GeneticAlgorithm eh um TAD que carrega os parametros de um algoritmo genetico/evolutivo
// -> tambem cuida da execucao do algoritmo

typedef struct geneticAlgorithm_st GA;

GA * geneticAlgorithm_create(const int populationSize,
                             const float mutationBase, const float mutationMultiplier, const int mutationAdaptationStuckPeriod,
                             const selection_method selectionMethod,
                             const genocide_method genocideMethod, const int genocideStuckPeriod,
                             const predation_method predationMethod, const int predationPeriod,
                             const boolean isSexual,
                             const boolean hasInheritance,
                             T *populationType, T_EVOL *populationTypeEvolvable);

boolean geneticAlgorithm_init(GA *geneticAlgorithm);
boolean geneticAlgorithm_run(GA *geneticAlgorithm, const int numGenerations);

int geneticAlgorithm_getNumGeneration(const GA *geneticAlgorithm);
void * geneticAlgorithm_getBestChromosome(const GA *geneticAlgorithm, float *out_bestFitness);
void ** geneticAlgorithm_getPopulation(const GA *geneticAlgorithm, float **out_populationFitness);

float * geneticAlgorithm_getBestFitnessHistory(const GA *geneticAlgorithm);
float * geneticAlgorithm_getMeanFitnessHistory(const GA *geneticAlgorithm);

void geneticAlgorithm_erase(GA **geneticAlgorithm_addr);

#ifdef __cplusplus
}
#endif

#endif //GENETICALGORITHM_H