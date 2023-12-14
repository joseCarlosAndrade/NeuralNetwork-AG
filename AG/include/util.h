#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//------------BOOLEAN---------------
typedef enum {
    FALSE = 0,
    TRUE = 1
} boolean;
//----------------------------------


//-----------COMPARISON-------------
typedef enum {
    LOWER = -1,
    EQUAL = 0,
    GREATER = 1
} comparison;
//----------------------------------


//------------------------STRING HANDLING-------------------------
// Funcoes que facilitam operacoes com string

char * string_copy(const char *string);
void string_free(char **string_addr);
//----------------------------------------------------------------


//-------------------------BYTES HANDLING-------------------------
// Funcoes que facilitam operacoes com bytes
typedef char byte;

void bytes_copy(byte *out_destination, const byte *source, size_t size);
void bytes_free(byte **bytes_addr);
//----------------------------------------------------------------


//-------------------CHECK NULL POINTER ERROR---------------------
// Funcao que checa se o ponteiro passado eh nulo, e finaliza o programa se for

void checkNullPointerError(const void *pointer);
//----------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif //UTIL_H