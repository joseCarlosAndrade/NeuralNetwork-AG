#include "../include/geneticAlgorithm.h"

struct geneticAlgorithm_st {
    int populationSize;
    float mutationBase;
    float mutationMultiplier;
    int mutationAdaptationStuckPeriod;
    SelectionFunction selectionFunction;
    GenocidedSubstitutionFunction genocidedSubstitutionFunction;
    int genocideStuckPeriod;
    PredatedSubstitutionFunction predatedSubstitutionFunction;
    int predationPeriod;
    boolean isSexual;
    boolean hasInheritance;

    int generation;
    void **population;
    float *fitnesses;
    int bestChromosomeIndex;

    int generationsStuck;
    float mutationRate;

    void *bestOfTheBest;
    float bestOfTheBestFitness;

    float **inheritances;

    float *bestFitnessHistory;
    float *meanFitnessHistory;

    T *populationType;
    T_EVOLVABLE *populationTypeEvolvable;
};



#define chromosomeSize(t) type_getSize(t)
#define copyChromosome(chromosome, t) type_getCopyFunction(t)(chromosome)
#define compareChromosomes(chromosome1, chromosome2, t) type_getCompareFunction(t)(chromosome1, chromosome2)
#define printChromosome(chromosome, t) type_getPrintFunction(t)(chromosome)
#define eraseChromosome(chromosome_addr, t) type_getEraseFunction(t)(chromosome_addr)

#define initChromosomeRand(t_evol) typeEvolvable_getInitFunction(t_evol)(NULL, 0)
#define initChromosomeSynthesis(population, popSize, t_evol) typeEvolvable_getInitFunction(t_evol)(population, popSize)
#define evaluatePopulation(population, popSize, out_fitness, t_evol) typeEvolvable_getEvaluateFunction(t_evol)(population, popSize, out_fitness)
#define crossover(chromosome1, chromosome2, t_evol) typeEvolvable_getCrossoverFunction(t_evol)(chromosome1, chromosome2)
#define mutate(chromosome, rate, t_evol) typeEvolvable_getMutateFunction(t_evol)(chromosome, rate)



typedef void (*SelectionFunction)(GA *, int, int *, int *); // Modelo de ponteiro de funcao de selecao
static void selectElitism(GA *geneticAlgorithm, int currentIndex, int *out_parent1Index, int *out_parent2Index);
static void select2WayTournament(GA *geneticAlgorithm, int currentIndex, int *out_parent1Index, int *out_parent2Index);
static void selectRouletteWheel(GA *geneticAlgorithm, int currentIndex, int *out_parent1Index, int *out_parent2Index);

typedef void ** (*GenocidedSubstitutionFunction)(GA *); // Modelo de ponteiro de funcao para gerar nova populacao apos genocidio
static void ** genocidedSubstituteKeepBest(GA *geneticAlgorithm);
static void ** genocidedSubstituteAll(GA *geneticAlgorithm);

typedef void * (*PredatedSubstitutionFunction)(GA *); // Modelo de ponteiro de funcao para gerar um substituto para o cromossomo predado
static void * predatedSubstituteRandom(GA *geneticAlgorithm);
static void * predatedSubstituteSynthesis(GA *geneticAlgorithm);



static boolean runGeneration(GA *geneticAlgorithm);
static boolean evolvePopulation(GA *geneticAlgorithm);
static boolean applyExternalAgents(GA *geneticAlgorithm);
static boolean adaptMutation(GA *geneticAlgorithm);
static boolean performGenocide(GA *geneticAlgorithm);
static boolean performPredation(GA *geneticAlgorithm);

static void updateFitnesses(GA *geneticAlgorithm);
static void updateBestOfTheBest(GA *geneticAlgorithm);
static void updateInheritances(GA *geneticAlgorithm);
static float getThisGenBestFitness(GA *geneticAlgorithm, boolean considerBestOfTheBest);
static float getThisGenWorstFitness(GA *geneticAlgorithm);

static boolean isInitialized(GA *geneticAlgorithm);
static boolean isStuck(GA *geneticAlgorithm);
static boolean shouldProtectIndex(GA *geneticAlgorithm, int index);
static boolean shouldAdaptMutation(GA *geneticAlgorithm);
static boolean shouldGenocide(GA *geneticAlgorithm);
static boolean shouldPredate(GA *geneticAlgorithm);

static void resetState(GA *geneticAlgorithm);
static void resetStuck(GA *geneticAlgorithm);
static void resetInheritances(GA *geneticAlgorithm);

static int findBestChromosomeIndex(float *fitnesses, int populationSize, float **inheritances);
static int findWorstChromosomeIndex(float *fitnesses, int populationSize, float **inheritances);
static float calcMeanFitness(float *fitnesses, int populationSize);
static float calcInheritedFitnessSum(float **inheritances, int chromosomeIndex);
static float calcMutation(float mutationRate);

static void ** copyPopulation(void **population, int populationSize, T *populationType);
static void erasePopulation(void ***population_addr, int populationSize, T *populationType);
static float * copyFitnessVec(float *fitnessVec, int vecSize);
static void eraseFitnessVec(float **fitnessVec_addr);
static void eraseFitnessMat(float ***fitnessMat_addr, int matRows);



#define ROULETTE_MAX_RATIO 20
#define STUCK_THRESHOLD 0.000001
#define MUTATION_RATE_LIMIT 0.6
#define PERIODS_TRY_REDUCE_MUTATION 2
#define INHERITANCE_LENGTH 4

GA * geneticAlgorithm_create(const int populationSize, const float mutationBase, const float mutationMultiplier, const int mutationAdaptationStuckPeriod, const selection_method selectionMethod, const genocide_method genocideMethod, const int genocideStuckPeriod, const predation_method predationMethod, const int predationPeriod, const boolean isSexual, const boolean hasInheritance, T *populationType, T_EVOLVABLE *populationTypeEvolvable) {
    GA *geneticAlgorithm = (GA *) malloc(1*sizeof(GA));
    if(geneticAlgorithm == NULL) {
        return NULL;
    } // Trata falha no malloc

    geneticAlgorithm->populationSize = populationSize;
    geneticAlgorithm->mutationBase = mutationBase;
    geneticAlgorithm->mutationMultiplier = mutationMultiplier;
    geneticAlgorithm->mutationAdaptationStuckPeriod = mutationAdaptationStuckPeriod;

    switch(selectionMethod) {
        case GA_SEL_ELITISM:
            geneticAlgorithm->selectionFunction = selectElitism;
            break;
        case GA_SEL_2WAYTOURNAMENT:
            geneticAlgorithm->selectionFunction = select2WayTournament;
            break;
        case GA_SEL_ROULETTEWHEEL:
            geneticAlgorithm->selectionFunction = selectRouletteWheel;
            break;
        default:
            geneticAlgorithm_erase(&geneticAlgorithm);
            return NULL;
    }
    switch(genocideMethod) {
        case GA_GENO_NONE:
            geneticAlgorithm->genocidedSubstitutionFunction = NULL;
            geneticAlgorithm->genocideStuckPeriod = -1;
            break;
        case GA_GENO_KEEPBEST:
            geneticAlgorithm->genocidedSubstitutionFunction = genocidedSubstituteKeepBest;
            geneticAlgorithm->genocideStuckPeriod = genocideStuckPeriod;
            break;
        case GA_GENO_ALL:
            geneticAlgorithm->genocidedSubstitutionFunction = genocidedSubstituteAll;
            geneticAlgorithm->genocideStuckPeriod = genocideStuckPeriod;
            break;
        default:
            geneticAlgorithm_erase(&geneticAlgorithm);
            return NULL;
    }
    switch(predationMethod) {
        case GA_PRED_NONE:
            geneticAlgorithm->predatedSubstitutionFunction = NULL;
            geneticAlgorithm->predationPeriod = -1;
            break;
        case GA_PRED_RANDOM:
            geneticAlgorithm->predatedSubstitutionFunction = predatedSubstituteRandom;
            geneticAlgorithm->predationPeriod = predationPeriod;
            break;
        case GA_PRED_SYNTHESIS:
            geneticAlgorithm->predatedSubstitutionFunction = predatedSubstituteSynthesis;
            geneticAlgorithm->predationPeriod = predationPeriod;
            break;
        default:
            geneticAlgorithm_erase(&geneticAlgorithm);
            return NULL;
    }

    geneticAlgorithm->isSexual = isSexual;
    geneticAlgorithm->hasInheritance = hasInheritance;

    geneticAlgorithm->generation = -1;
    geneticAlgorithm->population = NULL;
    geneticAlgorithm->fitnesses = NULL;
    geneticAlgorithm->bestChromosomeIndex = -1;
    geneticAlgorithm->generationsStuck = -1;
    geneticAlgorithm->mutationRate = -1;
    geneticAlgorithm->bestOfTheBest = NULL;
    geneticAlgorithm->bestOfTheBestFitness = -1;
    geneticAlgorithm->inheritances = NULL;
    geneticAlgorithm->bestFitnessHistory = NULL;
    geneticAlgorithm->meanFitnessHistory = NULL;

    geneticAlgorithm->populationType = populationType;
    geneticAlgorithm->populationTypeEvolvable = populationTypeEvolvable;
    return geneticAlgorithm;
}

boolean geneticAlgorithm_init(GA *geneticAlgorithm) {
    checkNullPointerError(geneticAlgorithm);
    if(isInitialized(geneticAlgorithm)) {
        resetState(geneticAlgorithm);
    }

    srand(time(NULL));

    geneticAlgorithm->generation = 0;

    geneticAlgorithm->population = (void **) calloc(geneticAlgorithm->populationSize, sizeof(void *));
    if(geneticAlgorithm->population == NULL) {
        resetState(geneticAlgorithm);
        return FALSE;
    } // Trata falha no calloc

    for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
        geneticAlgorithm->population[i] = initChromosomeRand(geneticAlgorithm->populationTypeEvolvable);
        if(geneticAlgorithm->population[i] == NULL) {
            resetState(geneticAlgorithm);
            return FALSE;
        } // Trata falha no malloc
    }

    geneticAlgorithm->fitnesses = (float *) malloc(geneticAlgorithm->populationSize*sizeof(float));
    if(geneticAlgorithm->fitnesses == NULL) {
        resetState(geneticAlgorithm);
        return FALSE;
    } // Trata falha no malloc
    updateFitnesses(geneticAlgorithm);

    resetStuck(geneticAlgorithm);

    if(geneticAlgorithm->hasInheritance) {
        geneticAlgorithm->inheritances = (float **) calloc(geneticAlgorithm->populationSize, sizeof(float *));
        if(geneticAlgorithm->inheritances == NULL) {
            resetState(geneticAlgorithm);
            return FALSE;
        } // Trata falha no calloc

        for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
            geneticAlgorithm->inheritances[i] = (float *) calloc(INHERITANCE_LENGTH, sizeof(float));
            if(geneticAlgorithm->inheritances[i] == NULL) {
                resetState(geneticAlgorithm);
                return FALSE;
            } // Trata falha no calloc
        }
    }

    geneticAlgorithm->bestFitnessHistory = (float *) malloc(1*sizeof(float));
    if(geneticAlgorithm->bestFitnessHistory == NULL) {
        resetState(geneticAlgorithm);
        return FALSE;
    } // Trata falha no malloc
    geneticAlgorithm->bestFitnessHistory[0] = geneticAlgorithm->fitnesses[geneticAlgorithm->bestChromosomeIndex];

    geneticAlgorithm->meanFitnessHistory = (float *) malloc(1*sizeof(float));
    if(geneticAlgorithm->meanFitnessHistory == NULL) {
        resetState(geneticAlgorithm);
        return FALSE;
    } // Trata falha no malloc
    geneticAlgorithm->meanFitnessHistory[0] = calcMeanFitness(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize);

    return TRUE;
}

boolean geneticAlgorithm_run(GA *geneticAlgorithm, const int numGenerations) {
    checkNullPointerError(geneticAlgorithm);
    if(!isInitialized(geneticAlgorithm)) {
        geneticAlgorithm_init(geneticAlgorithm);
    }

    geneticAlgorithm->bestFitnessHistory = (float *) realloc(geneticAlgorithm->bestFitnessHistory, (geneticAlgorithm->generation + numGenerations + 1)*sizeof(float));
    geneticAlgorithm->meanFitnessHistory = (float *) realloc(geneticAlgorithm->meanFitnessHistory, (geneticAlgorithm->generation + numGenerations + 1)*sizeof(float));

    for(int i=0 ; i<numGenerations ; i++) {
        if(!runGeneration(geneticAlgorithm)) {
            return FALSE;
        } // Trata falha no malloc
        
        geneticAlgorithm->generation++;
        geneticAlgorithm->bestFitnessHistory[geneticAlgorithm->generation] = getThisGenBestFitness(geneticAlgorithm, TRUE);
        geneticAlgorithm->meanFitnessHistory[geneticAlgorithm->generation] = calcMeanFitness(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize);
    }

    return TRUE;
}

int geneticAlgorithm_getNumGeneration(const GA *geneticAlgorithm) {
    checkNullPointerError(geneticAlgorithm);
    if(!isInitialized(geneticAlgorithm)) {
        return -1;
    }
    
    return geneticAlgorithm->generation;
}

void * geneticAlgorithm_getBestChromosome(const GA *geneticAlgorithm, float *out_bestFitness) {
    checkNullPointerError(geneticAlgorithm);
    if(!isInitialized(geneticAlgorithm)) {
        return NULL;
    }

    void *bestChromosomeCopy = NULL;
    if(geneticAlgorithm->bestOfTheBest == NULL) {
        bestChromosomeCopy = copyChromosome(geneticAlgorithm->population[geneticAlgorithm->bestChromosomeIndex], geneticAlgorithm->populationType);
        *out_bestFitness = geneticAlgorithm->fitnesses[geneticAlgorithm->bestChromosomeIndex];
    }
    else {
        bestChromosomeCopy = copyChromosome(geneticAlgorithm->bestOfTheBest, geneticAlgorithm->populationType);
        *out_bestFitness = geneticAlgorithm->bestOfTheBestFitness;
    }
    return bestChromosomeCopy;
}

void ** geneticAlgorithm_getPopulation(const GA *geneticAlgorithm, float **out_populationFitness) {
    checkNullPointerError(geneticAlgorithm);
    if(!isInitialized(geneticAlgorithm)) {
        return NULL;
    }

    *out_populationFitness = copyFitnessVec(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize);
    if(*out_populationFitness == NULL) {
        return NULL;
    } // Trata falha no malloc

    void **populationCopy = copyPopulation(geneticAlgorithm->population, geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
    return populationCopy;
}

float * geneticAlgorithm_getBestFitnessHistory(const GA *geneticAlgorithm) {
    checkNullPointerError(geneticAlgorithm);
    if(!isInitialized(geneticAlgorithm)) {
        return NULL;
    }

    float *bestFitnessHistoryCopy = copyFitnessVec(geneticAlgorithm->bestFitnessHistory, geneticAlgorithm->generation + 1);
    return bestFitnessHistoryCopy;
}

float * geneticAlgorithm_getMeanFitnessHistory(const GA *geneticAlgorithm) {
    checkNullPointerError(geneticAlgorithm);
    if(!isInitialized(geneticAlgorithm)) {
        return NULL;
    }

    float *meanFitnessHistoryCopy = copyFitnessVec(geneticAlgorithm->meanFitnessHistory, geneticAlgorithm->generation + 1);
    return meanFitnessHistoryCopy;
}

void geneticAlgorithm_erase(GA **geneticAlgorithm_addr) {
    if(*geneticAlgorithm_addr != NULL) {
        resetState(*geneticAlgorithm_addr);
        free(*geneticAlgorithm_addr);
        *geneticAlgorithm_addr = NULL;
    }
}



static void selectElitism(GA *geneticAlgorithm, int currentIndex, int *out_parent1Index, int *out_parent2Index) {
    *out_parent1Index = currentIndex;
    *out_parent2Index = geneticAlgorithm->bestChromosomeIndex;
}

static void select2WayTournament(GA *geneticAlgorithm, int currentIndex, int *out_parent1Index, int *out_parent2Index) {
    int *out_parents[2] = { out_parent1Index, out_parent2Index };
    for(int i=0 ; i<2 ; i++) {
        int candidate1 = rand() % geneticAlgorithm->populationSize;
        int candidate2 = rand() % geneticAlgorithm->populationSize;
        float fitness1 = geneticAlgorithm->fitnesses[candidate1];
        float fitness2 = geneticAlgorithm->fitnesses[candidate2];

        *(out_parents[i]) = (fitness1 > fitness2) ? candidate1 : candidate2;
        if(i == 1 && *(out_parents[0]) == *(out_parents[1])) {
            i--;
        }
    }
}

static void selectRouletteWheel(GA *geneticAlgorithm, int currentIndex, int *out_parent1Index, int *out_parent2Index) {
    float maxFitness = getThisGenBestFitness(geneticAlgorithm, FALSE);
    float minFitness = getThisGenWorstFitness(geneticAlgorithm);
    float offsetFitness = (maxFitness - minFitness) / (ROULETTE_MAX_RATIO - 1);
    float meanFitness = calcMeanFitness(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize);
    float normalizedFitnessSum = (meanFitness - minFitness + offsetFitness) * geneticAlgorithm->populationSize;
    
    int *out_parents[2] = { out_parent1Index, out_parent2Index };
    for(int i=0 ; i<2 ; i++) {
        int candidate = -1;
        if(normalizedFitnessSum == 0) {
            candidate = rand() % geneticAlgorithm->populationSize;
        }
        else {
            float roulette = (float)rand() / (float)RAND_MAX;
            while(roulette > 0) {
                candidate++;
                roulette -= (geneticAlgorithm->fitnesses[candidate] - minFitness + offsetFitness) / normalizedFitnessSum;
            }
            candidate = max(candidate, 0);
        }

        *(out_parents[i]) = candidate;
        if(i == 1 && *(out_parents[0]) == *(out_parents[1])) {
            i--;
        }
    }
}

static void ** genocidedSubstituteKeepBest(GA *geneticAlgorithm) {
    void **populationSubstitute = (void **) calloc(geneticAlgorithm->populationSize, sizeof(void *));
    if(populationSubstitute == NULL) {
        return NULL;
    } // Trata falha no calloc

    for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
        if(shouldProtectIndex(geneticAlgorithm, i)) {
            populationSubstitute[i] = copyChromosome(geneticAlgorithm->population[i], geneticAlgorithm->populationType);
        }
        else {
            populationSubstitute[i] = initChromosomeRand(geneticAlgorithm->populationTypeEvolvable);
        }

        if(populationSubstitute[i] == NULL) {
            erasePopulation(&populationSubstitute, geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
            return NULL;
        } // Trata falha no malloc
    }
    return populationSubstitute;
}

static void ** genocidedSubstituteAll(GA *geneticAlgorithm) {
    void **populationSubstitute = (void **) calloc(geneticAlgorithm->populationSize, sizeof(void *));
    if(populationSubstitute == NULL) {
        return NULL;
    } // Trata falha no calloc

    for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
        populationSubstitute[i] = initChromosomeRand(geneticAlgorithm->populationTypeEvolvable);
        if(populationSubstitute[i] == NULL) {
            erasePopulation(&populationSubstitute, geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
            return NULL;
        } // Trata falha no malloc
    }

    if(geneticAlgorithm->bestOfTheBest == NULL) {
        geneticAlgorithm->bestOfTheBest = copyChromosome(geneticAlgorithm->population[geneticAlgorithm->bestChromosomeIndex], geneticAlgorithm->populationType);
        if(geneticAlgorithm->bestOfTheBest == NULL) {
            erasePopulation(&populationSubstitute, geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
            return NULL;
        } // Trata falha no malloc
        geneticAlgorithm->bestOfTheBestFitness = geneticAlgorithm->fitnesses[geneticAlgorithm->bestChromosomeIndex];
    }
    return populationSubstitute;
}

static void * predatedSubstituteRandom(GA *geneticAlgorithm) {
    return initChromosomeRand(geneticAlgorithm->populationTypeEvolvable);
}

static void * predatedSubstituteSynthesis(GA *geneticAlgorithm) {
    return initChromosomeSynthesis(geneticAlgorithm->population, geneticAlgorithm->populationSize, geneticAlgorithm->populationTypeEvolvable);
}



static boolean runGeneration(GA *geneticAlgorithm) {
    if(geneticAlgorithm->generation > 0) {
        if(!applyExternalAgents(geneticAlgorithm)) {
            return FALSE;
        } // Trata falha no malloc
    }

    if(!evolvePopulation(geneticAlgorithm)) {
        return FALSE;
    } // Trata falha no malloc

    if(geneticAlgorithm->hasInheritance) updateInheritances(geneticAlgorithm);
    updateFitnesses(geneticAlgorithm);
    if(geneticAlgorithm->bestOfTheBest != NULL) updateBestOfTheBest(geneticAlgorithm);

    return TRUE;
}

static boolean evolvePopulation(GA *geneticAlgorithm) {
    void **newPopulation = (void **) calloc(geneticAlgorithm->populationSize, sizeof(void *));
    if(newPopulation == NULL) {
        return FALSE;
    } // Trata falha no calloc

    for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
        if(shouldProtectIndex(geneticAlgorithm, i)) {
            newPopulation[i] = copyChromosome(geneticAlgorithm->population[i], geneticAlgorithm->populationType);
        }
        else {
            int parent1 = -1, parent2 = -1;
            geneticAlgorithm->selectionFunction(geneticAlgorithm, i, &parent1, &parent2);

            if(geneticAlgorithm->isSexual) {
                newPopulation[i] = crossover(geneticAlgorithm->population[parent1], geneticAlgorithm->population[parent2], geneticAlgorithm->populationTypeEvolvable);
            }
            else {
                float fitness1 = geneticAlgorithm->fitnesses[parent1];
                float fitness2 = geneticAlgorithm->fitnesses[parent2];
                int candidate = (fitness1 > fitness2) ? parent1 : parent2;
                newPopulation[i] = copyChromosome(geneticAlgorithm->population[candidate], geneticAlgorithm->populationType);
            }

            float mutation = calcMutation(geneticAlgorithm->mutationRate);
            mutate(newPopulation[i], mutation, geneticAlgorithm->populationTypeEvolvable);
        }

        if(newPopulation[i] == NULL) {
            erasePopulation(&newPopulation, geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
            return FALSE;
        } // Trata falha no malloc
    }

    erasePopulation(&(geneticAlgorithm->population), geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
    geneticAlgorithm->population = newPopulation;
    return TRUE;
}

static boolean applyExternalAgents(GA *geneticAlgorithm) {
    if(isStuck(geneticAlgorithm)) {
        geneticAlgorithm->generationsStuck++;
        if(shouldGenocide(geneticAlgorithm)) {
            if(!performGenocide(geneticAlgorithm)) {
                return FALSE;
            } // Trata falha no malloc

            resetStuck(geneticAlgorithm);
            if(geneticAlgorithm->hasInheritance) resetInheritances(geneticAlgorithm);
            updateFitnesses(geneticAlgorithm);
        }
        else if(shouldAdaptMutation(geneticAlgorithm)) {
            if(!adaptMutation(geneticAlgorithm)) {
                return FALSE;
            } // Trata falha no malloc
        }
    }
    else {
        resetStuck(geneticAlgorithm);
    }

    if(shouldPredate(geneticAlgorithm)) {
        if(!performPredation(geneticAlgorithm)) {
            return FALSE;
        } // Trata falha no malloc
        
        updateFitnesses(geneticAlgorithm);
    }

    return TRUE;
}

static boolean adaptMutation(GA *geneticAlgorithm) {
    int period = geneticAlgorithm->generationsStuck / geneticAlgorithm->mutationAdaptationStuckPeriod;
    if(period <= PERIODS_TRY_REDUCE_MUTATION) {
        geneticAlgorithm->mutationRate /= geneticAlgorithm->mutationMultiplier;
    }
    else if(period == PERIODS_TRY_REDUCE_MUTATION + 1) {
        geneticAlgorithm->mutationRate = geneticAlgorithm->mutationBase * geneticAlgorithm->mutationMultiplier;
    }
    else {
        geneticAlgorithm->mutationRate *= geneticAlgorithm->mutationMultiplier;
    }
    return TRUE;
}

static boolean performGenocide(GA *geneticAlgorithm) {
    void **newPopulation = geneticAlgorithm->genocidedSubstitutionFunction(geneticAlgorithm);
    if(newPopulation == NULL) {
        return FALSE;
    } // Trata falha no malloc

    erasePopulation(&(geneticAlgorithm->population), geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
    geneticAlgorithm->population = newPopulation;
    return TRUE;
}

static boolean performPredation(GA *geneticAlgorithm) {
    int worst = findWorstChromosomeIndex(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize, NULL);
    if(!shouldProtectIndex(geneticAlgorithm, worst)) {
        void *newChromosome = geneticAlgorithm->predatedSubstitutionFunction(geneticAlgorithm);
        if(newChromosome == NULL) {
            return FALSE;
        } // Trata falha no malloc

        eraseChromosome(&(geneticAlgorithm->population[worst]), geneticAlgorithm->populationType);
        geneticAlgorithm->population[worst] = newChromosome;
    }
    return TRUE;
}



static void updateFitnesses(GA *geneticAlgorithm) {
    evaluatePopulation(geneticAlgorithm->population, geneticAlgorithm->populationSize, geneticAlgorithm->fitnesses, geneticAlgorithm->populationTypeEvolvable);
    geneticAlgorithm->bestChromosomeIndex = findBestChromosomeIndex(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize, geneticAlgorithm->inheritances);
}

static void updateBestOfTheBest(GA *geneticAlgorithm) {
    void *bestBackup = geneticAlgorithm->population[geneticAlgorithm->bestChromosomeIndex];
    geneticAlgorithm->population[geneticAlgorithm->bestChromosomeIndex] = geneticAlgorithm->bestOfTheBest;

    float *fitnessesWithBob = (float *) malloc(geneticAlgorithm->populationSize*sizeof(float)); // rezar para nao dar errado
    evaluatePopulation(geneticAlgorithm->population, geneticAlgorithm->populationSize, fitnessesWithBob, geneticAlgorithm->populationTypeEvolvable);

    geneticAlgorithm->population[geneticAlgorithm->bestChromosomeIndex] = bestBackup;

    float bestFitness = geneticAlgorithm->fitnesses[geneticAlgorithm->bestChromosomeIndex];
    float bobFitness = fitnessesWithBob[geneticAlgorithm->bestChromosomeIndex];
    if(bestFitness > bobFitness) {
        eraseChromosome(&(geneticAlgorithm->bestOfTheBest), geneticAlgorithm->populationType);
        geneticAlgorithm->bestOfTheBestFitness = -1;
    }
    else {
        geneticAlgorithm->bestOfTheBestFitness = bobFitness;
    }
}

static void updateInheritances(GA *geneticAlgorithm) {
    int genIndex = geneticAlgorithm->generation % INHERITANCE_LENGTH;
    for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
        geneticAlgorithm->inheritances[i][genIndex] = geneticAlgorithm->fitnesses[i];
    }
}

static float getThisGenBestFitness(GA *geneticAlgorithm, boolean considerBestOfTheBest) {
    int genBestIndex = -1;
    if(geneticAlgorithm->hasInheritance) {
        genBestIndex = findBestChromosomeIndex(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize, NULL);
    }
    else {
        genBestIndex = geneticAlgorithm->bestChromosomeIndex;
    }

    float bestFitness = geneticAlgorithm->fitnesses[genBestIndex];
    if(considerBestOfTheBest && geneticAlgorithm->bestOfTheBest != NULL) {
        float bobFitness = geneticAlgorithm->bestOfTheBestFitness;
        bestFitness = max(bestFitness, bobFitness);
    }
    return bestFitness;
}

static float getThisGenWorstFitness(GA *geneticAlgorithm) {
    int genWorstIndex = findWorstChromosomeIndex(geneticAlgorithm->fitnesses, geneticAlgorithm->populationSize, NULL);
    float worstFitness = geneticAlgorithm->fitnesses[genWorstIndex];
    return worstFitness;
}



static boolean isInitialized(GA *geneticAlgorithm) {
    return geneticAlgorithm->generation >= 0;
}

static boolean isStuck(GA *geneticAlgorithm) {
    return fabs(geneticAlgorithm->bestFitnessHistory[geneticAlgorithm->generation] - geneticAlgorithm->bestFitnessHistory[geneticAlgorithm->generation - 1]) < STUCK_THRESHOLD;
}

static boolean shouldProtectIndex(GA *geneticAlgorithm, int index) {
    return index == geneticAlgorithm->bestChromosomeIndex || geneticAlgorithm->fitnesses[index] > geneticAlgorithm->fitnesses[geneticAlgorithm->bestChromosomeIndex];
}

static boolean shouldAdaptMutation(GA *geneticAlgorithm) {
    return geneticAlgorithm->mutationAdaptationStuckPeriod > 0 && geneticAlgorithm->generationsStuck % geneticAlgorithm->mutationAdaptationStuckPeriod == 0;
}

static boolean shouldGenocide(GA *geneticAlgorithm) {
    return geneticAlgorithm->genocideStuckPeriod > 0 && geneticAlgorithm->generationsStuck >= geneticAlgorithm->genocideStuckPeriod;
}

static boolean shouldPredate(GA *geneticAlgorithm) {
    return geneticAlgorithm->predationPeriod > 0 && geneticAlgorithm->generation % geneticAlgorithm->predationPeriod == 0;
}



static void resetState(GA *geneticAlgorithm) {
    geneticAlgorithm->generation = -1;
    erasePopulation(&(geneticAlgorithm->population), geneticAlgorithm->populationSize, geneticAlgorithm->populationType);
    eraseFitnessVec(&(geneticAlgorithm->fitnesses));
    geneticAlgorithm->bestChromosomeIndex = -1;
    geneticAlgorithm->generationsStuck = -1;
    geneticAlgorithm->mutationRate = -1;
    eraseChromosome(&(geneticAlgorithm->bestOfTheBest), geneticAlgorithm->populationType);
    geneticAlgorithm->bestOfTheBestFitness = -1;
    eraseFitnessMat(&(geneticAlgorithm->inheritances), geneticAlgorithm->populationSize);
    eraseFitnessVec(&(geneticAlgorithm->bestFitnessHistory));
    eraseFitnessVec(&(geneticAlgorithm->meanFitnessHistory));
}

static void resetStuck(GA *geneticAlgorithm) {
    geneticAlgorithm->generationsStuck = 0;
    geneticAlgorithm->mutationRate = geneticAlgorithm->mutationBase;
}

static void resetInheritances(GA *geneticAlgorithm) {
    for(int i=0 ; i<geneticAlgorithm->populationSize ; i++) {
        for(int j=0 ; j<INHERITANCE_LENGTH ; j++) {
            geneticAlgorithm->inheritances[i][j] = 0;
        }
    }
}



static int findBestChromosomeIndex(float *fitnesses, int populationSize, float **inheritances) {
    int best = -1;
    float bestFitness = -INFINITY;
    for(int i=0 ; i<populationSize ; i++) {
        float thisFitness = -1;
        if(inheritances == NULL) {
            thisFitness = fitnesses[i];
        }
        else {
            thisFitness = (calcInheritedFitnessSum(inheritances, i) + fitnesses[i]) / (INHERITANCE_LENGTH + 1);
        }

        if(thisFitness > bestFitness) {
            best = i;
            bestFitness = thisFitness;
        }
    }
    return best;
}

static int findWorstChromosomeIndex(float *fitnesses, int populationSize, float **inheritances) {
    int worst = -1;
    float worstFitness = INFINITY;
    for(int i=0 ; i<populationSize ; i++) {
        float thisFitness = -1;
        if(inheritances == NULL) {
            thisFitness = fitnesses[i];
        }
        else {
            thisFitness = (calcInheritedFitnessSum(inheritances, i) + fitnesses[i]) / (INHERITANCE_LENGTH + 1);
        }

        if(thisFitness <= worstFitness) {
            worst = i;
            worstFitness = thisFitness;
        }
    }
    return worst;
}

static float calcMeanFitness(float *fitnesses, int populationSize) {
    float sum = 0;
    for(int i=0 ; i<populationSize ; i++) {
        sum += fitnesses[i];
    }
    return sum / populationSize;
}

static float calcInheritedFitnessSum(float **inheritances, int chromosomeIndex) {
    float sum = 0;
    for(int i=0 ; i<INHERITANCE_LENGTH ; i++) {
        sum += inheritances[chromosomeIndex][i];
    }
    return sum;
}

static float calcMutation(float mutationRate) {
    float random = (float)rand() / (float)RAND_MAX;
    return (random - 0.5) * 2 * min(mutationRate, MUTATION_RATE_LIMIT);
}



static void ** copyPopulation(void **population, int populationSize, T *populationType) {
    void **populationCopy = (void **) calloc(populationSize, sizeof(void *));
    if(populationCopy == NULL) {
        return NULL;
    } // Trata falha no calloc

    for(int i=0 ; i<populationSize ; i++) {
        populationCopy[i] = copyChromosome(population[i], populationType);
        if(populationCopy[i] == NULL) {
            erasePopulation(&populationCopy, populationSize, populationType);
            return NULL;
        } // Trata falha no malloc
    }
    return populationCopy;
}

static void erasePopulation(void ***population_addr, int populationSize, T *populationType) {
    if(*population_addr != NULL) {
        for(int i=0 ; i<populationSize ; i++) {
            eraseChromosome(&((*population_addr)[i]), populationType);
        }
        free(*population_addr);
        *population_addr = NULL;
    }
}

static float * copyFitnessVec(float *fitnessVec, int vecSize) {
    float *fitnessVecCopy = (float *) malloc(vecSize*sizeof(float));
    if(fitnessVecCopy == NULL) {
        return NULL;
    } // Trata falha no malloc

    for(int i=0 ; i<vecSize ; i++) {
        fitnessVecCopy[i] = fitnessVec[i];
    }
    return fitnessVecCopy;
}

static void eraseFitnessVec(float **fitnessVec_addr) {
    if(*fitnessVec_addr != NULL) {
        free(*fitnessVec_addr);
        *fitnessVec_addr = NULL;
    }
}

static void eraseFitnessMat(float ***fitnessMat_addr, int matRows) {
    if(*fitnessMat_addr != NULL) {
        for(int i=0 ; i<matRows ; i++) {
            eraseFitnessVec(&((*fitnessMat_addr)[i]));
        }
        free(*fitnessMat_addr);
        *fitnessMat_addr = NULL;
    }
}