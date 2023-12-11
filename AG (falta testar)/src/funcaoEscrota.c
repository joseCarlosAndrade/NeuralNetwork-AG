#include "../include/funcaoEscrota.h"

struct funcaoEscrota_st {
    float x;
};



static float function(const float x);

static void * funcaoEscrotaCopyFunction(const void *data);
static comparison funcaoEscrotaCompareFunction(const void *data1, const void *data2); // nao precisa
static void funcaoEscrotaPrintFunction(const void *data); // nao precisa
static void funcaoEscrotaEraseFunction(void **data_addr);

static void * funcaoEscrotaInitFunction(void **dataVec, const int vecSize);
static void funcaoEscrotaEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses);
static void * funcaoEscrotaCrossoverFunction(const void *data1, const void *data2);
static void funcaoEscrotaMutateFunction(void *data, const float mutation);



#define X_MAX 50
#define X_MIN -50

T * funcaoEscrota_getType() {
    T *funcaoEscrotaType = type_create(sizeof(FUNCAOESCROTA), funcaoEscrotaCopyFunction, funcaoEscrotaCompareFunction, funcaoEscrotaPrintFunction, funcaoEscrotaEraseFunction);
    return funcaoEscrotaType;
}

T_EVOLVABLE * funcaoEscrota_getTypeEvolvable() {
    T_EVOLVABLE *funcaoEscrotaTypeEvolvable = typeEvolvable_create(funcaoEscrotaInitFunction, funcaoEscrotaEvaluateFunction, funcaoEscrotaCrossoverFunction, funcaoEscrotaMutateFunction);
    return funcaoEscrotaTypeEvolvable;
}

FUNCAOESCROTA * funcaoEscrota_create(const float x) {
    if(x < X_MIN || x > X_MAX) {
        return NULL;
    }

    FUNCAOESCROTA *funcaoEscrota = (FUNCAOESCROTA *) malloc(1*sizeof(FUNCAOESCROTA));
    if(funcaoEscrota == NULL) {
        return NULL;
    } // Trata falha no malloc

    funcaoEscrota->x = x;
    return funcaoEscrota;
}

float funcaoEscrota_getX(const FUNCAOESCROTA *funcaoEscrota) {
    checkNullPointerError(funcaoEscrota);
    return funcaoEscrota->x;
}

void funcaoEscrota_erase(FUNCAOESCROTA **funcaoEscrota_addr) {
    if(*funcaoEscrota_addr != NULL) {
        free(*funcaoEscrota_addr);
        *funcaoEscrota_addr = NULL;
    }
}



static float function(const float x) {
    return -0.01*pow(x-5, 2) + 3 + 2*sin(2*x) + 0.5*cos(11*x);
}



static void * funcaoEscrotaCopyFunction(const void *data) {
    if(data == NULL) {
        return NULL;
    }
    FUNCAOESCROTA *funcaoEscrota = (FUNCAOESCROTA *) data;
    FUNCAOESCROTA *funcaoEscrotaCopy = funcaoEscrota_create(funcaoEscrota->x);
    return funcaoEscrotaCopy;
}

static comparison funcaoEscrotaCompareFunction(const void *data1, const void *data2) {
    FUNCAOESCROTA *funcaoEscrota1 = (FUNCAOESCROTA *) data1;
    FUNCAOESCROTA *funcaoEscrota2 = (FUNCAOESCROTA *) data2;
    float result = function(funcaoEscrota1->x) - function(funcaoEscrota2->x);
    if(result == 0) {
        return EQUAL;
    }
    else if(result < 0) {
        return LOWER;
    }
    else {
        return GREATER;
    }
}

static void funcaoEscrotaPrintFunction(const void *data) {
    FUNCAOESCROTA *funcaoEscrota = (FUNCAOESCROTA *) data;
    printf("(%.2f, %.2f)", funcaoEscrota->x, function(funcaoEscrota->x));
}

static void funcaoEscrotaEraseFunction(void **data_addr) {
    funcaoEscrota_erase((FUNCAOESCROTA **) data_addr);
}

static void * funcaoEscrotaInitFunction(void **dataVec, const int vecSize) {
    float x = -1;
    if(dataVec == NULL) {
        float random = (float)rand() / (float)RAND_MAX;
        x = random * (X_MAX - X_MIN) + X_MIN;
    }
    else {
        float sum = 0;
        for(int i=0 ; i<vecSize ; i++) {
            FUNCAOESCROTA *funcaoEscrota = (FUNCAOESCROTA *) dataVec[i];
            sum += funcaoEscrota->x;
        }
        x = sum / vecSize;
    }

    FUNCAOESCROTA *funcaoEscrotaNew = funcaoEscrota_create(x);
    return funcaoEscrotaNew;
}

static void funcaoEscrotaEvaluateFunction(void **dataVec, const int vecSize, float *out_fitnesses) {
    for(int i=0 ; i<vecSize ; i++) {
        FUNCAOESCROTA *funcaoEscrota = (FUNCAOESCROTA *) dataVec[i];
        out_fitnesses[i] = function(funcaoEscrota->x);
    }
}

static void * funcaoEscrotaCrossoverFunction(const void *data1, const void *data2) {
    FUNCAOESCROTA *funcaoEscrota1 = (FUNCAOESCROTA *) data1;
    FUNCAOESCROTA *funcaoEscrota2 = (FUNCAOESCROTA *) data2;
    float x = (funcaoEscrota1->x + funcaoEscrota2->x) / 2;

    FUNCAOESCROTA *funcaoEscrotaNew = funcaoEscrota_create(x);
    return funcaoEscrotaNew;
}

static void funcaoEscrotaMutateFunction(void *data, const float mutation) {
    if(data == NULL) {
        return;
    }
    FUNCAOESCROTA *funcaoEscrota = (FUNCAOESCROTA *) data;
    funcaoEscrota->x += mutation * (X_MAX - X_MIN);
    funcaoEscrota->x = fmin(fmax(funcaoEscrota->x, X_MIN), X_MAX);
}