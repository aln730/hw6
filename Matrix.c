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

// Destroy Matrix
void mat_destroy(Matrix mat) {
    if (!mat) return;
    free(mat->data);
    free(mat);
}

void mat_init(Matrix mat, const float data[]) {
    if (!mat || !data) return;
    size_t total = mat->rows * mat->cols;
    for (size_t i = 0; i < total; i++)
        mat->data[i] = data[i];
}

// Duplicate a matrix
Matrix mat_duplicate(const Matrix mat) {
    if (!mat) return NULL;
    Matrix dup = mat_create(mat->rows, mat->cols);
    if (!dup) return NULL;

    size_t total = mat->rows * mat->cols;
    for (size_t i = 0; i < total; i++)
        dup->data[i] = mat->data[i];

    return dup;
}

// Equality Comparison
bool mat_equals(const Matrix m1, const Matrix m2) {
    if (!m1 || !m2)
        return false;
    if (m1->rows != m2->rows || m1->cols != m2->cols)
        return false;

    size_t total = m1->rows * m1->cols;
    for (size_t i = 0; i < total; i++) {
        if (m1->data[i] != m2->data[i])
            return false;
    }
    return true;
}

// Scalar Multiplication
void mat_scalar_mult(Matrix mat, float scalar) {
    if (!mat) return;
    size_t total = mat->rows * mat->cols;
    for (size_t i = 0; i < total; i++)
        mat->data[i] *= scalar;
}

// mat_mul
Matrix mat_mult(const Matrix m1, const Matrix m2) {
    if (!m1 || !m2)
        return NULL;

    if (m1->cols != m2->rows)
        return NULL;

    Matrix result = mat_create(m1->rows, m2->cols);
    if (!result)
        return NULL;

    for (size_t i = 1; i <= m1->rows; i++) {
        for (size_t j = 1; j <= m2->cols; j++) {
            float sum = 0.0f;
            for (size_t k = 1; k <= m1->cols; k++)
                sum += m1->data[INDEX(m1, i, k)] * m2->data[INDEX(m2, k, j)];
            result->data[INDEX(result, i, j)] = sum;
        }
    }

    return result;
}
