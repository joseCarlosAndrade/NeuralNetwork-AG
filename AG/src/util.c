#include "../include/util.h"

char * string_copy(const char *string) {
    char *stringCopy = NULL;
    if(string != NULL)  {
        stringCopy = (char *) calloc(strlen(string) + 1, sizeof(char));
        strcpy(stringCopy, string);
    }
    return stringCopy;
}

void string_free(char **string_addr) {
    if(*string_addr != NULL) {
        free(*string_addr);
        *string_addr = NULL;
    }
}

void checkNullPointerError(const void *pointer) {
    if(pointer == NULL) {
        exit(1);
    }
}