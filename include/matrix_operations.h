#ifndef _OPERATION_H
#define _OPERATION_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

/* Basic math operations structures */

/* Base type data: 2d matrix of floats */
struct _float_2d_matrix {
    float ** _base_ptr;
    unsigned int row, col;
    // float ** transpose;
};


typedef struct _float_2d_matrix Matrix2Df;


// initialization
/* Creates de type `Matrix2Df`, a 2D matrix of floats (with all elements initialized to zero).

@param[in] uint i, number of rows
@param[in] uint j, number of columns 
@return Matrix2Df a pointer to the created matrix data type */
Matrix2Df * create_matrix(unsigned int i, unsigned int j);

/* Correctly closes and frees memory dinamically allocated to this data type.

@param[in] Matrix2Df m, the matrix to be closed */
void close_matrix(Matrix2Df*m);

/* Fills the matrix with the elements of the given float array. 

@param[in] Matrix2Df m, the matrix to be filled
@param[in] float* vec, the buffer of values to be put on the matrix
@return int 1 for successfully filling, 0 if not */
int fill_matrix(Matrix2Df *m, float * vec);

/* Fills the matrix with the elements of the given file name. It opens a stream to read
from the file the elements until it reaches the n*m th element. 

@param[in] Matrix2Df m, the matrix to be filled
@param[in] const char* f_name, the name of the file that contains the data
@return int 1 for successfully filling, 0 if not */
int fill_matrix_from_file(Matrix2Df*m, const char*f_name);

/* Standart printf in `stdout` to visualize the matrix values in plain ASCII.

@param[in] Matrix2Df m, the matrix to be visualized */
void print_matrix(Matrix2Df*m);

// operations
/* Addition operation between 2 matrices. Note: The matrices must have the same dimensions.

@param[in] Matrix2Df a operand
@param[in] Matrix2Df b operand
@return Matrix2Df result of a+b */
Matrix2Df* add_matrix(Matrix2Df *a, Matrix2Df *b);

/* Subtraction operation between 2 matrices. Note: The matrices must have the same dimensions.

@param[in] Matrix2Df a operand
@param[in] Matrix2Df b operand
@return Matrix2Df result of a-b */
Matrix2Df* sub_matrix(Matrix2Df *a, Matrix2Df *b);

/* Multiplication operation between 2 matrices. Note: The matrices must respect the dimensions
restriction for multiplication (number of columns of a must be equal to rows of b).

@param[in] Matrix2Df a operand
@param[in] Matrix2Df b operand
@return Matrix2Df result of a*b */
Matrix2Df* mult_matrix(Matrix2Df *a, Matrix2Df *b);

/* Multiplying a matrix by a `float` scalar operation.

@param[in] Matrix2Df a operand
@param[in] float f, scalar to multiply the matrix
@return Matrix2Df result of m*f */
Matrix2Df* scalar_mult(Matrix2Df *m, float f);

/* Get the transposed of matrix m.

@param[in] Matrix2Df m to find the transpose
@return Matrix2Df result m^T */
Matrix2Df* get_transposed(Matrix2Df *m);
#endif