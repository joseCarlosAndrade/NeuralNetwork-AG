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

void bytes_copy(byte *out_destination, const byte *source, size_t size) {
    if(out_destination == NULL || source == NULL || size <= 0) return;

	for(size_t i = 0; i < size; i++) {
		out_destination[i] = source[i];
	}
}

void bytes_free(byte **bytes_addr) {
	if(*bytes_addr != NULL) {
		free(*bytes_addr);
		*bytes_addr = NULL;
	}
}

void checkNullPointerError(const void *pointer) {
    if(pointer == NULL) {
        exit(1);
    }
}