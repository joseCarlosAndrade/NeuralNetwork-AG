#ifndef TYPEEVOLVABLE_H
#define TYPEEVOLVABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

// -> TypeEvolvable eh um TAD que carrega informacoes importantes sobre um outro TAD
// -> guarda funcoes especificas para a utilizacao em algoritmos evolutivos
// -> serve para que possamos criar uma Estrutura de Dados generica passando T_EVOLVABLE como argumento na
// sua criacao, para que a Estrutura saiba como lidar com os dados que recebe

typedef struct typeEvolvable_st T_EVOLVABLE;

typedef void * (*InitFunction)(void **, const int); // Modelo de ponteiro de funcao que inicializa um objeto desse TAD, usando uma lista (e seu tamanho) de outros objetos como argumento (para sintese, por exemplo), ou de forma aleatoria se arg = null
typedef void (*EvaluateFunction)(void **, const int, float *); // Modelo de ponteiro de funcao que avalia toda a lista de objetos desse TAD e salva os fitnesses no vetor fornecido
typedef void * (*CrossoverFunction)(const void *, const void *); // Modelo de ponteiro de funcao que gera um novo objeto desse TAD a partir de dois outros objetos
typedef void (*MutateFunction)(void *, const float); // Modelo de ponteiro de funcao que aplica mutacao em um objeto desse TAD

T_EVOLVABLE * typeEvolvable_create(const InitFunction initFunction, const EvaluateFunction evaluateFunction, const CrossoverFunction crossoverFunction, const MutateFunction mutateFunction);
InitFunction typeEvolvable_getInitFunction(const T_EVOLVABLE *typeEvolvable);
EvaluateFunction typeEvolvable_getEvaluateFunction(const T_EVOLVABLE *typeEvolvable);
CrossoverFunction typeEvolvable_getCrossoverFunction(const T_EVOLVABLE *typeEvolvable);
MutateFunction typeEvolvable_getMutateFunction(const T_EVOLVABLE *typeEvolvable);
void typeEvolvable_erase(T_EVOLVABLE **typeEvolvable_addr);

#ifdef __cplusplus
}
#endif

#endif //TYPEEVOLVABLE_H