#ifndef TYPE_H
#define TYPE_H

#include "util.h"

// -> Type eh um TAD que carrega informacoes importantes sobre um outro TAD
// -> serve para que possamos criar uma Estrutura de Dados generica passando T como argumento na
// sua criacao, para que a Estrutura saiba como lidar com os dados que recebe

typedef struct type_st T;

typedef void * (*CopyFunction)(const void *); // Modelo de ponteiro de funcao que copia os dados de um objeto desse TAD
typedef comparison (*CompareFunction)(const void *, const void *); // Modelo de ponteiro de funcao que compara dois objetos desse TAD
typedef void (*PrintFunction)(const void *); // Modelo de ponteiro de funcao que imprime os dados de um objeto desse TAD
typedef void (*EraseFunction)(void **); // Modelo de ponteiro de funcao que limpa os dados de um objeto desse TAD

T * type_create(const size_t size, const CopyFunction copyFunction, const CompareFunction compareFunction, const PrintFunction printFunction, const EraseFunction eraseFunction);
size_t type_getSize(const T *type);
CopyFunction type_getCopyFunction(const T *type);
CompareFunction type_getCompareFunction(const T *type);
PrintFunction type_getPrintFunction(const T *type);
EraseFunction type_getEraseFunction(const T *type);
void type_erase(T **type_addr);

#endif //TYPE_H