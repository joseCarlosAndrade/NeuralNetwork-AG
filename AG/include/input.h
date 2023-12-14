#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

// Funcoes que facilitam operacoes de input

void input_stringWord(char **out_string);
void input_stringWholeLine(char **out_string);
void input_stringUntilSeparator(char **out_string, const char separator);
void input_char(char *out_char);
void input_int(int *out_int);
void input_float(float *out_float);

#ifdef __cplusplus
}
#endif

#endif //INPUT_H