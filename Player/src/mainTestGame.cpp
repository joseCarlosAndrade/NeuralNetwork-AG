
#include "../include/util.h"
#include "../include/type.h"
#include "../include/typeEvolvable.h"
#include "../include/geneticAlgorithm.h"
//#include "../include/funcaoEscrota.h"

#include "neural_network.h"

using namespace MiniDNN;

int main() {
    // auto game = TicTacToe();
    // int num_layers = 6;
    // std::vector<int> num_neurons = {9,32,32,64,32,32,9};
    // Network player1;
    // Network player2;
    // generate_RNN(player1, num_neurons.size()-1, num_neurons);
    // generate_RNN(player2, num_neurons.size()-1, num_neurons);
    // auto parameters = player1.get_parameters();
    // deserialize_parameters_txt("evol_data/bestInfo.txt", parameters);
    // player1.set_parameters(parameters);
    // player2.set_parameters(parameters);
    // int wrong_moves1 = 0, wrong_moves2 = 0;
    // auto game_result = game.ComVSCom(&player1, &player2, &wrong_moves1, &wrong_moves2, true);
    // std::cout << "\nwrong moves 1: " <<wrong_moves1<<std::endl;
    // std::cout << "\nwrong moves 2: " <<wrong_moves2<<std::endl;
    // return 0;


    T *chromosomeType = player_getType();
    T_EVOL *chromosomeTypeEvolvable = player_getTypeEvolvable();

    int populationSize = 30;
    float mutationBase = 0.02;
    float mutationMultiplier = 2;
    int mutationAdaptationStuckPeriod = 8;
    selection_method selectionMethod = GA_SEL_ROULETTEWHEEL;   
    genocide_method genocideMethod = GA_GENO_ALL;
    int genocideStuckPeriod = 40;  // at least 4 times bigger than adaptation stuck period
    predation_method predationMethod = GA_PRED_NONE;
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

    int generations = 400;
    if(!geneticAlgorithm_run(evolution, generations)) {
        printf("evolucao falhou!");
    }

    int gen = geneticAlgorithm_getNumGeneration(evolution);
    printf("Generation: %d\n", gen);
    
    // Get best
    float bestFitness;
    PLAYER *best = (PLAYER *) geneticAlgorithm_getBestChromosome(evolution, &bestFitness);
    printf("Best fit: (%.2f)\n\n",bestFitness);

    //SAVE TO TXT FILE
    // FILE *bestInfo = fopen("evol_data/bestInfo.txt", "w");
    auto best_network = player_getElement(best);
    serialize_parameters_txt("evol_data/bestInfo.txt", best_network.get_parameters());

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