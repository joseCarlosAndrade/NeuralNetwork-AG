#include "../include/typeEvolvable.h"

struct typeEvolvable_st {
    InitFunction initFunction;
    EvaluateFunction evaluateFunction;
    CrossoverFunction crossoverFunction;
    MutateFunction mutateFunction;
};



T_EVOL * typeEvolvable_create(const InitFunction initFunction, const EvaluateFunction evaluateFunction, const CrossoverFunction crossoverFunction, const MutateFunction mutateFunction) {
    T_EVOL *typeEvolvable = (T_EVOL *) malloc(1*sizeof(T_EVOL));
    if(typeEvolvable == NULL) {
        return NULL;
    } // Trata falha no malloc

    typeEvolvable->initFunction = initFunction;
    typeEvolvable->evaluateFunction = evaluateFunction;
    typeEvolvable->crossoverFunction = crossoverFunction;
    typeEvolvable->mutateFunction = mutateFunction;
    return typeEvolvable;
}

InitFunction typeEvolvable_getInitFunction(const T_EVOL *typeEvolvable) {
    checkNullPointerError(typeEvolvable);
    return typeEvolvable->initFunction;
}

EvaluateFunction typeEvolvable_getEvaluateFunction(const T_EVOL *typeEvolvable) {
    checkNullPointerError(typeEvolvable);
    return typeEvolvable->evaluateFunction;
}

CrossoverFunction typeEvolvable_getCrossoverFunction(const T_EVOL *typeEvolvable) {
    checkNullPointerError(typeEvolvable);
    return typeEvolvable->crossoverFunction;
}

MutateFunction typeEvolvable_getMutateFunction(const T_EVOL *typeEvolvable) {
    checkNullPointerError(typeEvolvable);
    return typeEvolvable->mutateFunction;
}

void typeEvolvable_erase(T_EVOL **typeEvolvable_addr) {
    if(*typeEvolvable_addr != NULL) {
        free(*typeEvolvable_addr);
        *typeEvolvable_addr = NULL;
    }
}