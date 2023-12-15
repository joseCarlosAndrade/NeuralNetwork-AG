#include "../include/type.h"

struct type_st {
    size_t size;
    CopyFunction copyFunction;
    CompareFunction compareFunction;
    PrintFunction printFunction;
    EraseFunction eraseFunction;
};



T * type_create(const size_t size, const CopyFunction copyFunction, const CompareFunction compareFunction, const PrintFunction printFunction, const EraseFunction eraseFunction) {
    T *type = (T *) malloc(1*sizeof(T));
    if(type == NULL) {
        return NULL;
    } // Trata falha no malloc

    type->size = size;
    type->copyFunction = copyFunction;
    type->compareFunction = compareFunction;
    type->printFunction = printFunction;
    type->eraseFunction = eraseFunction;
    return type;
}

size_t type_getSize(const T *type) {
    checkNullPointerError(type);
    return type->size;
}

CopyFunction type_getCopyFunction(const T *type) {
    checkNullPointerError(type);
    return type->copyFunction;
}

CompareFunction type_getCompareFunction(const T *type) {
    checkNullPointerError(type);
    return type->compareFunction;
}

PrintFunction type_getPrintFunction(const T *type) {
    checkNullPointerError(type);
    return type->printFunction;
}

EraseFunction type_getEraseFunction(const T *type) {
    checkNullPointerError(type);
    return type->eraseFunction;
}

void type_erase(T **type_addr) {
    if(*type_addr != NULL) {
        free(*type_addr);
        *type_addr = NULL;
    }
}