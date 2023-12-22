#include "util.h"
#include "type.h"
#include "typeEvolvable.h"
#include "geneticAlgorithm.h"
#include "TicTacToe.h"
#include "Player.h"

int main() {
    vector<int> netStructure = {9, 16, 32, 16, 9};
    Player<TicTacToe>::SetNetStructure(netStructure);

    T *chromosomeType = Player<TicTacToe>::GetType();
    T_EVOL *chromosomeTypeEvolvable = Player<TicTacToe>::GetTypeEvolvable();

    int populationSize = 60;
    float mutationBase = 0.08;
    float mutationMultiplier = 2;
    int mutationAdaptationStuckPeriod = 10;
    selection_method selectionMethod = GA_SEL_ELITISM;
    genocide_method genocideMethod = GA_GENO_ALL;
    int genocideStuckPeriod = 50;
    predation_method predationMethod = GA_PRED_RANDOM;
    int predationPeriod = 10;
    boolean isSexual = TRUE;
    boolean hasInheritance = TRUE;

    GA *evolution = geneticAlgorithm_create(populationSize,
                                            mutationBase, mutationMultiplier, mutationAdaptationStuckPeriod,
                                            selectionMethod,
                                            genocideMethod, genocideStuckPeriod,
                                            predationMethod, predationPeriod,
                                            isSexual,
                                            hasInheritance,
                                            chromosomeType, chromosomeTypeEvolvable);

    if(!geneticAlgorithm_init(evolution)){
        printf("init falhou!");
    }

    int generations = 500;
    for(int i=0 ; i<generations ; i+=10) {
        if(!geneticAlgorithm_run(evolution, 10)) {
            printf("evolucao falhou!");
        }
        cout << "Populacao na Geracao numero " << i+10 << endl;
    }

    int gen = geneticAlgorithm_getNumGeneration(evolution);
    printf("Generation: %d\n", gen);
    
    // Get best
    float bestFitness;
    Player<TicTacToe> *best = (Player<TicTacToe> *) geneticAlgorithm_getBestChromosome(evolution, &bestFitness);
    printf("Best fit: (%.2f)\n\n",bestFitness);

    // Save to txt file
    DenseNetwork *best_network = best->GetAI();
    best_network->SaveAs("evol_data/bestInfo.txt");

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

    delete best;
    free(bestFistnessHistory);
    free(meanFistnessHistory);

    geneticAlgorithm_erase(&evolution);

    type_erase(&chromosomeType);
    typeEvolvable_erase(&chromosomeTypeEvolvable);

    return 0;
}