#ifndef INPUT_H
#define INPUT_H

#include "util.h"

// Funcoes que facilitam operacoes de input

void input_stringWord(char **out_string);
void input_stringWholeLine(char **out_string);
void input_stringUntilSeparator(char **out_string, const char separator);
void input_char(char *out_char);
void input_int(int *out_int);
void input_float(float *out_float);

#endif //INPUT_H