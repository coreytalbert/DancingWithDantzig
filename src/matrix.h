#include <cstdio>
#include "MatrixElement.h"
#include "MatrixRow.h"
#pragma once

template <typename T>
class Matrix
{
private:
    unsigned rows ;
    unsigned cols ;
    MatrixRow<T> * matrix = nullptr ;
    void initialize() ;

public:
    /* Square matrix constructor */
    Matrix( const unsigned & m ) ;
    /* Rectangular matrix constructor */
    Matrix( const unsigned & m , const unsigned & n ) ;
    /* Destructor */
    ~Matrix() ;
    /* Free all memory */
    void clear() ;
    /* Transpose the matrix. */
    void transpose() ;
    /* Scalar multiplication */
    void scale( const T & x ) ;
    /* for square matrices */
    void display() ;
    /* True if square matrix */
    bool isSquare() { return rows == cols; }
    /* Access the first element of a matrix row. */
    MatrixRow<T> & operator[]( const unsigned & i ) { return matrix[ i ]; }
    Matrix<T> & operator=( Matrix<T> && rhs ) ;

    static Matrix<T> & multiply( Matrix & L , Matrix & R ) ;
    static Matrix<T> & transpose( const Matrix & A ) ;

} ;

template <typename T>
void Matrix<T>::initialize()
{
    matrix = new MatrixRow<T>[ rows ];

    for ( unsigned i = 0 , x = 1 ; i < rows ; i ++ )
    {
        matrix[ i ] = new MatrixRow<T>( cols );
        for ( unsigned j = 0 ; j < cols ; j++ )
        {
            matrix[ i ][ j ] = x++;
        }
    }
}

template <typename T>
Matrix<T>::Matrix( const unsigned & m )
    : rows( m ) , cols( m )
{
    initialize() ;
}

/* Rectangular matrix constructor */
template <typename T>
Matrix<T>::Matrix( const unsigned & m , const unsigned & n )
    : rows( m ) , cols( n )
{
    initialize() ;
}

template <typename T>
Matrix<T>::~Matrix()
{
    clear() ;
}

template <typename T>
void Matrix<T>::clear()
{
    /* for ( unsigned i = 0 ; i < rows ; i++ )
    {
        delete &matrix[ i ] ;
    } */
    delete[] matrix ;
    rows = 0 ;
    cols = 0 ;
}

template <typename T>
void Matrix<T>::transpose()
{
    /* In-place square matrix transpose */
    if ( this->isSquare() )
    {
        for ( unsigned i = 0 ; i < cols ; i++ )
        {
            for ( unsigned j = i + 1 ; j < rows ; j++ )
            {
                T temp = matrix[ i ][ j ];
                matrix[ i ][ j ] = matrix[ j ][ i ] ;
                matrix[ j ][ i ] = temp ;
            }
        }
    }

    /* Rectangular matrix transpose */
    else
    {
        Matrix A_T( cols , rows ) ;
        for ( unsigned i = 0 ; i < cols ; i++ )
        {
            for ( unsigned j = 0 ; j < rows ; j++ )
            {
                A_T[ i ][ j ] = matrix[ j ][ i ] ;
            }
        }
        unsigned old_rows = rows ;
        unsigned old_cols = cols ;
        clear() ;
        rows = old_cols ;
        cols = old_rows ;
        // Must be some way to copy the matrix of A_T before it goes out of scope
        for ( unsigned i = 0 ; i < rows ;++i )
        {
            this->matrix[i] = new MatrixRow<T>(cols) ;
            for ( unsigned j = 0 ; j < cols ; ++j )
            {
                this->matrix[ i ][ j ] = A_T.matrix[ i ][ j ] ;
            }
        }
    }
}

template <typename T>
void Matrix<T>::scale( const T & x )
{
    for ( unsigned i = 0 ; i < rows ; ++i )
    {
        for ( unsigned j = 0 ; j < cols ; j++ )
        {
            matrix[ i ][ j ] *= x ;
        }
    }

}

template <typename T>
void Matrix<T>::display()
{
    for ( unsigned i = 0 ; i < rows ; i++ )
    {
        for ( unsigned j = 0 ; j < cols ; j++ )
        {
            printf( "A[%i][%i]: %1.2g\t" , i , j , matrix[ i ][ j ] ) ;
        }
        putchar( '\n' ) ;
    }
}

template <typename T>
Matrix<T> & Matrix<T>::multiply( Matrix & L , Matrix & R )
{
    Matrix * new_matrix ;
    /* Multiplication not defined for these matrices */
    if ( L.cols != R.rows )
    {
        new_matrix = new Matrix( 0 , 0 ) ;
    }
    /* Multiplication */
    else
    {
        new_matrix = new Matrix( L.rows , R.cols ) ;
        unsigned b = L.cols ;
        for ( unsigned x = 0 ; x < L.rows ; ++x )
        {
            for ( unsigned y = 0 ; y < R.cols;++y )
            {
                T new_value = 0 ;
                for ( int i = 0 ; i < b; ++i )
                {
                    new_value += L[ x ][ i ] * R[ i ][ y ] ;
                }
                new_matrix[ x ][ y ] = new_value ;
            }
        }
    }
    return * new_matrix ;
}

