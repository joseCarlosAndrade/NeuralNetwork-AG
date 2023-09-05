#include"../include/matrix_operations.h"


Matrix2Df* add_matrix(Matrix2Df *a, Matrix2Df *b) {
    // base checking
    assert(
        a!=NULL &&
        b!= NULL &&
        a->row == b->row &&
        a->col == b->col
    );

    Matrix2Df * r = create_matrix(a->row, a->col);

    for (int i = 0; i < r->row; i++) {
        for (int j = 0; j < r->col; j++) {
            r->_base_ptr[i][j] = a->_base_ptr[i][j] + b->_base_ptr[i][j];
        }
    }

    return r;
}


Matrix2Df* sub_matrix(Matrix2Df *a, Matrix2Df *b) {
    // base checking
    assert(
        a!=NULL &&
        b!= NULL &&
        a->row == b->row &&
        a->col == b->col
    );

    Matrix2Df * r = create_matrix(a->row, a->col);

    for (int i = 0; i < r->row; i++) {
        for (int j = 0; j < r->col; j++) {
            r->_base_ptr[i][j] = a->_base_ptr[i][j] - b->_base_ptr[i][j];
        }
    }

    return r;

}

Matrix2Df* scalar_mult(Matrix2Df *m, float f) {
    assert(m !=NULL );

    Matrix2Df * r = create_matrix(m->row, m->col);

        for (int i = 0; i < m->row; i++) {
            for (int j = 0; j < m->col; j++) {
                r->_base_ptr[i][j] = m->_base_ptr[i][j]*f;
            }
        }
    return r;
}

Matrix2Df* mult_matrix(Matrix2Df *a, Matrix2Df *b) {
    assert(
        a!=NULL &&
        b!= NULL &&
        a->col == b->row
    );

    Matrix2Df * r = create_matrix(a->row, b->col);

    for ( int i = 0; i < a->row ; i++) {
        for (int j = 0; j< b->col ; j++) {

            for (int o = 0 ; o < a->col ; o++) {
                r->_base_ptr[i][j] += a->_base_ptr[i][o] * b->_base_ptr[o][j];
            }
        }
    }

    return r;
}

Matrix2Df* get_transposed(Matrix2Df *m) {
    assert(m!= NULL);

    Matrix2Df * t = create_matrix(m->col, m->row);

    for (int i = 0; i < t->row; i++) {
        for (int j = 0; j < t->col; j++) {
            t->_base_ptr[i][j] = m->_base_ptr[j][i];
        }
    }
    return t;
}
 