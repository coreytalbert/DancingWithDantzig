
#pragma once

template<typename T>
class MatrixElement {
private:
    T value = 0;
public:
    MatrixElement() {}
    /* Construct a MatrixElement with value x. */
    MatrixElement( T & x ): value( x ) {}
    /* Destructor. */
    ~MatrixElement() { value = 0 ; }
    /* Set value to rhs. */
    void operator=( const T& rhs ) { value = rhs ; }
    /* Convert this MatrixElement to an object of type T. */
    & operator T() { return value ; }
} ;