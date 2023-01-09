#include <cstring>
#include "MatrixElement.h"
#pragma once

template <typename T>
class MatrixRow
{
private:
    unsigned size ;
    MatrixElement<T> * row = nullptr ;

public:
    /* Default constructor. Construct a MatrixRow of size 0. */
    MatrixRow(): size( 0 ) , row( nullptr ) {}

    /* Construct an empty MatrixRow of size s. */
    MatrixRow( const unsigned & s ): size( s ) , row( new MatrixElement<T>[ s ] )
    {

    }

    /* Construct a MatrixRow of size s from array r. */
    MatrixRow( const unsigned & s , const T * arr ): size( s ) , row( new MatrixElement<T>[ s ] )
    {
        if ( arr )
        {
            for ( int i = 0 ; i < s ; ++i )
            {
                row[ i ] = new MatrixElement<T>( arr[ i ] ) ;
            }
        }
    }

    /* Destructor. */
    ~MatrixRow()
    {
        //clear() ;
        size = 0 ;
    }

    void clear()
    {
        for ( unsigned i = 0 ; i < size ; ++i )
        {
            row[ i ] = 0 ;
        }
    }

    T & operator[]( const unsigned & i ) { return row[ i ] ; }

    MatrixRow<T> & operator=( const MatrixRow<T> * rhs )
    {
        this->size = rhs->size ;
        this->row = rhs->row ;
        return *this ;
    }

    operator T * ( ) { return ( float * ) row ; }


} ;