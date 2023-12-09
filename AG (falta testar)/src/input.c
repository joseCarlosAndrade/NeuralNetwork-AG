#include "../include/input.h"

static void consumeExtraChar();



void input_stringWord(char **out_string) {
    string_free(out_string);
    int stringSize = 0;

    char thisChar;
    do {
        thisChar = (char) getchar();
        stringSize++;
        *out_string = (char *) realloc(*out_string, sizeof(char)*stringSize);
        (*out_string)[stringSize - 1] = thisChar;
        if(thisChar == '\r') {
            thisChar = (char) getchar();
        }
    } while(thisChar != ' ' && thisChar != '\n' && thisChar != EOF);
    (*out_string)[stringSize - 1] = '\0';
}

void input_stringWholeLine(char **out_string) {
    input_stringUntilSeparator(out_string, '\n');
}

void input_stringUntilSeparator(char **out_string, const char separator) {
    string_free(out_string);
    int stringSize = 0;

    char thisChar;
    do {
        thisChar = (char) getchar();
        stringSize++;
        *out_string = (char *) realloc(*out_string, sizeof(char)*stringSize);
        (*out_string)[stringSize - 1] = thisChar;
        if(separator == '\n' && thisChar == '\r') {
            thisChar = (char) getchar();
        }
    } while(thisChar != separator && thisChar != EOF);
    (*out_string)[stringSize - 1] = '\0';
}

void input_char(char *out_char) {
    scanf("%c", out_char);
    consumeExtraChar();
}

void input_int(int *out_int) {
    scanf("%d", out_int);
    consumeExtraChar();
}

void input_float(float *out_float) {
    scanf("%f", out_float);
    consumeExtraChar();
}



static void consumeExtraChar() {
    char extraChar;
    extraChar = (char) getchar();
    if(extraChar == '\r') {
        getchar();
    }
}