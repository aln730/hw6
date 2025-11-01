// File: Matrix.c
// Author: Arnav Gawas

#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct matrix_st {
    size_t rows;
    size_t cols;
    float *data;
};


#define INDEX(mat, row, col) (((row) - 1) * (mat)->cols + ((col) - 1)) //Macros are cool


// Create a new matrix
Matrix mat_create(size_t rows, size_t cols) {
    Matrix mat = malloc(sizeof(struct matrix_st));
    if (!mat)
        return NULL;

    mat->rows = rows;
    mat->cols = cols;
    mat->data = calloc(rows * cols, sizeof(float));
    if (!mat->data) {
        free(mat);
        return NULL;
    }

    // Initialize
    if (rows == cols) {
        for (size_t i = 1; i <= rows; i++)
            mat->data[INDEX(mat, i, i)] = 1.0f;
    }

    return mat;
}



