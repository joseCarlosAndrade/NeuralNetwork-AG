
#include "../include/util.h"
#include "../include/type.h"
#include "../include/typeEvolvable.h"
#include "../include/geneticAlgorithm.h"
//#include "../include/funcaoEscrota.h"

#include "neural_network.h"

using namespace MiniDNN;

int main() {
    T *chromosomeType = player_getType();
    T_EVOLVABLE *chromosomeTypeEvolvable = player_getTypeEvolvable();

    int populationSize = 30;
    float mutationBase = 0.02;
    float mutationMultiplier = 2;
    int mutationAdaptationStuckPeriod = 10;
    selection_method selectionMethod = GA_SEL_ELITISM;
    genocide_method genocideMethod = GA_GENO_KEEPBEST;
    int genocideStuckPeriod = 60;
    predation_method predationMethod = GA_PRED_RANDOM;
    int predationPeriod = 10;
    boolean isSexual = TRUE;
    boolean hasInheritance = FALSE;

    GA *evolution = geneticAlgorithm_create(populationSize,
                                            mutationBase, mutationMultiplier, mutationAdaptationStuckPeriod,
                                            selectionMethod,
                                            genocideMethod, genocideStuckPeriod,
                                            predationMethod, predationPeriod,
                                            isSexual,
                                            hasInheritance,
                                            chromosomeType, chromosomeTypeEvolvable);


    playerInitFunction(nullptr, 0);

    if(!geneticAlgorithm_init(evolution)){
        printf("init falhou!");
    }

    int generations = 30;
    if(!geneticAlgorithm_run(evolution, generations)) {
        printf("evolucao falhou!");
    }

    int gen = geneticAlgorithm_getNumGeneration(evolution);
    printf("Generation: %d\n", gen);


    FILE *bestInfo = fopen("evol_data/bestInfo.txt", "w");

    float bestFitness;
    PLAYER *best = (PLAYER *) geneticAlgorithm_getBestChromosome(evolution, &bestFitness);
    printf("Best: (%.2f, %.2f)\n\n", player_getElement(best), bestFitness);
    fprintf(bestInfo, "%f\n\n", player_getElement(best));
    fprintf(bestInfo, "Fitness: %f", bestFitness);

    fclose(bestInfo);


    FILE *history = fopen("evol_data/history.csv", "w");

    float *bestFistnessHistory = geneticAlgorithm_getBestFitnessHistory(evolution);
    for(int i=0 ; i<=gen ; i++) {
        fprintf(history, "%f", bestFistnessHistory[i]);
        if(i != gen) {
            fprintf(history, ", ");
        }
    }
    fprintf(history, "\n\n");

    float *meanFistnessHistory = geneticAlgorithm_getMeanFitnessHistory(evolution);
    for(int i=0 ; i<=gen ; i++) {
        fprintf(history, "%f", meanFistnessHistory[i]);
        if(i != gen) {
            fprintf(history, ", ");
        }
    }

    fclose(history);
    player_erase(&best);
    free(bestFistnessHistory);
    free(meanFistnessHistory);

    geneticAlgorithm_erase(&evolution);

    type_erase(&chromosomeType);
    typeEvolvable_erase(&chromosomeTypeEvolvable);

    return 0;
}