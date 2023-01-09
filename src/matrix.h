#include <cstdio>
#pragma once

template <typename T>
class Matrix {
private:
    unsigned rows;
    unsigned cols;
    T **matrix = nullptr;
    void initialize();

public:
    /* Copy constructor */
    Matrix(Matrix<T> &);
    /* Square matrix constructor */
    Matrix(const unsigned &m);
    /* Rectangular matrix constructor */
    Matrix(const unsigned &, const unsigned &);
    /* Destructor */
    ~Matrix();
    /* Erase the contents of the matrix */
    void clear();
    /* Transpose the matrix. */
    void transpose();
    /* Scalar multiplication */
    void scale(const T &x);
    /* for square matrices */
    void display();
    /* True if square matrix */
    bool isSquare() { return rows == cols; }

    // ELEMENTARY ROW OPERATIONS
    bool rowSum(const unsigned &augend, const unsigned &addend, const T &scale = 1);
    bool rowMult(const unsigned &row, const T &scale);
    bool rowSwap(const unsigned &row_a, const unsigned &row_b);

    /* Access the first element of a matrix row. */
    T *operator[](const unsigned &i) { return matrix[i]; }
    // Matrix<T> & operator=( Matrix<T> && rhs ) ;

    static Matrix<T> &multiply(Matrix<T> &L, Matrix<T> &R);
    // static Matrix<T> & transpose( const Matrix<T> & A ) ;
};

template <typename T>
void Matrix<T>::initialize() {
    matrix = new T * [rows];
    for (unsigned i = 0, x = 1; i < rows; i++) {
        matrix[i] = new T[cols];
        for (unsigned j = 0; j < cols; j++) {
            matrix[i][j] = x++;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &A) {
    this->rows = A.rows;
    this->cols = A.cols;
    matrix = new T * [rows];
    for (unsigned i = 0; i < rows; i++) {
        matrix[i] = new T[cols];
        for (unsigned j = 0; j < cols; j++) {
            matrix[i][j] = A[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const unsigned &m): rows(m), cols(m) {
    initialize();
}

/* Rectangular matrix constructor */
template <typename T>
Matrix<T>::Matrix(const unsigned &m, const unsigned &n): rows(m), cols(n) {
    initialize();
}

template <typename T>
Matrix<T>::~Matrix() {
    clear();
}

template <typename T>
void Matrix<T>::clear() {
    for (unsigned i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    rows = 0;
    cols = 0;
}

template <typename T>
void Matrix<T>::transpose() {
    /* In-place square matrix transpose */
    if (this->isSquare()) {
        for (unsigned i = 0; i < cols; i++) {
            for (unsigned j = i + 1; j < rows; j++) {
                T temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }

    /* Rectangular matrix transpose */
    else {
        Matrix A_T(cols, rows);
        for (unsigned i = 0; i < cols; i++) {
            for (unsigned j = 0; j < rows; j++) {
                A_T[i][j] = matrix[j][i];
            }
        }
        unsigned old_rows = rows;
        unsigned old_cols = cols;
        clear();
        rows = old_cols;
        cols = old_rows;
        // Must be some way to copy the matrix of A_T before it goes out of scope
        for (unsigned i = 0; i < rows; ++i) {
            this->matrix[i] = new T[cols];
            for (unsigned j = 0; j < cols; ++j) {
                this->matrix[i][j] = A_T.matrix[i][j];
            }
        }
    }
}

template <typename T>
void Matrix<T>::scale(const T &x) {
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; j++) {
            matrix[i][j] *= x;
        }
    }
}

template <typename T>
void Matrix<T>::display() {
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            printf("A[%i][%i]: %1.2g\t", i, j, matrix[i][j]);
        }
        putchar('\n');
    }
}

template <typename T>
Matrix<T> &Matrix<T>::multiply(Matrix<T> &L, Matrix<T> &R) {
    Matrix<T> *new_matrix;
    /* Multiplication not defined for these matrices */
    if (L.cols != R.rows) {
        new_matrix = new Matrix<T>(0, 0);
    }
    /* Multiplication */
    else {
        new_matrix = new Matrix<T>(L.rows, R.cols);
        unsigned b = L.cols;
        for (unsigned x = 0; x < L.rows; ++x) {
            for (unsigned y = 0; y < R.cols; ++y) {
                T new_value = 0;
                for (unsigned i = 0; i < b; ++i) {
                    new_value += L[x][i] * R[i][y];
                }
                (*new_matrix)[x][y] = new_value;
            }
        }
    }
    return *new_matrix;
}

template <typename T>
bool Matrix<T>::rowSum(const unsigned &augend, const unsigned &addend, const T &scale) {
    bool op_success = false;
    return op_success;
}

template <typename T>
bool Matrix<T>::rowMult(const unsigned &row, const T &scale) {
    bool op_success = false;
    if (row > 0 and row <= this->rows) {
        for (unsigned i = 0; i < cols; ++i) {
            matrix[row - 1][i] *= scale;
        }
        op_success = true;
    }
    return op_success;
}

template <typename T>
bool Matrix<T>::rowSwap(const unsigned &row_a, const unsigned &row_b) {
    bool op_success = false;
    if (row_a > 0 and row_a <= this->rows and row_b > 0 and row_b <= this->rows) {
        if (row_a != row_b) {
            for (unsigned i = 0; i < cols; ++i) {
                T temp = matrix[row_a - 1][i];
                matrix[row_a - 1][i] = matrix[row_b - 1][i];
                matrix[row_b - 1][i] = temp;
            }
        }
        op_success = true;
    }
    return op_success;
}
