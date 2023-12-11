#ifndef FUNCAOESCROTA_H
#define FUNCAOESCROTA_H

#include "util.h"
#include "type.h"
#include "typeEvolvable.h"

typedef struct funcaoEscrota_st FUNCAOESCROTA;

T * funcaoEscrota_getType();
T_EVOLVABLE * funcaoEscrota_getTypeEvolvable();

FUNCAOESCROTA * funcaoEscrota_create(const float x);
float funcaoEscrota_getX(const FUNCAOESCROTA *funcaoEscrota);
void funcaoEscrota_erase(FUNCAOESCROTA **funcaoEscrota_addr);

#endif //FUNCAOESCROTA_H