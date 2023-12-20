#include "../include/util.h"
#include "../include/type.h"
#include "../include/typeEvolvable.h"
#include "../include/geneticAlgorithm.h"
#include "../include/funcaoEscrota.h"

int main() {
    T *chromosomeType = funcaoEscrota_getType();
    T_EVOL *chromosomeTypeEvolvable = funcaoEscrota_getTypeEvolvable();

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

    if(!geneticAlgorithm_init(evolution)) {
        printf("init falhou!");
    }

    int generations = 300;
    if(!geneticAlgorithm_run(evolution, generations)) {
        printf("evolucao falhou!");
    }

    int gen = geneticAlgorithm_getNumGeneration(evolution);
    printf("Generation: %d\n", gen);



    FILE *bestInfo = fopen("evol_data/bestInfo.txt", "w");

    float bestFitness;
    FUNCAOESCROTA *best = (FUNCAOESCROTA *) geneticAlgorithm_getBestChromosome(evolution, &bestFitness);
    printf("Best: (%.2f, %.2f)\n\n", funcaoEscrota_getX(best), bestFitness);
    fprintf(bestInfo, "%f\n\n", funcaoEscrota_getX(best));
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



    funcaoEscrota_erase(&best);
    free(bestFistnessHistory);
    free(meanFistnessHistory);

    geneticAlgorithm_erase(&evolution);

    type_erase(&chromosomeType);
    typeEvolvable_erase(&chromosomeTypeEvolvable);

    return 0;
}